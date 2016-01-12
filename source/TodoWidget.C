#include "TodoWidget.h"
#include "Todo.h"
#include "ToDoApp.h"
#include "Mailing.h"

#include <Wt/WCalendar>
#include <Wt/WDate>
#include <Wt/WDateEdit>
#include <Wt/WCheckBox>

#include <Wt/WApplication>
#include <Wt/WLogger>
#include <Wt/Dbo/WtSqlTraits>
#include <functional>

using namespace Wt;
namespace dbo = Wt::Dbo;

TodoWidget::TodoWidget(WContainerWidget *parent,
    dbo::ptr<UserAccount> user)
    : WContainerWidget(parent),
    user_(user)
{
  setStyleClass("todo");

  title_ = new WText("Hello " + user_->name + "<br/>", this);
  todoTitle_ = new WLineEdit(this);
  todoTitle_->setFocus();
  addTodoButton_ = new WPushButton(tr("todo.add"), this);
  addTodoButton_->clicked().connect(this, &TodoWidget::clickTodo);
  mailLineEdit_ = new WLineEdit(this);

  dbo::Session &session = ToDoApp::toDoApp()->session;
  dbo::Transaction transaction(session);

  mailLineEdit_->setText(user_->mail.toUTF8());

  transaction.commit();

  saveMailButton_ = new WPushButton(tr("todo.save_mail"), this);
  saveMailButton_->clicked().connect(this, &TodoWidget::saveMail);
  sortBoxText_ = new WText("<br/>Sort by ", this);
  sortCBox_ = new WComboBox(this);
  sortCBox_->addItem("deadline");
  sortCBox_->addItem("title");
  sortCBox_->addItem("done");
  sortCBox_->changed().connect(std::bind([=] () {
    todoTable_->clear();
    TodoWidget::drawTable(sortCBox_->currentText().narrow());
  }));
  TodoWidget::drawTable();
}

void TodoWidget::drawTable(std::string sortBy)
{
  todoTable_ = new WTable(this);
  todoTable_->setHeaderCount(1);
  todoTable_->elementAt(0, 0)->addWidget(new Wt::WText(tr("todo.num")));
  todoTable_->elementAt(0, 1)->addWidget(new Wt::WText(tr("todo.title")));
  todoTable_->elementAt(0, 2)->addWidget(new Wt::WText(tr("todo.deadline")));
  todoTable_->elementAt(0, 3)->addWidget(new Wt::WText(tr("todo.done")));
  todoTable_->elementAt(0, 4)->addWidget(new Wt::WText(tr("todo.notification")));

  dbo::Session &session = ToDoApp::toDoApp()->session;
  dbo::Transaction transaction(session);

  typedef dbo::collection< dbo::ptr<Todo> > MyTodos;
  dbo::Query< dbo::ptr<Todo> > query = session.find<Todo>();
  query.where("user_id = ?").bind(user_.id());
  query.orderBy(sortBy);
  MyTodos todos = query.resultList();

  Wt::WDateEdit **datePickers = new Wt::WDateEdit*[todos.size()];
  Wt::WCheckBox **doneCheckBox = new Wt::WCheckBox*[todos.size()];
  Wt::WCheckBox **notificationCheckBox = new Wt::WCheckBox*[todos.size()];

  int row = 1;

  for (MyTodos::const_iterator i = todos.begin(); i != todos.end(); ++i)
  {
    dbo::ptr<Todo> todo = *i;
    todoTable_->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("{1}").arg(row)));
    todoTable_->elementAt(row, 1)->addWidget(new Wt::WText((*i)->title.toUTF8()));

    datePickers[row-1] = new Wt::WDateEdit();
    todoTable_->elementAt(row, 2)->addWidget(datePickers[row-1]);
    datePickers[row-1]->setDate(todo->deadline);
    datePickers[row-1]->setBottom(Wt::WDate::currentServerDate());

    datePickers[row-1]->changed().connect(std::bind([=] () {
      dbo::Session &session = ToDoApp::toDoApp()->session;
      dbo::Transaction transaction(session);
      if(datePickers[row-1]->validate() == Wt::WValidator::Valid)
        todo.modify()->deadline = datePickers[row-1]->date();
      transaction.commit();

    }));
    doneCheckBox[row-1] = new Wt::WCheckBox();
    todoTable_->elementAt(row, 3)->addWidget(doneCheckBox[row-1]);
    Wt::CheckState isDone;
    if(todo->done == 0)
      isDone = Wt::Unchecked;
    else
      isDone = Wt::Checked;
    doneCheckBox[row-1]->setCheckState((isDone));
    doneCheckBox[row-1]->changed().connect(std::bind([=] () {
      dbo::Session &session = ToDoApp::toDoApp()->session;
      dbo::Transaction transaction(session);
      todo.modify()->done = doneCheckBox[row-1]->checkState();
      transaction.commit();
    }));

    notificationCheckBox[row-1] = new Wt::WCheckBox();
    todoTable_->elementAt(row, 4)->addWidget(notificationCheckBox[row-1]);
    Wt::CheckState send;
    if(todo->sendNotification == 0)
      send = Wt::Unchecked;
    else
    {
      send = Wt::Checked;
      notificationCheckBox[row-1]->setEnabled(false);
    }
    notificationCheckBox[row-1]->setCheckState(send);
    notificationCheckBox[row-1]->changed().connect(std::bind([=] () {
      dbo::Session &session = ToDoApp::toDoApp()->session;
      dbo::Transaction transaction(session);
      todo.modify()->sendNotification = notificationCheckBox[row-1]->checkState();
      transaction.commit();
      notificationCheckBox[row-1]->setEnabled(false);
    }));
    notificationCheckBox[row-1]->checked().connect(boost::bind(&TodoWidget::sendNotification, this, user_->mail.toUTF8(), todo->title));

    row++;
  }

  transaction.commit();
}

void TodoWidget::clickTodo()
{
  dbo::Session &session = ToDoApp::toDoApp()->session;
  dbo::Transaction transaction(session);

  WApplication::instance()->log("notice") << "Creating todo: " << todoTitle_->text().toUTF8();
  dbo::ptr<Todo> todo = session.add(new Todo());
  todo.modify()->title = todoTitle_->text().toUTF8();
  todo.modify()->user = user_;

  transaction.commit();

  todoTable_->clear();
  TodoWidget::drawTable();
}

void TodoWidget::saveMail()
{
  dbo::Session &session = ToDoApp::toDoApp()->session;
  dbo::Transaction transaction(session);

  user_.modify()->mail = mailLineEdit_->text().toUTF8();

  transaction.commit();
}

void TodoWidget::sendNotification(std::string email, Wt::WString todoTitle)
{
  Mailing *mailing = new Mailing();
  mailing->sendMail(email, todoTitle);
}

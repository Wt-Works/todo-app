#include "TodoWidget.h"
#include "Todo.h"
#include "ToDoApp.h"

#include <Wt/WApplication>
#include <Wt/WLogger>
#include <Wt/Dbo/WtSqlTraits>

using namespace Wt;
namespace dbo = Wt::Dbo;

TodoWidget::TodoWidget(WContainerWidget *parent,
    dbo::ptr<UserAccount> user)
    : WContainerWidget(parent),
    user_(user)
{
  setStyleClass("todo");

  title_ = new WText("Hello " + user_->name, this);
  todoTitle_ = new WLineEdit(this);
  todoTitle_->setFocus();
  addTodoButton_ = new WPushButton(tr("todo.add"), this);
  addTodoButton_->clicked().connect(this, &TodoWidget::clickTodo);
  TodoWidget::drawTable();
}

void TodoWidget::drawTable()
{
  todoTable_ = new WTable(this);
  todoTable_->setHeaderCount(1);
  todoTable_->elementAt(0, 0)->addWidget(new Wt::WText(tr("todo.num")));
  todoTable_->elementAt(0, 1)->addWidget(new Wt::WText(tr("todo.title")));

  dbo::Session &session = ToDoApp::toDoApp()->session;
  dbo::Transaction transaction(session);

  typedef dbo::collection< dbo::ptr<Todo> > MyTodos;
  MyTodos todos = session.find<Todo>("where user_id = ?").bind(user_.id());

  int row = 1;

  for (MyTodos::const_iterator i = todos.begin(); i != todos.end(); ++i)
  {
    todoTable_->elementAt(row, 0)->addWidget(new Wt::WText(Wt::WString::fromUTF8("{1}").arg(row)));
    todoTable_->elementAt(row, 1)->addWidget(new Wt::WText((*i)->title.toUTF8()));

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

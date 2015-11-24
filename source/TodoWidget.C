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
}

void TodoWidget::clickTodo()
{
  dbo::Session &session = ToDoApp::toDoApp()->session;
  dbo::Transaction transaction(session);

  WApplication::instance()->log("notice") << "Creating todo: " << todoTitle_->text().toUTF8();
  dbo::ptr<Todo> todo = session.add(new Todo());
  todo.modify()->title = todoTitle_->text().toUTF8();

  transaction.commit();
}

#include "TodoWidget.h"
#include "Todo.h"
#include "ToDoApp.h"

#include <Wt/Dbo/WtSqlTraits>

using namespace Wt;

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
  // Session& session = ToDoApp::ToDoApp()->session;
  // Transaction transaction(session);
  //
  // ptr<Todo> todo =
  //   ToDoApp::ToDoApp()->session.add(new Todo());
  // todo.modify()->title = todoTitle_->text().toUTF8();
  //
  // transaction.commit();
}

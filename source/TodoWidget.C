#include "TodoWidget.h"
#include "Todo.h"

using namespace Wt;

TodoWidget::TodoWidget(WContainerWidget *parent, dbo::ptr<UserAccount> user) : WContainerWidget(parent), user_(user)
{
  title_ = new WText("Hello world!", this);
  addTodoButton_ = new WPushButton(tr("todo.add"), this);
  todoTitle_ = new WLineEdit(this);
  todoTitle_->setFocus();
}

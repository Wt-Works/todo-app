#include "UserAccount.h"

#include <Wt/Dbo/Dbo>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>

class TodoWidget : public Wt::WContainerWidget
{
public:
  // TodoWidget();
  TodoWidget(Wt::WContainerWidget *parent,
    dbo::ptr<UserAccount> user);
  void clickTodo();

private:
  Wt::Signal<Wt::WString> todoAdded_;
  Wt::WText *title_;
  Wt::WPushButton *addTodoButton_;
  Wt::WLineEdit *todoTitle_;
  Wt::WText *output_;
  dbo::ptr<UserAccount> user_;
};

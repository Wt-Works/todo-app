#include "UserAccount.h"

#include <Wt/Dbo/Dbo>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>

namespace dbo = Wt::Dbo;

class TodoWidget : public Wt::WContainerWidget
{
public:
  TodoWidget();
  TodoWidget(Wt::WContainerWidget *parent, dbo::ptr<UserAccount> user);

private:
  Wt::WText *title_;
  Wt::WPushButton *addTodoButton_;
  Wt::WLineEdit *todoTitle_;
  dbo::ptr<UserAccount> user_;
};

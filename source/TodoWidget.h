#include "UserAccount.h"

#include <Wt/Dbo/Dbo>
#include <Wt/WContainerWidget>
#include <Wt/WText>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
#include <Wt/WTable>
#include <Wt/WComboBox>

class TodoWidget : public Wt::WContainerWidget
{
public:
  // TodoWidget();
  TodoWidget(Wt::WContainerWidget *parent,
    dbo::ptr<UserAccount> user);
  void clickTodo();
  void saveMail();
  void drawTable(std::string sortBy = "deadline");
  void sendNotification(std::string email, Wt::WString todoTitle);

private:
  Wt::Signal<Wt::WString> todoAdded_;
  Wt::WText *title_;
  Wt::WText *sortBoxText_;
  Wt::WPushButton *addTodoButton_;
  Wt::WLineEdit *todoTitle_;
  Wt::WPushButton *saveMailButton_;
  Wt::WLineEdit *mailLineEdit_;
  Wt::WText *output_;
  Wt::WTable *todoTable_;
  Wt::WTable *doneTable_;
  Wt::WComboBox *sortCBox_;
  dbo::ptr<UserAccount> user_;
};

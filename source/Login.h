#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>

class Login : public Wt::WContainerWidget
{
public:
  Login(Wt::WContainerWidget* parent);

  Wt::Signal<Wt::WString>& loggedIn() { return loggedIn_; }

private:
  void userNameEnterPressed();
  void loginClicked(const Wt::WMouseEvent& me);
  void login();

private:
  Wt::Signal<Wt::WString> loggedIn_;
  Wt::WLineEdit *userNameEdit_;
  Wt::WPushButton *loginButton_;
};

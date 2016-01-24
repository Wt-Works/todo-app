#include "Login.h"

#include <Wt/WLabel>
#include <functional>

using namespace Wt;

Login::Login(WContainerWidget* parent) : WContainerWidget(parent), loggedIn_(this)
{
  setStyleClass("login");

  WLabel* userNameL = new WLabel(tr("login.userName"), this);
  userNameEdit_ = new WLineEdit(this);
  userNameEdit_->setFocus();
  userNameL->setBuddy(userNameEdit_);

  loginButton_ = new WPushButton(tr("login.loginButton"), this);
  loginButton_->setEnabled(false);
  userNameEdit_->textInput().connect(std::bind([=] () {
    if(userNameEdit_->text() == "")
      loginButton_->setEnabled(false);
    else
      loginButton_->setEnabled(true);
  }));
  loginButton_->clicked().connect(this, &Login::login);
}

void Login::login()
{
  loggedIn_.emit(userNameEdit_->text());
}

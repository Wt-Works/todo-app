#include "Login.h"

#include <Wt/WLabel>

using namespace Wt;

Login::Login(WContainerWidget* parent) : WContainerWidget(parent), loggedIn_(this)
{
  setStyleClass("login");

  WLabel* userNameL = new WLabel(tr("login.userName"), this);
  userNameEdit_ = new WLineEdit(this);
  userNameEdit_->setFocus();
  userNameL->setBuddy(userNameEdit_);

  userNameEdit_->enterPressed().connect(this, &Login::login);

  loginButton_ = new WPushButton(tr("login.loginButton"), this);
  loginButton_->clicked().connect(this, &Login::login);
}

void Login::login()
{
  loggedIn_.emit(userNameEdit_->text());
}

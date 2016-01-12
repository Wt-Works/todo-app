#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WLogger>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WBootstrapTheme>

#include "ToDoApp.h"

#include "Todo.h"
#include "Login.h"
#include "TodoWidget.h"
// #include "UserAccount.h"
class UserAccount;


using namespace Wt;

ToDoApp::ToDoApp(const WEnvironment &env)
  : WApplication(env),
  sqlite3_(Wt::WApplication::appRoot() + "todo.db")
{
  setTheme(new WBootstrapTheme());

  session.setConnection(sqlite3_);
  sqlite3_.setProperty("show-queries", "true");

  session.mapClass<UserAccount>("user_account");
  session.mapClass<Todo>("todo");

  dbo::Transaction transaction(session);
  try {
    session.createTables();
    log("info") << "db created";
  } catch (...) {
    log("info") << "using existing db";
  }

  transaction.commit();

  messageResourceBundle().use(appRoot() + "todo");

  useStyleSheet("todo.css");

  Login *login = new Login(root());
  login->loggedIn().connect(this, &ToDoApp::login);
}

void ToDoApp::login(const WString &user)
{
  root()->clear();

  dbo::ptr<UserAccount> ua = UserAccount::login(session, user);
  new TodoWidget(root(), ua);
}

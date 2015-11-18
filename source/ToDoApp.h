#include <Wt/WApplication>
#include <Wt/WString>

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/backend/Sqlite3>

class ToDoApp : public Wt::WApplication
{
public:
  Wt::Dbo::Session session;

  ToDoApp(const Wt::WEnvironment &env);

  static ToDoApp *toDoApp()
  {
    return (ToDoApp*)WApplication::instance();
  }

private:
  Wt::Dbo::backend::Sqlite3 sqlite3_;

  void login(const Wt::WString &user);
};

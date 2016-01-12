#include <Wt/WDate>
#include <Wt/WString>

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>

class Todo;

namespace dbo = Wt::Dbo;

class UserAccount
{
public:
  Wt::WString name;
  Wt::WString mail;
  dbo::collection< dbo::ptr<Todo> > entries;

  UserAccount();
  UserAccount(const Wt::WString &name);

  static dbo::ptr<UserAccount> login(dbo::Session &session, const Wt::WString &user);
  template<class Action>
  void persist(Action &a)
  {
    dbo::field(a, name, "name");
    dbo::field(a, mail, "mail");
    dbo::hasMany(a, entries, dbo::ManyToOne, "user");
  }
};

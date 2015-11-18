#include <Wt/WDateTime>

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>

class UserAccount;

namespace dbo = Wt::Dbo;

class Todo
{
public:
  dbo::ptr<UserAccount> user;

  Wt::WDateTime deadline;
  Wt::WString title;
  Wt::WString description;

  template<class Action>
  void persist(Action &a)
  {
    dbo::belongsTo(a, user, "user");

    dbo::field(a, deadline, "deadline");
    dbo::field(a, title, "title");
    dbo::field(a, description, "description");
  }
};

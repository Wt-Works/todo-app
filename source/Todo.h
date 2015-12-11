#include <Wt/WDate>

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>

class UserAccount;
// #include "UserAccount.h"

namespace dbo = Wt::Dbo;

class Todo
{
public:
  dbo::ptr<UserAccount> user;

  Wt::WDate deadline;
  Wt::WString title;
  Wt::WString description;
  bool done;

  template<class Action>
  void persist(Action &a)
  {
    dbo::belongsTo(a, user, "user");

    dbo::field(a, deadline, "deadline");
    dbo::field(a, title, "title");
    dbo::field(a, description, "description");
    dbo::field(a, done, "done");
  }
};

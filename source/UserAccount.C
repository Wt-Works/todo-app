#include "UserAccount.h"
#include "Todo.h"

#include <Wt/WApplication>
#include <Wt/WLogger>

#include <Wt/Dbo/WtSqlTraits>

using namespace Wt;
using namespace Wt::Dbo;

UserAccount::UserAccount()
{ }

UserAccount::UserAccount(const WString &aName)
  : name(aName)
{ }

ptr<UserAccount> UserAccount::login(Session& session,
				    const WString& userName)
{
  Transaction transaction(session);

  ptr<UserAccount> ua = session.find<UserAccount>("where name = ?").bind(userName);

  if(!ua) {
    WApplication::instance()->log("notice") << "Creating user: " << userName.toUTF8();

    ua = session.add(new UserAccount(userName));
  }

  transaction.commit();

  return ua;
}

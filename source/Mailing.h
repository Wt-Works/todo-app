#include <Wt/Mail/Client>
#include <Wt/Mail/Message>

class Mailing
{
public:
  Mailing();
  // void sendMail();

private:
  Wt::Mail::Message message;
  Wt::Mail::Client client;
};

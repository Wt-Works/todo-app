#include <Wt/Mail/Client>
#include <Wt/Mail/Message>

class Mailing
{
public:
  Mailing();
  void sendMail(std::string email, Wt::WString todoTitle);

private:
  Wt::Mail::Message message;
  Wt::Mail::Client client;
};

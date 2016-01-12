#include <Wt/Mail/Client>
#include <Wt/Mail/Message>
#include <Wt/WLogger>

#include "Mailing.h"

Mailing::Mailing()
{
}

void Mailing::sendMail(std::string email, Wt::WString todoTitle)
{
  message.setFrom(Wt::Mail::Mailbox("todoapp@todoapp.com", "To Do App"));
  message.addRecipient(Wt::Mail::To, Wt::Mail::Mailbox(email));
  message.setSubject("Notification " + todoTitle);
  // message.setDate();
  message.setBody("That mail client seems to be working.");
  message.addHtmlBody ("<p>"
       "<a href=\"http://www.webtoolkit.eu/wt\">That mail client</a>"
       " seems to be working just great!</p>");

  client.connect("localhost");
  client.send(message);
  Wt::log("info") << "mail sent";
}

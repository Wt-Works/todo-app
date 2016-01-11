#include <Wt/Mail/Client>
#include <Wt/Mail/Message>
#include <Wt/WLogger>

#include "Mailing.h"

Mailing::Mailing()
{
  // message = new Wt::Mail::Message();
  message.setFrom(Wt::Mail::Mailbox("todoapp@todoapp.com", "To Do App"));
  message.addRecipient(Wt::Mail::To, Wt::Mail::Mailbox("mikolaj06120@gmail.com", "Mikolaj M."));
  message.setSubject("Hey there!");
  message.setBody("That mail client seems to be working.");
  message.addHtmlBody ("<p>"
       "<a href=\"http://www.webtoolkit.eu/wt\">That mail client</a>"
       " seems to be working just great!</p>");

  // client = new Wt::Mail::Client();
  client.connect("localhost");
  client.send(message);
  Wt::log("info") << "mail sent";
}

// void Mailing::sendMail()
// {
//   message = new Mail::Message();
//   message->setFrom(Mail::Mailbox("todoapp@todoapp.com", "To Do App");
//   message->addRecipient(Mail::To, Mail::Mailbox("mikolaj06120@gmail.com", "Mikolaj M.");
//   message->setSubject("Hey there!");
//   message->setBody("That mail client seems to be working.");
//   message->addHtmlBody ("<p>"
//        "<a href=\"http://www.webtoolkit.eu/wt\">That mail client</a>"
//        " seems to be working just great!</p>");
//
//   client = new Mail::Client();
//   client->connect("localhost");
//   client->send(message);
// }

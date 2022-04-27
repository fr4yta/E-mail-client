#include "ReadMails.h"

ReadMails::ReadMails(string serverAddress, string userName, string password, int port) : serverAddress(serverAddress), userName(userName), password(password), port(port) {}

ReadMails::Mail ReadMails::getMailInfo(POP3ClientSession& session, int messageId) {
    Poco::Net::MailMessage message;
    session.retrieveMessage(messageId, message);

    ReadMails::Mail mail;
    mail.receivedTime = message.getDate().epochTime();
    mail.subject = message.getSubject();
    mail.sender = message.getSender();
    mail.content = message.getContent();
    mail.getContentType = message.getContentType();
    return mail;
}

vector <ReadMails::Mail> ReadMails::downloadLastMails(int numberOfMails) {
    try {
        POP3ClientSession session(this->serverAddress, this->port);
        session.login(this->userName, this->password);

        POP3ClientSession::MessageInfoVec messages;
        session.listMessages(messages);

        vector <Mail> downloadedMails;
        int counter = 0;
        for (auto m = messages.rbegin(); m != messages.rend(); ++m) {
            if (counter >= numberOfMails) {
                break;
            }

            Mail currentMail = getMailInfo(session, m->id);
            currentMail.sizeInBytes = m->size;
            currentMail.mailId = m->id;
            downloadedMails.push_back(currentMail);
            counter++;
        }

        return downloadedMails;
    }
    catch (const POP3ClientSession& e) {
        exit(0);
    }
    catch (const POP3Exception& e) {
        exit(1);
    }
    catch (const NetException& e) {
        exit(2);
    }
}
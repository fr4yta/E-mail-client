#include "WriteMail.h"

WriteMail::WriteMail(string smtpserverAddress, string userName, string password, int port) : smtpserverAddress(smtpserverAddress), userName(userName), password(password), port(port) {}

string WriteMail::writeMail(string toAdressEmailSend, string titleToSend, string messageToSend) {
    try {
        MailRecipient recipient1(MailRecipient::PRIMARY_RECIPIENT, toAdressEmailSend);

        MailMessage message;
        message.setRecipients({recipient1});
        message.setSubject(titleToSend);
        message.setSender(this->userName);
        message.setContentType("text/plain; charset=utf-8;");
        message.setContent(messageToSend);

        SMTPClientSession session(this->smtpserverAddress, this->port);
        session.login(SMTPClientSession::AUTH_PLAIN, this->userName, this->password);
        session.sendMessage(message);
        session.close();
        return "ok";
    }
    catch (const SMTPException& e) {
        string what = e.what();
        string message = e.message();
        return "B��d z obs�ug� SMTP: " + what + " wiadomo��: " + message;
        exit(0);
    }
    catch (const NetException& e) {
        string what = e.what();
        return "B��d po stronie obs�ugi sieci: " + what;
        exit(1);
    }
}
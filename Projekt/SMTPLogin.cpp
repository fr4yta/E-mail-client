#include "SMTPLogin.h"

SMTPLogin::SMTPLogin(string smtpserverAddress, string userName, string password, int port) : smtpserverAddress(smtpserverAddress), userName(userName), password(password), port(port) {}

string SMTPLogin::loginSMTP() {
    try {
        SMTPClientSession session(this->smtpserverAddress, this->port);
        session.login(SMTPClientSession::AUTH_PLAIN, this->userName, this->password);
        session.close();
        return "ok";
    }
    catch (const exception& e) {
        return "B��d z obs�ug� SMTP. Sprawd� poprawno�� danych.";
        exit(0);
    }
    catch (const SMTPClientSession& e) {
        return "Przekroczono limit po��cze�: " + to_string(e.getTimeout().milliseconds()) + " ms.";
        exit(1);
    }
    catch (const SMTPException& e) {
        string what = e.what();
        string message = e.message();
        return "B��d z obs�ug� SMTP: " + what + " wiadomo��: " + message;
        exit(2);
    }
    catch (const NetException& e) {
        string what = e.what();
        return "B��d po stronie obs�ugi sieci: " + what;
        exit(3);
    }
}
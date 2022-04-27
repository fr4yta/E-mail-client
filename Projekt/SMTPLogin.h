#pragma once
#include <iostream>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/NetException.h>

using namespace std;
using namespace Poco::Net;

/** Klasa SMTPLogin odpowiedzialna za probe logowania do protokolu `SMTP` */
class SMTPLogin {
public:
    /// Adresu serwera SMTP
    string smtpserverAddress;
    /// Nazwa uzytkownika
    string userName;
    /// Haslo uzytkownika
    string password;
    /// Port serwera SMTP
    int port;

    /** Konstruktor `SMTPLogin` przechowujace dane do logowania */
    SMTPLogin(string smtpserverAddress, string userName, string password, int port = 25);

    /** Metoda `loginSMTP()` odpowiedzialna za probe logowania do protokolu `SMTP` */
    string loginSMTP();
};
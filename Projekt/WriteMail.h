#pragma once
#include <iostream>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/NetException.h>

using namespace std;
using namespace Poco::Net;

/** Klasa WriteMail odpowiedzialna za probe wyslania wiadomosci za pomoca protokolu `SMTP` */
class WriteMail {
public:
    /// Adresu serwera SMTP
    string smtpserverAddress;
    /// Nazwa uzytkownika
    string userName;
    /// Haslo uzytkownika
    string password;
    /// Port serwera SMTP
    int port;

    /** Konstruktor `WriteMail` przechowujace dane do logowania */
    WriteMail(string smtpserverAddress, string userName, string password, int port = 25);

    /** Metoda `writeMail()` wysyla wiadomosc email
    *
    * @param toAdressEmailSend - adres email do kogo ma zostac wyslany email
    * @param titleTosend - tytul wiadomosci email
    * @param messageToSend - kontent wiadomosci email (wiadomosc)
    * @result - zwraca `ok` jesli wiadomosc zostala wyslana poprawnie, jesli nie zwraca blad (dlaczego wiadomosc nie zostala wyslana)
    */
    string writeMail(string toAdressEmailSend, string titleToSend, string messageToSend);
};
#pragma once
#include <iostream>
#include <Poco/Net/POP3ClientSession.h>
#include <Poco/Net/MessageHeader.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/NetException.h>

using namespace std;
using namespace Poco::Net;

/** Klasa POP3Login odpowiedzialna za probe logowania do protokolu `POP3` */
class POP3Login {
public:
    /// Adresu serwera POP3
    string serverAddress;
    /// Nazwa uzytkownika
    string userName;
    /// Haslo uzytkownika
    string password;
    /// Port serwera POP3
    int port;

    /** Konstruktor `POP3Login` przechowujace dane do logowania */
    POP3Login(string serverAddress, string userName, string password, int port = 110);

    /** Metoda `loginPOP3()` odpowiedzialna za probe logowania do protokolu `POP3` */
    string loginPOP3();
};
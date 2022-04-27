#pragma once
#include <iostream>

#include <Poco/Net/POP3ClientSession.h>
#include <Poco/Net/MessageHeader.h>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/NetException.h>

using namespace std;
using namespace Poco::Net;

/** Klasa `ReadMails` odpowiedzialna za odbieranie listy wiadomosci z poczty za pomoca protokolu `POP3` */
class ReadMails {
public:
    /// Adresu serwera POP3
    string serverAddress;
    /// Nazwa uzytkownika
    string userName;
    /// Haslo uzytkownika
    string password;
    /// Port serwera POP3
    int port;

    /** Konstruktor `ReadMails` przechowujace dane do logowania oraz odczytywania listy wiadomosci z poczty */
    ReadMails(string serverAddress, string userName, string password, int port = 110);

    /** Struktura `Mail` przechowujace odpowiednie zmienne w celu uzyskania listy wiadomosci */
    struct Mail {
        /// Data otrzymania wiadomosci
        time_t receivedTime;
        /// Nastepujaco: osoba wysylajaca, temat, wiadomosc, typ wiadomosci
        string sender, subject, content, getContentType;
        /// Rozmiar w bajtach [B]
        int sizeInBytes;
        /// Id otrzymanej wiadomosci
        int mailId;
    };

    /** Metoda `getMailInfo()` dzialajaca na powyzszej strukturze zwraca informacje o danej wiadomosci
    * 
    * @param session - sesja na ktorej dzialamy dla protokolu POP3
    * @param messageId - id wiadomosci z ktorej chcemy otrzymac wszystkie niezbedne informacje
    * @result - zwraca nam wszystkie niezbedne informacje o danym mailu przekaza przez `messageId`
    */
    Mail getMailInfo(POP3ClientSession& session, int messageId);

    /** Metoda `downloadLastMails()` dzialajaca na powyzszej strukturze oraz na wektorze zwraca wektor wszystkich wiadomosci
    * 
    * @param numberOfMails - ilosc wiadomosci ktora chcemy zobaczyc
    * @result - zwraca wektor wiadomosci
    */
    vector <Mail> downloadLastMails(int numberOfMails = 3);
};
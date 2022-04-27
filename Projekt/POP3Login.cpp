#include "POP3Login.h"

POP3Login::POP3Login(string serverAddress, string userName, string password, int port) : serverAddress(serverAddress), userName(userName), password(password), port(port) {}

string POP3Login::loginPOP3() {
    try {
        POP3ClientSession session(this->serverAddress, this->port);
        session.login(this->userName, this->password);
        POP3ClientSession::MessageInfoVec messages;
        session.listMessages(messages);
        session.close();
        return "ok";
    }
    catch (const exception& e) {
        return "B³¹d z obs³ug¹ POP3. SprawdŸ poprawnoœæ danych.";
        exit(0);
    }
    catch (const POP3ClientSession& e) {
        return "Przekroczono limit po³¹czeñ: " + to_string(e.getTimeout().milliseconds()) + " ms.";
        exit(1);
    }
    catch (const POP3Exception& e) {
        string what = e.what();
        return "B³¹d z obs³ug¹ POP3. SprawdŸ poprawnoœæ danych.";
        exit(2);
    }
    catch (const NetException& e) {
        string what = e.what();
        return "B³¹d po stronie obs³ugi sieci: " + what;
        exit(3);
    }
}
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

class TCPClient {
public:
    TCPClient();
    ~TCPClient();

    bool connectToServer(const std::string& ip, int port);
    bool sendMessage(const std::string& message);
    std::string receiveMessage();
    void closeConnection();

private:
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server;
};

#endif // TCPCLIENT_H

#include "TCPClient.h"
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

TCPClient::TCPClient() : sock(INVALID_SOCKET) {
    int wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsResult != 0) {
        std::cerr << "WSAStartup failed: " << wsResult << std::endl;
        exit(1);
    }
}

TCPClient::~TCPClient() {
    closesocket(sock);
    WSACleanup();
}

bool TCPClient::connectToServer(const std::string& ip, int port) {
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &server.sin_addr);

    int connResult = connect(sock, (struct sockaddr*)&server, sizeof(server));
    if (connResult == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    return true;
}

bool TCPClient::sendMessage(const std::string& message) {
    int sendResult = send(sock, message.c_str(), message.size(), 0);
    if (sendResult == SOCKET_ERROR) {
        std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    return true;
}

std::string TCPClient::receiveMessage() {
    char buffer[4096];
    ZeroMemory(buffer, 4096);
    int bytesReceived = recv(sock, buffer, 4096, 0);
    if (bytesReceived > 0) {
        return std::string(buffer, 0, bytesReceived);
    }

    return "";
}

void TCPClient::closeConnection() {
    closesocket(sock);
}

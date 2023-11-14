#include "TCPClient.h"
#include <iostream>

#define DEBUG 1

int main() {
    TCPClient client;

    if (client.connectToServer("127.0.0.1", 12345)) {

        client.sendMessage("Hello from the client");

        std::string response = client.receiveMessage();
        std::cout << "Server> " << response << std::endl;
        client.closeConnection();
    }

    return 0;
}

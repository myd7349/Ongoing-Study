#include <iostream>
#include <string>

#include "../../../strutils.hpp"
#include "../../UDPClient.h"


int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    UDPClient serverSocket;
    if (!serverSocket.Bind(12000))
    {
        std::cerr << "Failed to bind to port number 12000.\n";
        return 1;
    }

    char message[16] = "";

    while (true)
    {
        int readSizeInBytes;
        SOCKADDR_IN saClient;

        readSizeInBytes = serverSocket.ReceiveFrom(message, 0, ARRAYSIZE(message), saClient);
        if (readSizeInBytes >= 0)
        {
            std::string sentence(message, message + readSizeInBytes);
            std::cout << "Received [" << sentence << "] from " << inet_ntoa(saClient.sin_addr) << ":" << saClient.sin_port << "\n";

            ToUpperInPlace(sentence);
            serverSocket.SendTo(sentence.c_str(), sentence.length(), saClient);
        }
        else
        {
            std::cout << "Failed to receive message!\n";
            serverSocket.SendTo("", 0, saClient);
        }
    }

    WSACleanup();

    return 0;
}

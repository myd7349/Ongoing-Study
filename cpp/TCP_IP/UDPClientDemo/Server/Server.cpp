#include <cstdlib>
#include <iostream>
#include <string>

#include "../../../strutils.hpp"
#include "../../UDPClient.h"


int main()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        std::cerr << "WSAStartup failed: " << result << '\n';
        return EXIT_FAILURE;
    }

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
        int result;
        SOCKADDR_IN saClient;

        readSizeInBytes = serverSocket.ReceiveFrom(message, 0, ARRAYSIZE(message),
            reinterpret_cast<SOCKADDR &>(saClient), INFINITE);
        if (readSizeInBytes >= 0)
        {
            std::string sentence(message, message + readSizeInBytes);
            std::cout << "Received [" << sentence << "] from " << inet_ntoa(saClient.sin_addr) << ":" << saClient.sin_port << "\n";

            ToUpperInPlace(sentence);
            result = serverSocket.SendTo(sentence.c_str(), sentence.length(),
                reinterpret_cast<const SOCKADDR &>(saClient), 3000);
            if (result < 0)
            {
                std::cerr << "Failed to send message: ";
                if (result == UDPClient::UDP_TIME_OUT)
                    std::cerr << "Time out!\n";
                else if (result == UDPClient::UDP_SOCKET_ERROR)
                    std::cerr << "Socket error!\n";
                else
                    std::cerr << "Unknown error!\n";
            }
        }
        else
        {
            std::cerr << "Failed to receive message: ";
            if (readSizeInBytes == UDPClient::UDP_TIME_OUT)
                std::cerr << "Time out!\n";
            else if (readSizeInBytes == UDPClient::UDP_SOCKET_ERROR)
                std::cerr << "Socket error!\n";
            else
                std::cerr << "Unknown error!\n";
        }
    }

    WSACleanup();

    return 0;
}

#include <iostream>
#include <string>

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

    UDPClient clientSocket;
    clientSocket.Connect("127.0.0.1", 12000);

    char message[16] = "";

    while (true)
    {
        std::cout << "> ";

        std::string sentence;
        if (!std::getline(std::cin, sentence))
            break;

        int result = clientSocket.Send(sentence.c_str(), sentence.length(), INFINITE);
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

        int readSizeInBytes = clientSocket.Receive(message, 0, ARRAYSIZE(message), 2000);
        if (readSizeInBytes >= 0)
            std::cout << "Response from server: [" << std::string(message, readSizeInBytes) << "]\n";
        else if (readSizeInBytes == UDPClient::UDP_TIME_OUT)
            std::cerr << "Time out!\n";
        else if (readSizeInBytes == UDPClient::UDP_SOCKET_ERROR)
            std::cerr << "Socket error!\n";
        else
            std::cerr << "Unknown error!\n";
    }

    WSACleanup();

    return 0;
}

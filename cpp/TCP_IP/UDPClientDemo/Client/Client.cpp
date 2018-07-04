#include <iostream>
#include <string>

#include "../../UDPClient.h"


int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    UDPClient clientSocket;
    clientSocket.Connect("127.0.0.1", 12000);

    char message[16] = "";

    while (true)
    {
        std::cout << "> ";

        std::string sentence;
        if (!std::getline(std::cin, sentence))
            break;

        clientSocket.Send(sentence.c_str(), sentence.length());

        int readSizeInBytes = clientSocket.Receive(message, 0, ARRAYSIZE(message));
        if (readSizeInBytes > 0)
            std::cout << "Response from server: [" << std::string(message, readSizeInBytes) << "]\n";
        else
            std::cout << "No response!\n";
    }

    WSACleanup();

    return 0;
}

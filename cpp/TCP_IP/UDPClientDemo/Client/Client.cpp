#include <iostream>
#include <string>

#include "../../Error.h"
#include "../../UDPClient.h"


int main()
{
    TCP_IP_INIT();

    UDPClient clientSocket;
    clientSocket.Connect("127.0.0.1", 12000);

    // https://github.com/dotnet/runtime/blob/82239a2a0def33c00159c0372226427099cfa355/src/libraries/System.Net.Sockets/src/System/Net/Sockets/UDPClient.cs#L16
    // > private const int MaxUDPSize = 0x10000;
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
            std::cerr << "Failed to send message [" << sentence << "]: ";
            if (result == UDPClient::UDP_TIME_OUT)
                std::cerr << ReportError("Time out!");
            else if (result == UDPClient::UDP_SOCKET_ERROR)
                std::cerr << ReportError("Socket error!");
            else
                std::cerr << ReportError("Unknown error!");
        }

        int readSizeInBytes = clientSocket.Receive(message, 0, ARRAYSIZE(message), 2000);
        if (readSizeInBytes >= 0)
            std::cout << "Response from server: [" << std::string(message, readSizeInBytes) << "]\n";
        else if (readSizeInBytes == UDPClient::UDP_TIME_OUT)
            std::cerr << ReportError("Time out!");
        else if (readSizeInBytes == UDPClient::UDP_SOCKET_ERROR)
            std::cerr << ReportError("Socket error!");
        else
            std::cerr << ReportError("Unknown error!");
    }

    return 0;
}

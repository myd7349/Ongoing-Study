#include <cstdlib>
#include <iostream>
#include <string>

#include "../../../strutils.hpp"
#include "../../Error.h"
#include "../../UDPClient.h"


int main()
{
    TCP_IP_INIT();

    UDPClient serverSocket;
    if (!serverSocket.Bind(12000))
    {
        std::cerr << "Failed to bind to port number 12000.\n";
        return 1;
    }

    // https://github.com/dotnet/runtime/blob/82239a2a0def33c00159c0372226427099cfa355/src/libraries/System.Net.Sockets/src/System/Net/Sockets/UDPClient.cs#L16
    // > private const int MaxUDPSize = 0x10000;
    // #define WSAEMSGSIZE 10040
    char message[16] = "";

    while (true)
    {
        int readSizeInBytes;
        int result;
        struct sockaddr_in saClient;

        readSizeInBytes = serverSocket.ReceiveFrom(message, 0, ARRAYSIZE(message),
            reinterpret_cast<struct sockaddr &>(saClient), INFINITE);
        if (readSizeInBytes >= 0)
        {
            std::string sentence(message, message + readSizeInBytes);
            std::cout << "Received [" << sentence << "] from " << inet_ntoa(saClient.sin_addr) << ":" << saClient.sin_port << "\n";

            ToUpperInPlace(sentence);
            result = serverSocket.SendTo(sentence.c_str(), sentence.length(),
                reinterpret_cast<const struct sockaddr &>(saClient), 3000);
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
        }
        else
        {
            std::cerr << "Failed to receive message: ";
            if (readSizeInBytes == UDPClient::UDP_TIME_OUT)
                std::cerr << ReportError("Time out!");
            else if (readSizeInBytes == UDPClient::UDP_SOCKET_ERROR)
                std::cerr << ReportError("Socket error!");
            else
                std::cerr << ReportError("Unknown error!");
        }
    }

    return 0;
}

#include <iostream>
#include <string>

#include "../../Error.h"
#include "../../UDPClient.h"


int main()
{
    TCP_IP_INIT();

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
            std::cerr << "Failed to send message [" << sentence << "]: ";
            if (result == UDPClient::UDP_TIME_OUT)
                std::cerr << ReportError("Time out!");
            else if (result == UDPClient::UDP_SOCKET_ERROR)
                std::cerr << ReportError("Socket error!");
            else
                std::cerr << ReportError("Unknown error!");
        }

#ifdef USE_MSG_TRUNC
        int readSizeInBytes = clientSocket.Receive(message, ARRAYSIZE(message), MSG_TRUNC, 2000);
#else
        int readSizeInBytes = clientSocket.Receive(message, 0, ARRAYSIZE(message), 2000);
#endif
        if (readSizeInBytes >= 0)
            std::cout << "Response from server: [" << std::string(message, readSizeInBytes) << "]. Receive returns " << readSizeInBytes << ".\n";
        else if (readSizeInBytes == UDPClient::UDP_TIME_OUT)
            std::cerr << ReportError("Time out!");
        else if (readSizeInBytes == UDPClient::UDP_SOCKET_ERROR)
            std::cerr << ReportError("Socket error!");
        else
            std::cerr << ReportError("Unknown error!");
    }

    return 0;
}


// References:
// [getting message length in udp before recvfrom()](https://stackoverflow.com/questions/7448408/getting-message-length-in-udp-before-recvfrom)
// [UDPclient buffer too small](https://stackoverflow.com/questions/24411213/udpclient-buffer-too-small)
// > With UDP you cannot send messages bigger than 64KB. Use TCP, or split the payload yourself into multiple messages which will be extremely complex because messages can be lost.
// https://github.com/sipwise/rtpengine/issues/70
// > UDP packets have a maximum length of 65535 bytes. If the size exceeds the MTU, they get fragmented, not truncated.
// [reading partially from sockets](https://stackoverflow.com/questions/3069204/reading-partially-from-sockets)
// > Each read from UDP socket de-queues one whole datagram off kernel socket receive buffer no matter what's your userland buffer size. That is:
// > - If your buffer is bigger then the next pending datagram, you'll read less then your buffer size.
// > - If your buffer is smaller, you'll read your buffer size worth and the rest of the data is discarded.
// > - You can set MSG_TRUNC option in the flags, so recv(2) will return the whole datagram length, not just the part you read into your userland buffer.
// [using flags MSG_TRUNC , MSG_CTRUNC in UDP socket](https://stackoverflow.com/questions/11863264/using-flags-msg-trunc-msg-ctrunc-in-udp-socket)
// https://linux.die.net/man/2/recvfrom
// https://github.com/dotnet/runtime/blob/82239a2a0def33c00159c0372226427099cfa355/src/libraries/System.Net.Sockets/src/System/Net/Sockets/UDPClient.cs#L16
// > private const int MaxUDPSize = 0x10000;

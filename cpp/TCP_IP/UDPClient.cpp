#include "UDPClient.h"


#pragma comment(lib, "Ws2_32.lib")


const int MIN_PORT_NUMBER = 0x00000000;
const int MAX_PORT_NUMBER = 0x0000FFFF;


UDPClient::UDPClient()
    : socket_(INVALID_SOCKET), isConnected_(false), remoteIP_(0), remotePortNumber_(-1)
{
}


UDPClient::~UDPClient()
{
    Close();
}


bool UDPClient::Bind(int portNumber)
{
    assert(portNumber >= MIN_PORT_NUMBER && portNumber <= MAX_PORT_NUMBER);
    
    if (!CreateSocket())
        return false;

    struct sockaddr_in saLocalAddress = { AF_INET };
    saLocalAddress.sin_port = htons(portNumber);
    saLocalAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    int result = bind(socket_, (const struct sockaddr *)&saLocalAddress, (int)sizeof(struct sockaddr_in));
    return result != SOCKET_ERROR;
}


bool UDPClient::Connect(const char *remoteIP, int portNumber)
{
    return Connect(inet_addr(remoteIP), portNumber);
}


bool UDPClient::Connect(unsigned long remoteIP, int portNumber)
{
    if (isConnected_ && remoteIP_ == remoteIP && remotePortNumber_ == portNumber)
        return true;

    assert(portNumber >= MIN_PORT_NUMBER && portNumber <= MAX_PORT_NUMBER);

    remoteIP_ = remoteIP;
    remotePortNumber_ = portNumber;

    saRemote_.sin_family = AF_INET;
    saRemote_.sin_addr.s_addr = remoteIP_;
    saRemote_.sin_port = htons(portNumber);

    isConnected_ = true;

    return CreateSocket();
}


bool UDPClient::SetSendBufferSize(int sizeInBytes)
{
    if (!CreateSocket())
        return false;

    int result = setsockopt(socket_, SOL_SOCKET, SO_SNDBUF,
        reinterpret_cast<const char *>(&sizeInBytes), sizeof(sizeInBytes));
    assert(result != SOCKET_ERROR);
    return result != SOCKET_ERROR;
}


bool UDPClient::SetReceiveBufferSize(int sizeInBytes)
{
    if (!CreateSocket())
        return false;

    int result = setsockopt(socket_, SOL_SOCKET, SO_RCVBUF,
        reinterpret_cast<const char *>(&sizeInBytes), sizeof(sizeInBytes));
    assert(result != SOCKET_ERROR);
    return result != SOCKET_ERROR;
}


void UDPClient::Close()
{
    if (socket_ != INVALID_SOCKET)
    {
        closesocket(socket_);
        socket_ = INVALID_SOCKET;

        isConnected_ = false;
    }
}


bool UDPClient::CreateSocket()
{
    if (socket_ == INVALID_SOCKET)
        return (socket_ = socket(AF_INET, SOCK_DGRAM, 0)) != INVALID_SOCKET;

    return true;
}


int UDPClient::SendTo(const char *buffer, std::size_t sizeInBytes, const struct sockaddr *to, socklen_t tolen, unsigned timeoutInMs)
{
    assert(IsValid());
    assert(buffer != nullptr && sizeInBytes >= 0);
    assert(to != nullptr && tolen > 0);

    struct timeval timeout = { 0 };
    struct timeval *timeoutPtr = NULL;
    
    if (timeoutInMs != INFINITE)
    {
        timeout.tv_sec = timeoutInMs / 1000;
        timeout.tv_usec = (timeoutInMs % 1000) * 1000;
        timeoutPtr = &timeout;
    }

    fd_set fdWrite = { 0 };
    FD_ZERO(&fdWrite);
    FD_SET(socket_, &fdWrite);

    int result = 1;
    if (timeoutPtr != NULL)
        result = select((int)socket_ + 1, NULL, &fdWrite, NULL, timeoutPtr); // +1 is important here, otherwise you will get a timeout on linux.

    if (result > 0)
    {
        result = sendto(socket_, buffer, static_cast<int>(sizeInBytes), 0, to, tolen);
        if (result == SOCKET_ERROR)
            return UDP_SOCKET_ERROR;

        return result;
    }
    else
    {
        return UDP_TIME_OUT;
    }
}


int UDPClient::ReceiveFrom(char *buffer, std::size_t sizeInBytes, struct sockaddr *from, socklen_t *fromlen, unsigned timeoutInMs)
{
    assert(IsValid());
    assert(buffer != nullptr && sizeInBytes >= 0);
    assert(from != nullptr && fromlen != nullptr);

    struct timeval timeout = { 0 };
    struct timeval *timeoutPtr = NULL;
    
    if (timeoutInMs != INFINITE)
    {
        timeout.tv_sec = timeoutInMs / 1000;
        timeout.tv_usec = (timeoutInMs % 1000) * 1000;
        timeoutPtr = &timeout;
    }

    fd_set fdRead = { 0 };
    FD_ZERO(&fdRead);
    FD_SET(socket_, &fdRead);

    int result = 1;
    if (timeoutPtr != NULL)
        result = select((int)socket_ + 1, &fdRead, NULL, NULL, timeoutPtr);

    if (result > 0)
    {
        result = recvfrom(socket_, buffer, static_cast<int>(sizeInBytes), 0, from, fromlen);
        if (result == SOCKET_ERROR)
            return UDP_SOCKET_ERROR;

        return result;
    }
    else
    {
        return UDP_TIME_OUT;
    }
}


// References:
// corefx:IPEndPoint.cs
// https://stackoverflow.com/questions/1098897/what-is-the-largest-safe-udp-packet-size-on-the-internet
// https://github.com/dotnet/runtime/blob/82239a2a0def33c00159c0372226427099cfa355/src/libraries/System.Net.Sockets/src/System/Net/Sockets/UDPClient.cs#L16
// > private const int MaxUDPSize = 0x10000;
// [Multi-threaded Client/Server Socket Class](https://www.codeproject.com/articles/2477/multi-threaded-client-server-socket-class)
// Beej's Guide to Network Programming Using Internet Sockets
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Net.Sockets/src/System/Net/Sockets/UDPClient.cs
// https://docs.microsoft.com/en-us/windows/win32/winsock/winsock-programming-considerations
// https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-sendto
// [Sockets - How to find out what port and address I'm assigned](https://stackoverflow.com/questions/4046616/sockets-how-to-find-out-what-port-and-address-im-assigned)
// https://linux.die.net/man/2/select
// https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-select
// [Implementing UDP sockets with select in C](https://stackoverflow.com/questions/15592089/implementing-udp-sockets-with-select-in-c)
// [Simple select implementation with UDP in c++](https://stackoverflow.com/questions/26821047/simple-select-implementation-with-udp-in-c)
// > you are passing the socket value as-is to the first parameter of select(),
// > but you actually need to pass s+1 instead if you are monitoring a single
// > socket. The parameter must be set to the highest socket value +1 that is
// > being monitored. On Windows, the parameter is completely ignored, but on
// > other platforms it is actually used, so you have to specify a proper value
// > on non-Windows platforms where a socket is just an index into an array of
// > file descriptors. The parameter represents the highest index in that array
// > where select() cannot access.

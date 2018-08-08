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

    SOCKADDR_IN saLocalAddress = { AF_INET };
    saLocalAddress.sin_port = htons(portNumber);
    saLocalAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    int result = bind(socket_, (SOCKADDR *)&saLocalAddress, sizeof(SOCKADDR));
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
    saRemote_.sin_addr.S_un.S_addr = remoteIP_;
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


int UDPClient::SendTo(const char *buffer, int sizeInBytes, const SOCKADDR *to, int tolen, DWORD timeoutInMs)
{
    assert(IsValid());
    assert(buffer != nullptr && sizeInBytes >= 0);
    assert(to != nullptr && tolen > 0);

    TIMEVAL timeout = { 0 };
    TIMEVAL *timeoutPtr = NULL;
    
    if (timeoutInMs != INFINITE)
    {
        timeout.tv_sec = timeoutInMs / 1000;
        timeout.tv_usec = (timeoutInMs % 1000) * 1000;
        timeoutPtr = &timeout;
    }

    fd_set fdWrite = { 0 };
    FD_SET(socket_, &fdWrite);

    int result = 1;
    if (timeoutPtr != NULL)
        result = select((int)socket_, NULL, &fdWrite, NULL, timeoutPtr);

    if (result > 0)
    {
        result = sendto(socket_, buffer, sizeInBytes, 0, to, tolen);
        if (result == SOCKET_ERROR)
            return UDP_SOCKET_ERROR;

        return result;
    }
    else
    {
        return UDP_TIME_OUT;
    }
}


int UDPClient::ReceiveFrom(char *buffer, int sizeInBytes, SOCKADDR *from, int *fromlen, DWORD timeoutInMs)
{
    assert(IsValid());
    assert(buffer != nullptr && sizeInBytes >= 0);
    assert(from != nullptr && fromlen != nullptr);

    TIMEVAL timeout = { 0 };
    TIMEVAL *timeoutPtr = NULL;
    
    if (timeoutInMs != INFINITE)
    {
        timeout.tv_sec = timeoutInMs / 1000;
        timeout.tv_usec = (timeoutInMs % 1000) * 1000;
        timeoutPtr = &timeout;
    }

    fd_set fdRead = { 0 };
    FD_SET(socket_, &fdRead);

    int result = 1;
    if (timeoutPtr != NULL)
        result = select((int)socket_, &fdRead, NULL, NULL, timeoutPtr);

    if (result > 0)
    {
        result = recvfrom(socket_, buffer, sizeInBytes, 0, from, fromlen);
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
// [Multi-threaded Client/Server Socket Class](https://www.codeproject.com/articles/2477/multi-threaded-client-server-socket-class)
// Beej's Guide to Network Programming Using Internet Sockets

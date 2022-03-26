#include "Socket.h"

#if defined(_WIN32)
#pragma comment(lib, "Ws2_32.lib")
#endif

const int MIN_PORT_NUMBER = 0x00000000;
const int MAX_PORT_NUMBER = 0x0000FFFF;


Socket::Socket()
    : socket_(INVALID_SOCKET), isConnected_(false), remotePortNumber_(-1)
{
}


Socket::Socket(int domain, int type)
    : socket_(INVALID_SOCKET), isConnected_(false), remotePortNumber_(-1)
{
	Create(domain, type);
}


Socket::~Socket()
{
    Close();
}


bool Socket::Create(int domain, int type)
{
    if (socket_ == INVALID_SOCKET)
        return (socket_ = socket(domain, type, 0)) != INVALID_SOCKET;

    return true;
}


void Socket::Close()
{
    if (socket_ != INVALID_SOCKET)
    {
        closesocket(socket_);
        socket_ = INVALID_SOCKET;

        isConnected_ = false;
    }
}


bool Socket::Bind(int portNumber)
{
    assert(IsValid());
    assert(portNumber >= MIN_PORT_NUMBER && portNumber <= MAX_PORT_NUMBER);

    struct sockaddr_in saLocalAddress = { AF_INET };
    saLocalAddress.sin_port = htons(portNumber);
    saLocalAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    int result = bind(socket_, (const struct sockaddr *)&saLocalAddress, (int)sizeof(struct sockaddr_in));
    return result != SOCKET_ERROR;
}


bool Socket::Connect(const char *remoteIP, int portNumber)
{
    return Connect(inet_addr(remoteIP), portNumber);
}


bool Socket::Connect(unsigned long remoteIP, int portNumber)
{
    assert(IsValid());

    if (isConnected_ &&
        saRemote_.sin_addr.s_addr == remoteIP &&
        remotePortNumber_ == portNumber)
        return true;

    assert(portNumber >= MIN_PORT_NUMBER && portNumber <= MAX_PORT_NUMBER);

    saRemote_.sin_family = AF_INET;
    saRemote_.sin_addr.s_addr = remoteIP;
    saRemote_.sin_port = htons(portNumber);

    remotePortNumber_ = portNumber;

    isConnected_ = connect(socket_,
        reinterpret_cast<const struct sockaddr *>(&saRemote_), static_cast<socklen_t>(sizeof(saRemote_))) == 0;

    return isConnected_;
}


bool Socket::Disconnect()
{
    assert(IsValid());

    bzero(&saRemote_, sizeof(saRemote_));
    saRemote_.sin_family = AF_UNSPEC;
    isConnected_ = false;

    return connect(socket_, reinterpret_cast<const struct sockaddr *>(&saRemote_), static_cast<socklen_t>(sizeof(saRemote_))) == 0;
}


bool Socket::SetSendBufferSize(int sizeInBytes)
{
    assert(IsValid());

    int result = setsockopt(socket_, SOL_SOCKET, SO_SNDBUF,
        reinterpret_cast<const char *>(&sizeInBytes), sizeof(sizeInBytes));
    assert(result != SOCKET_ERROR);
    return result != SOCKET_ERROR;
}


bool Socket::SetReceiveBufferSize(int sizeInBytes)
{
    assert(IsValid());

    int result = setsockopt(socket_, SOL_SOCKET, SO_RCVBUF,
        reinterpret_cast<const char *>(&sizeInBytes), sizeof(sizeInBytes));
    assert(result != SOCKET_ERROR);
    return result != SOCKET_ERROR;
}


int Socket::Send(const char *buffer, std::size_t sizeInBytes, unsigned timeoutInMs)
{
    assert(IsValid());
    assert(buffer != nullptr && sizeInBytes >= 0);
    assert(isConnected_);

#if defined(INFINITE)
    assert(timeoutInMs != INFINITE);
#endif

    struct timeval timeout = { 0 };
    timeout.tv_sec = timeoutInMs / 1000;
    timeout.tv_usec = (timeoutInMs % 1000) * 1000;

    fd_set fdWrite = { 0 };
    FD_ZERO(&fdWrite);
    FD_SET(socket_, &fdWrite);

    int result = select((int)socket_ + 1, NULL, &fdWrite, NULL,
                        &timeout);  // +1 is important here, otherwise you will
                                   // get a timeout on linux.

    if (result > 0)
    {
        result = send(socket_, buffer, static_cast<int>(sizeInBytes), 0);
        if (result == SOCKET_ERROR)
            return Error;

        return result;
    }
    else
    {
        return Timeout;
    }
}


int Socket::SendTo(const char *buffer, std::size_t sizeInBytes, const struct sockaddr *to, socklen_t tolen, unsigned timeoutInMs)
{
    assert(IsValid());
    assert(buffer != nullptr && sizeInBytes >= 0);

#if defined(INFINITE)
    assert(timeoutInMs != INFINITE);
#endif

    struct timeval timeout = { 0 };
    timeout.tv_sec = timeoutInMs / 1000;
    timeout.tv_usec = (timeoutInMs % 1000) * 1000;

    fd_set fdWrite = { 0 };
    FD_ZERO(&fdWrite);
    FD_SET(socket_, &fdWrite);

    int result = select((int)socket_ + 1, NULL, &fdWrite, NULL, &timeout); // +1 is important here, otherwise you will get a timeout on linux.

    if (result > 0)
    {
        result = sendto(socket_, buffer, static_cast<int>(sizeInBytes), 0, to, tolen);
        if (result == SOCKET_ERROR)
            return Error;

        return result;
    }
    else
    {
        return Timeout;
    }
}


int Socket::Receive(char *buffer, std::size_t sizeInBytes, int flags, unsigned timeoutInMs)
{
    assert(IsValid());
    assert(buffer != nullptr && sizeInBytes >= 0);
    assert(isConnected_);

#if defined(INFINITE)
    assert(timeoutInMs != INFINITE);
#endif

    struct timeval timeout = { 0 };
    timeout.tv_sec = timeoutInMs / 1000;
    timeout.tv_usec = (timeoutInMs % 1000) * 1000;

    fd_set fdRead = { 0 };
    FD_ZERO(&fdRead);
    FD_SET(socket_, &fdRead);

    int result = select((int)socket_ + 1, &fdRead, NULL, NULL, &timeout);

    if (result > 0)
    {
        result = recv(socket_, buffer, static_cast<int>(sizeInBytes), 0);
        if (result == SOCKET_ERROR)
            return Error;

        return result;
    }
    else
    {
        return Timeout;
    }
}


int Socket::ReceiveFrom(char *buffer, std::size_t sizeInBytes, int flags, struct sockaddr *from, socklen_t *fromlen, unsigned timeoutInMs)
{
    assert(IsValid());
    assert(buffer != nullptr && sizeInBytes >= 0);

#if defined(INFINITE)
    assert(timeoutInMs != INFINITE);
#endif

    struct timeval timeout = { 0 };
    timeout.tv_sec = timeoutInMs / 1000;
    timeout.tv_usec = (timeoutInMs % 1000) * 1000;

    fd_set fdRead = { 0 };
    FD_ZERO(&fdRead);
    FD_SET(socket_, &fdRead);

    int result = select((int)socket_ + 1, &fdRead, NULL, NULL, &timeout);

    if (result > 0)
    {
        result = recvfrom(socket_, buffer, static_cast<int>(sizeInBytes), flags, from, fromlen);
        if (result == SOCKET_ERROR)
            return Error;

        return result;
    }
    else
    {
        return Timeout;
    }
}


// References:
// corefx:IPEndPoint.cs
// https://stackoverflow.com/questions/1098897/what-is-the-largest-safe-udp-packet-size-on-the-internet
// https://github.com/dotnet/runtime/blob/82239a2a0def33c00159c0372226427099cfa355/src/libraries/System.Net.Sockets/src/System/Net/Sockets/Socket.cs#L16
// > private const int MaxUDPSize = 0x10000;
// [Multi-threaded Client/Server Socket Class](https://www.codeproject.com/articles/2477/multi-threaded-client-server-socket-class)
// Beej's Guide to Network Programming Using Internet Sockets
// https://github.com/dotnet/runtime/blob/main/src/libraries/System.Net.Sockets/src/System/Net/Sockets/Socket.cs
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
// [getting message length in udp before recvfrom()](https://stackoverflow.com/questions/7448408/getting-message-length-in-udp-before-recvfrom)
// [Socket buffer too small](https://stackoverflow.com/questions/24411213/Socket-buffer-too-small)
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
// https://github.com/dotnet/runtime/blob/82239a2a0def33c00159c0372226427099cfa355/src/libraries/System.Net.Sockets/src/System/Net/Sockets/Socket.cs#L16
// > private const int MaxUDPSize = 0x10000;
// [Can I be sure that a UDP recv executed immediately after a successfull call to recv with MSG_PEEK will not block?](https://stackoverflow.com/questions/44317781/can-i-be-sure-that-a-udp-recv-executed-immediately-after-a-successfull-call-to-r)
// [UDP Socket Set Timeout](https://stackoverflow.com/questions/13547721/udp-socket-set-timeout)
// [Why timeout is needed for UDP send when UDP is connectionless?](https://stackoverflow.com/questions/19736590/why-timeout-is-needed-for-udp-send-when-udp-is-connectionless)
// https://github.com/KMakowsky/Socket.cpp
// https://github.com/ReneNyffenegger/Socket.cpp
// https://www.cin.ufpe.br/~mvpm/socket/sockets.html
// https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/Socket_cpp/index
// https://renenyffenegger.ch/notes/web/webserver/cpp/simple/index
// https://www.codeproject.com/Articles/7108/A-light-weighted-client-server-socket-class-in-C
// https://github.com/mahilab/mahi-com/blob/master/include/Mahi/Com/Socket.hpp
// https://github.com/SFML/SFML/blob/master/include/SFML/Network/Socket.hpp
// https://gafferongames.com/post/sending_and_receiving_packets/
// https://github.com/ThisIsRobokitty/netgame
// https://github.com/libsdl-org/SDL_net

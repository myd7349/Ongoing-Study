// 2018-07-04T12:31+08:00
#ifndef UDP_CLIENT_H_
#define UDP_CLIENT_H_

#include "Platform.h"

#ifndef UDPCLIENT_API
#ifdef UDPCLIENT_EXPORTS
#define UDPCLIENT_API PLATFORM_EXPORT
#else
#define UDPCLIENT_API PLATFORM_IMPORT
#endif
#endif


class UDPClient
{
public:
    enum ErrorCode
    {
        UDP_SOCKET_ERROR = SOCKET_ERROR,
        UDP_TIME_OUT     = -2
    };

    UDPClient();
    ~UDPClient();

    bool CreateSocket();
    void Close();

    socket_t GetSocket() const
    {
        return socket_;
    }

    bool IsValid() const
    {
        return socket_ != INVALID_SOCKET;        
    }

    bool Bind(int portNumber);
    bool Connect(const char *remoteIP, int portNumber);
    bool Connect(unsigned long remoteIP, int portNumber);
    bool Disconnect();

    // TODO: SetSocketOption
    bool SetSendBufferSize(int sizeInBytes);
    bool SetReceiveBufferSize(int sizeInBytes);

    int Send(const char *buffer, std::size_t sizeInBytes)
    {
        return send(socket_, buffer, static_cast<int>(sizeInBytes), 0);
    }

    int Send(const char *buffer, std::size_t sizeInBytes, unsigned timeoutInMs);

    template <int N>
    int Send(const char (&buffer)[N], unsigned timeoutInMs)
    {
        return Send(buffer, N, timeoutInMs);
    }

    int SendTo(const char *buffer, std::size_t sizeInBytes, const struct sockaddr_in &saRemote)
    {
        return sendto(
            socket_,
            buffer, static_cast<int>(sizeInBytes),
            0,
            reinterpret_cast<const struct sockaddr *>(&saRemote), (socklen_t)sizeof(saRemote));
    }

    int SendTo(const char *buffer, std::size_t sizeInBytes, const struct sockaddr_in &saRemote, unsigned timeoutInMs)
    {
        return SendTo(buffer, sizeInBytes, reinterpret_cast<const struct sockaddr *>(&saRemote), (socklen_t)sizeof(saRemote), timeoutInMs);
    }

    template <int N>
    int SendTo(const char (&buffer)[N], const struct sockaddr_in &saRemote, unsigned timeoutInMs)
    {
        return SendTo(buffer, N, saRemote, timeoutInMs);
    }

    int Receive(char *buffer, std::size_t sizeInBytes)
    {
        return recv(socket_, buffer, static_cast<int>(sizeInBytes), 0);
    }

    int Receive(char *buffer, std::size_t sizeInBytes, int flags, unsigned timeoutInMs);

    int Receive(char *buffer, std::size_t sizeInBytes, unsigned timeoutInMs)
    {
        assert(isConnected_);
        return Receive(buffer, sizeInBytes, 0, timeoutInMs);
    }

    template <int N>
    int Receive(char (&buffer)[N], int offset, std::size_t bytes, unsigned timeoutInMs)
    {
        return Receive(buffer + offset, bytes, timeoutInMs);
    }

    int ReceiveFrom(char *buffer, std::size_t sizeInBytes, struct sockaddr_in &saRemote)
    {
        socklen_t addressLength = (socklen_t)sizeof(saRemote);
        return recvfrom(
            socket_,
            buffer, static_cast<int>(sizeInBytes),
            0,
            reinterpret_cast<struct sockaddr *>(&saRemote), &addressLength);
    }

    int ReceiveFrom(char *buffer, std::size_t sizeInBytes, struct sockaddr_in &saRemote, unsigned timeoutInMs)
    {
        socklen_t addressLength = (socklen_t)sizeof(saRemote);
        return ReceiveFrom(buffer, sizeInBytes, 0, reinterpret_cast<struct sockaddr *>(&saRemote), &addressLength, timeoutInMs);
    }

    int ReceiveFrom(char *buffer, std::size_t sizeInBytes, int flags, struct sockaddr_in &saRemote, unsigned timeoutInMs)
    {
        socklen_t addressLength = (socklen_t)sizeof(saRemote);
        return ReceiveFrom(buffer, sizeInBytes, flags, reinterpret_cast<struct sockaddr *>(&saRemote), &addressLength, timeoutInMs);
    }

    template <int N>
    int ReceiveFrom(char (&buffer)[N], int offset, std::size_t bytes, struct sockaddr_in &saRemote, unsigned timeoutInMs)
    {
        assert(offset >= 0 && offset < N);
        assert(bytes > 0 && offset + bytes <= N);
        return ReceiveFrom(buffer + offset, bytes, saRemote, timeoutInMs);
    }

private:
    UDPClient(const UDPClient &);
    UDPClient &operator=(const UDPClient &);

    int SendTo(const char *buffer, std::size_t sizeInBytes, const struct sockaddr *to, socklen_t tolen, unsigned timeoutInMs);
    int ReceiveFrom(char *buffer, std::size_t sizeInBytes, int flags, struct sockaddr *from, socklen_t *fromlen, unsigned timeoutInMs);

    socket_t           socket_;
    bool               isConnected_;
    struct sockaddr_in saRemote_;
    int                remotePortNumber_;
};

#endif // UDP_CLIENT_H_

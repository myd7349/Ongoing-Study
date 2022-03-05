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

    bool Bind(int portNumber);
    bool Connect(const char *remoteIP, int portNumber);
    bool Connect(unsigned long remoteIP, int portNumber);
    
    bool IsValid() const
    {
        return socket_ != INVALID_SOCKET;        
    }

    socket_t GetSocket() const
    {
        return socket_;
    }

    int SendTo(const char *buffer, std::size_t sizeInBytes, const struct sockaddr &saRemote, unsigned timeoutInMs)
    {
        return SendTo(buffer, sizeInBytes, &saRemote, sizeof(struct sockaddr), timeoutInMs);
    }

    int ReceiveFrom(char *buffer, std::size_t sizeInBytes, struct sockaddr &saRemote, unsigned timeoutInMs)
    {
        socklen_t readSizeInBytes = (socklen_t)sizeof(struct sockaddr);
        return ReceiveFrom(buffer, sizeInBytes, &saRemote, &readSizeInBytes, timeoutInMs);
    }

    template <int N>
    int SendTo(const char (&buffer)[N], const struct sockaddr &saRemote, unsigned timeoutInMs)
    {
        return SendTo(buffer, N, saRemote, timeoutInMs);
    }

    template <int N>
    int ReceiveFrom(char (&buffer)[N], int offset, std::size_t bytes, struct sockaddr &saRemote, unsigned timeoutInMs)
    {
        assert(offset >= 0 && offset < N);
        assert(bytes > 0 && offset + bytes <= N);
        return ReceiveFrom(buffer + offset, bytes, saRemote, timeoutInMs);
    }

    int Send(const char *buffer, std::size_t sizeInBytes, unsigned timeoutInMs)
    {
        assert(isConnected_);
        return SendTo(buffer, sizeInBytes, reinterpret_cast<const struct sockaddr *>(&saRemote_), (socklen_t)sizeof(struct sockaddr), timeoutInMs);
    }

    int Receive(char *buffer, std::size_t sizeInBytes, unsigned timeoutInMs)
    {
        assert(isConnected_);
        socklen_t readSizeInBytes = (socklen_t)sizeof(struct sockaddr);
        return ReceiveFrom(buffer, sizeInBytes, reinterpret_cast<struct sockaddr *>(&saRemote_), &readSizeInBytes, timeoutInMs);
    }

    template <int N>
    int Send(const char (&buffer)[N], unsigned timeoutInMs)
    {
        return Send(buffer, N, timeoutInMs);
    }

    template <int N>
    int Receive(char (&buffer)[N], int offset, std::size_t bytes, unsigned timeoutInMs)
    {
        return Receive(buffer + offset, bytes, timeoutInMs);
    }

    // TODO: SetSocketOption
    bool SetSendBufferSize(int sizeInBytes);
    bool SetReceiveBufferSize(int sizeInBytes);

    void Close();

private:
    UDPClient(const UDPClient &);
    UDPClient &operator=(const UDPClient &);

    bool CreateSocket();

    int SendTo(const char *buffer, std::size_t sizeInBytes, const struct sockaddr *to, socklen_t tolen, unsigned timeoutInMs);
    int ReceiveFrom(char *buffer, std::size_t sizeInBytes, struct sockaddr *from, socklen_t *fromlen, unsigned timeoutInMs);

    socket_t           socket_;
    bool               isConnected_;
    unsigned long      remoteIP_;
    int                remotePortNumber_;
    struct sockaddr_in saRemote_;
};

#endif // UDP_CLIENT_H_

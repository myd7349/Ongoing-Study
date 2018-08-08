// 2018-07-04T12:31+08:00
#ifndef UDP_CLIENT_H_
#define UDP_CLIENT_H_

#include <cassert>

#include <WinSock2.h>


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

    SOCKET GetSocket() const
    {
        return socket_;
    }

    int SendTo(const char *buffer, int sizeInBytes, const SOCKADDR &saRemote, DWORD timeoutInMs)
    {
        return SendTo(buffer, sizeInBytes, &saRemote, sizeof(SOCKADDR), timeoutInMs);
    }

    int ReceiveFrom(char *buffer, int sizeInBytes, SOCKADDR &saRemote, DWORD timeoutInMs)
    {
        int readSizeInBytes = sizeof(SOCKADDR);
        return ReceiveFrom(buffer, sizeInBytes, &saRemote, &readSizeInBytes, timeoutInMs);
    }

    template <int N>
    int SendTo(const char (&buffer)[N], const SOCKADDR &saRemote, DWORD timeoutInMs)
    {
        return SendTo(buffer, N, saRemote, timeoutInMs);
    }

    template <int N>
    int ReceiveFrom(char (&buffer)[N], int offset, int bytes, SOCKADDR &saRemote, DWORD timeoutInMs)
    {
        assert(offset >= 0 && offset < N);
        assert(bytes > 0 && offset + bytes <= N);
        return ReceiveFrom(buffer + offset, bytes, saRemote, timeoutInMs);
    }

    int Send(const char *buffer, int sizeInBytes, DWORD timeoutInMs)
    {
        assert(isConnected_);
        return SendTo(buffer, sizeInBytes, reinterpret_cast<const SOCKADDR *>(&saRemote_), sizeof(SOCKADDR), timeoutInMs);
    }

    int Receive(char *buffer, int sizeInBytes, DWORD timeoutInMs)
    {
        assert(isConnected_);
        int readSizeInBytes = sizeof(SOCKADDR);
        return ReceiveFrom(buffer, sizeInBytes, reinterpret_cast<SOCKADDR *>(&saRemote_), &readSizeInBytes, timeoutInMs);
    }

    template <int N>
    int Send(const char (&buffer)[N], DWORD timeoutInMs)
    {
        return Send(buffer, N, timeoutInMs);
    }

    template <int N>
    int Receive(char (&buffer)[N], int offset, int bytes, DWORD timeoutInMs)
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

    int SendTo(const char *buffer, int sizeInBytes, const SOCKADDR *to, int tolen, DWORD timeoutInMs);
    int ReceiveFrom(char *buffer, int sizeInBytes, SOCKADDR *from, int *fromlen, DWORD timeoutInMs);

    SOCKET        socket_;
    bool          isConnected_;
    unsigned long remoteIP_;
    int           remotePortNumber_;
    SOCKADDR_IN   saRemote_;
};

#endif // UDP_CLIENT_H_

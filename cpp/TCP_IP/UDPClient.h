// 2018-07-04T12:31+08:00
#ifndef UDP_CLIENT_H_
#define UDP_CLIENT_H_

#include <cassert>

#include <WinSock2.h>


class UDPClient
{
public:
    UDPClient();
    ~UDPClient();

    bool Bind(int portNumber);
    bool Connect(const char *remoteIP, int portNumber);
    bool Connect(unsigned long remoteIP, int portNumber);

    int SendTo(const char *buffer, int sizeInBytes, const SOCKADDR_IN &saRemote)
    {
        return SendTo(buffer, sizeInBytes, reinterpret_cast<const SOCKADDR *>(&saRemote), sizeof(SOCKADDR));
    }

    int ReceiveFrom(char *buffer, int sizeInBytes, SOCKADDR_IN &saRemote)
    {
        int readSizeInBytes = sizeof(SOCKADDR);
        return ReceiveFrom(buffer, sizeInBytes, reinterpret_cast<SOCKADDR *>(&saRemote), &readSizeInBytes);
    }

    template <int N>
    int SendTo(const char (&buffer)[N], const SOCKADDR_IN &saRemote)
    {
        return SendTo(buffer, N, saRemote);
    }

    template <int N>
    int ReceiveFrom(char (&buffer)[N], int offset, int bytes, SOCKADDR_IN &saRemote)
    {
        assert(offset >= 0 && offset < N);
        assert(bytes > 0 && offset + bytes <= N);
        return ReceiveFrom(buffer + offset, bytes, saRemote);
    }

    int Send(const char *buffer, int sizeInBytes)
    {
        assert(isConnected_);
        return SendTo(buffer, sizeInBytes, reinterpret_cast<const SOCKADDR *>(&saRemote_), sizeof(SOCKADDR));
    }

    int Receive(char *buffer, int sizeInBytes)
    {
        assert(isConnected_);
        int readSizeInBytes = sizeof(SOCKADDR);
        return ReceiveFrom(buffer, sizeInBytes, reinterpret_cast<SOCKADDR *>(&saRemote_), &readSizeInBytes);
    }

    template <int N>
    int Send(const char (&buffer)[N])
    {
        return SendTo(buffer, N, saRemote_);
    }

    template <int N>
    int Receive(char (&buffer)[N], int offset, int bytes)
    {
        assert(offset >= 0 && offset < N);
        assert(bytes > 0 && offset + bytes <= N);
        return ReceiveFrom(buffer + offset, bytes, saRemote_);
    }

    // TODO: SetSocketOption
    bool SetSendBufferSize(int sizeInBytes);
    bool SetReceiveBufferSize(int sizeInBytes);

    void Close();

private:
    UDPClient(const UDPClient &);
    UDPClient &operator=(const UDPClient &);

    bool CreateSocket();

    int SendTo(const char *buffer, int sizeInBytes, const SOCKADDR *to, int tolen);
    int ReceiveFrom(char *buffer, int sizeInBytes, SOCKADDR *from, int *fromlen);

    SOCKET        socket_;
    bool          isConnected_;
    unsigned long remoteIP_;
    int           remotePortNumber_;
    SOCKADDR_IN   saRemote_;
};

#endif // UDP_CLIENT_H_

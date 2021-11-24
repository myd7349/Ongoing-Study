#include <stdlib.h>

#include <ifaddrs.h>
#include <linux/if_link.h>
#include <linux/wireless.h>
#include <sys/ioctl.h>

#include "tcpip.h"


const char *family_to_str(int family)
{
    switch (family)
    {
    case AF_INET: return "AF_INET"; break;
    case AF_INET6: return "AF_INET6"; break;
    case AF_PACKET: return "AF_PACKET"; break;
    default: return "<unknown>"; break;
    }
}


// https://gist.github.com/edufelipe/6108057
int check_wireless(const char* ifname, char* protocol)
{
    int sock = -1;
    struct iwreq pwrq;
    memset(&pwrq, 0, sizeof(pwrq));
    strncpy(pwrq.ifr_name, ifname, IFNAMSIZ);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        print_error_ex("socket");
        return 0;
    }

    if (ioctl(sock, SIOCGIWNAME, &pwrq) != -1)
    {
        if (protocol)
            strncpy(protocol, pwrq.u.name, IFNAMSIZ);
        close(sock);
        return 1;
    }

    close(sock);
    return 0;
}


int main(void)
{
    struct ifaddrs *addrs;
    struct ifaddrs *current;
    struct sockaddr_in *sa;
    int family;
    char *addr;
    int index = 0;
    int result;
    char host[NI_MAXHOST];
    struct rtnl_link_stats *stats;
    char protocol[IFNAMSIZ]  = {0};

    if (getifaddrs(&addrs) == -1)
    {
        print_error_ex("getifaddrs");
        return EXIT_FAILURE;
    }

    for (current = addrs; current != NULL; current = current->ifa_next)
    {
        if (current->ifa_addr == NULL)
            continue;

        sa = (struct sockaddr_in *)current->ifa_addr;
        family = current->ifa_addr->sa_family;

        printf("#%d ---------------------\n", ++index);

        printf("\tName: %s\n", current->ifa_name);
        printf("\tFamily: %s\n", family_to_str(family));

        if (family == AF_INET || family == AF_INET6)
        {
            result = getnameinfo(
                current->ifa_addr,
                (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
                host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (result != 0)
            {
                print_error_ex("getnameinfo");
            }
            else
            {
                printf("\tAddress: %s\n", host);
                if (family == AF_INET)
                    printf("\tAddress(inet_ntoa): %s\n", inet_ntoa(sa->sin_addr));
            }

            if (check_wireless(current->ifa_name, protocol))
                printf("\tWireless: true, Protocol: %s\n", protocol);
            else
                printf("\tWireless: false\n");
        }
        else if (family == AF_PACKET)
        {
            stats = current->ifa_data;
            if (stats != NULL)
            {
                printf(
                    "\ttx_packets = %10u; rx_packets = %10u\n"
                    "\ttx_bytes   = %10u; rx_bytes   = %10u\n",
                    stats->tx_packets, stats->rx_packets,
                    stats->tx_bytes, stats->rx_bytes);
            }
        }
    }

    freeifaddrs(addrs);

    return 0;
}


// References:
// [How can I get to know the IP address for interfaces in C?](https://stackoverflow.com/questions/4139405/how-can-i-get-to-know-the-ip-address-for-interfaces-in-c)
// [is_wireless.c](https://gist.github.com/edufelipe/6108057)
// [Porting getifaddrs to Win XP](https://stackoverflow.com/questions/3069082/porting-getifaddrs-to-win-xp)
// [GetAdaptersAddresses function (iphlpapi.h)](https://docs.microsoft.com/en-us/windows/win32/api/iphlpapi/nf-iphlpapi-getadaptersaddresses)
// https://github.com/apple/cups/blob/master/cups/getifaddrs-internal.h
// https://github.com/apple/cups/blob/master/cups/getifaddrs.c
// https://github.com/steve-o/openpgm/blob/master/openpgm/pgm/getifaddrs.c
// [Alternative to gethostbyname](https://stackoverflow.com/questions/6638580/alternative-to-gethostbyname)
// http://beej.us/guide/bgnet/html/
// https://github.com/steve-o/openpgm/blob/master/openpgm/pgm/getifaddrs.c
// https://man7.org/linux/man-pages/man3/getifaddrs.3.html
// https://linux.die.net/man/3/getifaddrs
// [bind socket to network interface](https://stackoverflow.com/questions/14478167/bind-socket-to-network-interface)

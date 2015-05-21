// 2015-05-20T17:55+08:00
#include <iostream>
#include <vector>

#include "serial/serial.h" // https://github.com/wjwwood/serial

#ifdef _MSC_VER
# pragma comment(lib, "serial.lib")
#endif

int main()
{
    std::vector<serial::PortInfo> ports = serial::list_ports();
    for (std::vector<serial::PortInfo>::const_iterator it = ports.cbegin();
        it != ports.cend(); ++it) {
        std::cout << it->port << '\t' << it->hardware_id << '\t' << it->description << std::endl;
    }

    std::system("pause");

    return 0;
}
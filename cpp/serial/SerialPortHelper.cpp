#define SERIAL_API __declspec(dllexport)
#include "SerialPortHelper.h"

#include <algorithm>
#include <cassert>
#include <regex>
#include <string>
#include <vector>

#include <serial/serial.h>


int PortNumber(const std::string &port)
{
    std::regex re("COM(\\d+)");
    std::smatch matchResults;

    std::regex_match(port.cbegin(), port.cend(), matchResults, re);
    if (matchResults.size() == 2)
    {
        return std::stoi(matchResults[1]);
    }

    return -1;
}

int GetSerialPortNumber(const char *desc)
{
    assert(desc != NULL);

    std::vector<serial::PortInfo> ports = serial::list_ports();
    if (ports.empty())
    {
        return -1;
    }

    std::vector<serial::PortInfo>::const_iterator it = std::find_if(ports.cbegin(), ports.cend(), 
        [&desc](const serial::PortInfo &portInfo) -> bool
        {
            return portInfo.description.find(desc) != std::string::npos;
        });

    if (it != ports.cend())
    {
        return PortNumber(it->port);
    }
    else
    {
        return -1;
    }
}
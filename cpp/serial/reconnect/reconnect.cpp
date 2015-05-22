// 2015-05-21T15:17+08:00
// Demonstrates how to reconnect to a serial port once the device was unplugged and then plugged back.
//
// Firstly, connect the device to the PC. Start this program. And some stuff is dumped out.
// Then, plug out the device and wait a while. In the meantime, see how the output changes.
// Finally, reconnect the device and see the output.
// 
// Each time you run this program, please try to use a different `OPERATION_DELAY` and
// see how it will influence the behaviour of this program. For example, try 10 and 200 separately.
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "serial/serial.h" // https://github.com/wjwwood/serial

#include "../../common.h"

#ifdef _MSC_VER
# pragma comment(lib, "serial.lib")
#endif

#ifdef _WIN32
# include <windows.h>
# define sleepMS(ms) Sleep(ms)
#else
# error Not implemented yet!
#endif

std::string GetDevicePort()
{
    std::vector<serial::PortInfo> ports = serial::list_ports();
    auto it = std::find_if(ports.cbegin(), ports.cend(), 
        [](const serial::PortInfo &portInfo) ->bool
        {
            std::string description = "Silicon Labs CP210x USB to UART Bridge";
            return portInfo.description.substr(0, description.length()) == description; 
        });
    if (it != ports.cend()) {
        return it->port;
    } else {
        return "";
    }
}

int main(int argc, char *argv[])
{
    // Try to change the value of `OPERATION_DELAY` and see how the behavior of this program changes.
#ifndef NDEBUG
    const int OPERATION_DELAY(200);
#else
    int OPERATION_DELAY;
    if (argc < 2) {
        OPERATION_DELAY = 200;
    } else {
        try {
            OPERATION_DELAY = std::stoi(argv[1]);
        } catch (...) {
            OPERATION_DELAY = 200;
        }
    }
#endif

    std::unique_ptr<serial::Serial> serialPtr = nullptr;
    try {
        serialPtr = std::unique_ptr<serial::Serial>(new serial::Serial(GetDevicePort(), 576000));
    } catch (const std::exception &e) {
        RETURN_ON_FAILURE();
    }

    serial::Serial &serialPort = *serialPtr;

    std::function<void (std::uint8_t b0, std::uint8_t b1)> sendTwoBytesCommand = 
        [&](std::uint8_t b0, std::uint8_t b1)
        {
            std::uint8_t command[] = {b0, b1};
            if (serialPort.isOpen()) {
                serialPort.write(command, 2);
            }
        };
    std::function<void ()> start  = std::bind(sendTwoBytesCommand, 0xAA, 0xAA);
    std::function<void ()> stop   = std::bind(sendTwoBytesCommand, 0xBB, 0xBB);
    std::function<void ()> getVer = std::bind(sendTwoBytesCommand, 0xCC, 0xCC);

    std::function<void ()> reopen = [&]() 
    {
        serialPort.close();

        serialPort.open();
        if (serialPort.isOpen()) {
            std::uint8_t version[3] = {0};

            try {
                // Send a command to get the version of our device
                getVer();
                // Receive version information
                std::size_t len = serialPort.read(version, ARRAYSIZE(version));
                if (len != ARRAYSIZE(version) || version[0] != 0x50) {
                    serialPort.close();
                }
            } catch (...) {
                serialPort.close();
            }
        }
    };

    while (true) {
        try {
            if (!serialPort.isOpen()) {
                putchar('.');
                reopen();

                // *** Important
                sleepMS(OPERATION_DELAY);
            } else {
                getVer();

                std::uint8_t version[3];
                std::size_t len = serialPort.read(version, ARRAYSIZE(version));
                if (len == ARRAYSIZE(version) && version[0] == 0x50) {
                    std::printf("%#02x %#02x %#02x\n", version[0], version[1], version[2]);
                }

                // *** Important
                sleepMS(OPERATION_DELAY);
            }
        } catch (...) {
            serialPort.close();
        }
    }

    PAUSE();
    return 0;
}
// References:
// [C read call blocking on serial port operation](http://stackoverflow.com/questions/7396255/c-read-call-blocking-on-serial-port-operation)
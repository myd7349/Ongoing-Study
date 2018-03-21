// 2018-03-21T11:55+08:00
#include <array>
#include <iostream>
#include <string>
#include <thread>

#include "channel.hpp"


const int BUFFER_SIZE = 6;

struct Args
{
    Channel A2B;
    Channel B2C;
    Channel C2M;
    std::string log;
};


void StepA(Args &args)
{
    std::cout << "-------- Step A --------\n";

    std::string msg = "Step A finished!\n";
    args.log = msg;
    args.A2B.Send(msg.c_str(), msg.length());
}


void StepB(Args &args)
{
    std::array<char, BUFFER_SIZE> buffer;
    std::size_t size = args.A2B.Receive(buffer.data(), buffer.size());
    std::cout << std::string(buffer.data(), size) << std::endl;

    std::cout << "-------- Step B --------\n";

    std::string msg = "Step B finished!\n";
    args.log += msg;
    args.B2C.Send(msg.c_str(), msg.length());
}


void StepC(Args &args)
{
    std::array<char, BUFFER_SIZE> buffer;
    std::size_t size = args.B2C.Receive(buffer.data(), buffer.size());
    std::cout << std::string(buffer.data(), size) << std::endl;

    std::cout << "-------- Step C --------\n";

    std::string msg = "Step C finished!\n";
    args.log += msg;
    args.C2M.Send(msg.c_str(), msg.length());
}


int main()
{
    Args args;

    std::thread stepA(StepA, std::ref(args));
    std::thread stepB(StepB, std::ref(args));
    std::thread stepC(StepC, std::ref(args));

    std::array<char, BUFFER_SIZE> buffer;
    std::size_t size = args.C2M.Receive(buffer.data(), buffer.size());
    std::cout << std::string(buffer.data(), size) << std::endl;

    stepA.join();
    stepB.join();
    stepC.join();

    std::cout << "Log:\n" << args.log;

    return 0;
}

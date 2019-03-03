#include <iostream>

#include <process.hpp>


int main()
{
    TinyProcessLib::Process proc("./answer");
    auto answer = proc.get_exit_status();
    std::cout << "The answer: " << answer << std::endl;
    
    return 0;
}
#include <iostream>
#include <sstream>

#include "../../common.h"


static int ID = 0;


void LogImpl(std::ostream &os)
{
}


template <typename TFirst, typename ...TRest>
void LogImpl(std::ostream &os, TFirst &&first, TRest &&...rest)
{
    os << std::forward<TFirst>(first);
    LogImpl(os, std::forward<TRest>(rest)...);
}


template <typename TFirst, typename ...TParams>
void Log(TFirst &&first, TParams &&...params)
{
    // What if when uncomment the following line?
    //static int ID = 0;

    std::ostringstream oss;
    oss << "Out [" << ++ID << "]: ";
    LogImpl(oss, first, std::forward<TParams>(params)...);
    oss << std::endl;

    std::cout << oss.str();
}


int main()
{
    Log("Hello, world!");
    Log("This is a test code!");
    Log("This is a real life!");

    PAUSE();

    return 0;
}


// References:
// https://stackoverflow.com/questions/29326460/how-to-make-a-variadic-macro-for-stdcout
// https://stackoverflow.com/questions/2821223/how-would-one-call-stdforward-on-all-arguments-in-a-variadic-function
// http://eli.thegreenplace.net/2014/variadic-templates-in-c/

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
    oss << "Out [" << ++ID << "] <" << sizeof...(params) << ">: ";
    LogImpl(oss, first, std::forward<TParams>(params)...);
    oss << std::endl;

    std::cout << oss.str();
}


template <typename T>
std::ostream &Print(std::ostream &os, const T &t)
{
    return os << t;
}


template <typename T, typename... TArgs>
std::ostream &Print(std::ostream &os, const T &t, const TArgs&... rest)
{
    os << t << ", ";
    return Print(os, rest...);
}


template <typename T, typename... TArgs>
std::ostream &Println(std::ostream &os, const T &t, const TArgs&... rest)
{
    os << t << ", ";
    return Print(os, rest...) << '\n';
}


template <typename T>
inline T Square(T x)
{
    return x * x;
}


template <typename... TArgs>
std::ostream &PrintSquared(std::ostream &os, const TArgs&... rest)
{
    return Println(os, Square(rest)...);
}


int main()
{
    Log("Hello, world!");
    Log("This is a test code!");
    Log("This is a real life!");
    Log("PI: ", 3.141592653);
    
    Println(std::cout, 1, 2, 3, 4);
    Println(std::cout, 1, 2, 3.14, 42, 5.0);

    PrintSquared(std::cout, 1, 2, 3, 4, 5);

    PAUSE();

    return 0;
}


// References:
// https://stackoverflow.com/questions/29326460/how-to-make-a-variadic-macro-for-stdcout
// https://stackoverflow.com/questions/2821223/how-would-one-call-stdforward-on-all-arguments-in-a-variadic-function
// http://eli.thegreenplace.net/2014/variadic-templates-in-c/
// C++ Primer, 5th Edition, 16.4 Variadic Templates

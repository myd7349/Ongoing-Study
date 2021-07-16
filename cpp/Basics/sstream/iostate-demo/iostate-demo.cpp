#include <iomanip>
#include <iostream>
#include <sstream>


struct Point
{
    Point(float xv = .0f, float yv = .0f) // 0f won't work.
        : x(xv), y(yv)
    {
    }

    float x, y;
};


void DumpIoState(std::ios_base::iostate state)
{
    if (state == std::ios_base::goodbit)
    {
        std::cout << "good";
        return;
    }

    bool split = false;

    if (state & std::ios_base::eofbit)
    {
        if (split)
            std::cout << '|';
        std::cout << "eof";
        if (!split)
            split = true;
    }

    if (state & std::ios_base::failbit)
    {
        if (split)
            std::cout << '|';
        std::cout << "fail";
        if (!split)
            split = true;
    }

    if (state & std::ios_base::badbit)
    {
        if (split)
            std::cout << '|';
        std::cout << "bad";
        if (!split)
            split = true;
    }
}


void DumpIoState(std::ios_base &ios)
{
    DumpIoState(ios.rdstate());
}


void DumpIoStateViaAccessors(std::istream &is)
{
    std::cout << std::boolalpha;

    std::cout << " good():" << is.good();
    std::cout << " eof():" << is.eof();
    std::cout << " fail():" << is.fail();
    std::cout << " bad():" << is.bad();
    std::cout << " operator bool():" << is.operator bool();
}


Point FromString(const char *s)
{
    std::cout << s << "\n--------------------------------------------------------------------------------\n";

    Point value;

    std::istringstream iss(s);
    char ch;

#define _ DumpIoState(iss); DumpIoStateViaAccessors(iss); std::cout << std::endl

    iss >> ch; _;
    iss >> ch; _;
    iss >> ch; _;
    iss >> ch; _;
    iss >> ch; _;
    iss >> ch; _;

    iss >> value.x; _;
    iss >> ch; _;
    iss >> value.y; _;
    iss >> ch; _;

#undef _

    std::cout << "\n\n";

    return value;
}


std::string ToString(const Point &value)
{
    std::ostringstream oss;
    oss << "Point(" << value.x << ',' << value.y << ')';

    return oss.str();
}


int main()
{
    FromString("");
    FromString("P");
    FromString("Point");
    FromString("Point(");
    FromString("Point123");
    FromString("Point(123");
    FromString("Point(123,");
    FromString("Point(123,456");
    FromString("Point(123,456)");

    return 0;
}


// Reference:
// [C++ String stream ignore() not working](https://stackoverflow.com/questions/46480689/c-string-stream-ignore-not-working)
// [std::stringstream - discard a value](https://stackoverflow.com/questions/33561518/stdstringstream-discard-a-value)
// [How does istream::ignore( ) work?](https://stackoverflow.com/questions/14693106/how-does-istreamignore-work)
// [What is the difference between eof(), fail(), bad(), and good() in C++ streams?](https://stackoverflow.com/questions/43084612/what-is-the-difference-between-eof-fail-bad-and-good-in-c-streams)
// https://en.cppreference.com/w/cpp/io/ios_base/iostate
// [C++ printing boolean, what is displayed?](https://stackoverflow.com/questions/15960015/c-printing-boolean-what-is-displayed/15960054)

/*

--------------------------------------------------------------------------------
eof|fail good():false eof():true fail():true bad():false operator bool():false  
eof|fail good():false eof():true fail():true bad():false operator bool():false  
eof|fail good():false eof():true fail():true bad():false operator bool():false  
eof|fail good():false eof():true fail():true bad():false operator bool():false  
eof|fail good():false eof():true fail():true bad():false operator bool():false  
eof|fail good():false eof():true fail():true bad():false operator bool():false  
eof|fail good():false eof():true fail():true bad():false operator bool():false  
eof|fail good():false eof():true fail():true bad():false operator bool():false  
eof|fail good():false eof():true fail():true bad():false operator bool():false  
eof|fail good():false eof():true fail():true bad():false operator bool():false  


P
--------------------------------------------------------------------------------
good good():true eof():false fail():false bad():false operator bool():true    
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false


Point
--------------------------------------------------------------------------------
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false


Point(
--------------------------------------------------------------------------------
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false


Point123
--------------------------------------------------------------------------------
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
eof good():false eof():true fail():false bad():false operator bool():true
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false


Point(123
--------------------------------------------------------------------------------
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
eof good():false eof():true fail():false bad():false operator bool():true
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false


Point(123,
--------------------------------------------------------------------------------
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
eof|fail good():false eof():true fail():true bad():false operator bool():false
eof|fail good():false eof():true fail():true bad():false operator bool():false


Point(123,456
--------------------------------------------------------------------------------
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
eof good():false eof():true fail():false bad():false operator bool():true
eof|fail good():false eof():true fail():true bad():false operator bool():false


Point(123,456)
--------------------------------------------------------------------------------
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true
good good():true eof():false fail():false bad():false operator bool():true


*/
#include <iostream>

struct Basic
{
	int x;
	int y;
};

struct Detailed : /* public */ Basic
{
	int z;
	int w;
};

void Fill(Basic &b)
{
	b.x = 1;
	b.y = 2;
}

void Fill(Detailed &d)
{
	Fill(static_cast<Basic &>(d));

	d.z = 3;
	d.w = 4;
}


void Print(const Basic &b)
{
    std::cout << "x: " << b.x << ", y: " << b.y;
}

void Print(const Detailed &d)
{
	Print(static_cast<const Basic &>(d));

	std::cout << ", z: " << d.z << ", w: " << d.w;
}


int main()
{
    Detailed d;
    Fill(d);
    Print(d);

	return 0;
}


// References:
// [Is it possible to pass derived classes by reference to a function taking base class as a parameter](https://stackoverflow.com/questions/9285627/is-it-possible-to-pass-derived-classes-by-reference-to-a-function-taking-base-cl)
// [Struct inheritance: implicitly public or private?](https://stackoverflow.com/questions/23017907/struct-inheritance-implicitly-public-or-private)
// [Assigning base struct to derived struct](https://stackoverflow.com/questions/12483663/assigning-base-struct-to-derived-struct)
// [C++ cast to base class](https://stackoverflow.com/questions/42912136/c-cast-to-base-class)
// [What is object slicing?](https://stackoverflow.com/questions/274626/what-is-object-slicing)

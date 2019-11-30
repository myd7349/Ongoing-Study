#include "flushinp.h"

#include <stdio.h>


void flushinp(void)
{
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n')
    {
    }
}


// References:
// https://github.com/wmcbrine/PDCurses/blob/master/wincon/pdckbd.c
// Jumping into C++, Ch3, What if your program exits immediately?
// > std::cin.ignore();


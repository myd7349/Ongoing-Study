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

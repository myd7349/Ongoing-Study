#include <stdio.h>

#include "lib.h"


int main(void)
{
    print_address();
    print_address_macro();

    printf("%c\n", array1[0]);
    printf("%c\n", array2[0]); // Oops!

    return 0;
}


// References:
// Expert C Programming: Deep C Secrets, Ch4.3.2

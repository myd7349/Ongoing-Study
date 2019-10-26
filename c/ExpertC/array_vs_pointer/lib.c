#include <stdio.h>

char array1[] = { 'H', 'e', 'l', 'l', 'o' };
char array2[] = { 'H', 'e', 'l', 'l', 'o' };


void print_address()
{
    printf("array1: %p\n", array1);
    printf("array2: %p\n", array2);
    printf("&array1[0]: %p\n", &array1[0]);
    printf("&array2[0]: %p\n", &array2[0]);
}

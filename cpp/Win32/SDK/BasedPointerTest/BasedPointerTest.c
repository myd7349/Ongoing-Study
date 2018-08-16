#include <stdio.h>


int *pBased;
typedef int __based(pBased) *pbasedptr_t;


int main()
{
    pbasedptr_t ptr = 0;
    int arr[] = { 1, 1, 2, 3, 5, 8, 13 };
    int arr2[] = { 1, 4, 9, 16 };

    pBased = arr;

    printf("%p %p\n", arr, (void *)ptr);
    printf("%d\n", ptr[2]);

    pBased = arr2;

    printf("%p %p\n", arr2, (void *)ptr);
    printf("%d\n", ptr[2]);

    return 0;
}

// References:
// https://msdn.microsoft.com/en-us/library/57a97k4e.aspx
// Multithreading Applications in Win32, Chapter 13, P286

#include <stdio.h>


void print_addr_v1(char ca[])
{
    printf("&ca: %p, &(ca[0]): %p, &(ca[1]): %p\n",
        &ca, &(ca[0]), &ca[1]);
}


void print_addr_v2(char *pa)
{
    printf("&pa: %p, &(pa[0]): %p, &(pa[1]): %p\n",
        &pa, &(pa[0]), &pa[1]);
}


char ga[] = { 'H', 'e', 'l', 'l', 'o' };


int main()
{
    char arr[] = { 'H', 'e', 'l', 'l', 'o' };

    printf("&arr: %p, &(arr[0]): %p, &(arr[1]): %p\n",
        &arr, &(arr[0]), &arr[1]);
    print_addr_v1(arr);
    print_addr_v2(arr);

    printf("&ga: %p, &(ga[0]): %p, &(ga[1]): %p\n",
        &ga, &(ga[0]), &ga[1]);
    print_addr_v1(ga);

    return 0;
}

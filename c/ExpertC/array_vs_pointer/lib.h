extern char array1[];
extern char *array2;

#define print_address_macro() \
    printf("array1: %p\n", array1); \
    printf("array2: %p\n", array2); \
    printf("&array1[0]: %p\n", &array1[0]); \
    printf("&array2[0]: %p\n", &array2[0]);

void print_address();

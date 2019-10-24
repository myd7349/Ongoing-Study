#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>


#define error(format, ...) \
    do \
    { \
        fprintf(stderr, "Error: %s(%d): " format, __FILE__, __LINE__, __VA_ARGS__); \
        exit(EXIT_FAILURE); \
    } while (0)

#endif /* UTILS_H_ */

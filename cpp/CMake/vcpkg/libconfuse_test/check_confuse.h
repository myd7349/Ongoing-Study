#ifndef _check_confuse_h_
#define _check_confuse_h_

#include <stdlib.h>

#include <confuse.h>


#define fail_unless(test) \
    do { if(!(test)) { \
        fprintf(stderr, \
                "----------------------------------------------\n" \
                "%s:%d: test FAILED:\nFailed test: %s\n" \
                "----------------------------------------------\n", \
                __FILE__, __LINE__, #test); \
        exit(1); \
    } } while(0)

#define SRC_DIR "."

#endif


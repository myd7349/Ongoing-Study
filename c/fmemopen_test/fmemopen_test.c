#include <stdlib.h>

#ifdef _WIN32
# include <shlwapi.h>
# include "../fmemopen.h"
#else
# define _GNU_SOURCE
# include <stdio.h>
# include <unistd.h>
#endif


static int is_file_exists(const char *fname)
{
#ifdef _WIN32
    return !!PathFileExistsA(fname);
#else
    return access(fname, F_OK) != -1;
#endif
    return 0;
}


int main(void)
{
    char buffer[1024];
    FILE *fmem = fmemopen(buffer, sizeof(buffer), "r+b");
    if (fmem == NULL)
        return EXIT_FAILURE;

    fclose(fmem);

#ifdef _WIN32
    printf("Does \"%s\" still exist? %d\n",
        tmp_file_name, is_file_exists(tmp_file_name));
#endif

    return 0;
}


// References:
// https://linux.die.net/man/3/fmemopen
// https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c

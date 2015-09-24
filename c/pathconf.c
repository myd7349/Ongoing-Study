// 2015-09-24T16:30+08:00
// APUE 2.5.4
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STRX(c) #c
#define STR(c) STRX(c)

#define PRINT_PATHCONF(path, name) \
  do { \
    long val = pathconf(path, name); \
    if (val == -1) \
      fprintf(stderr, "Failed to get pathconf of \"" \
                      STR(name) \
                      "\" for path \"%s\": %s\n", \
                      path, strerror(errno)); \
    else \
      printf(STR(name) " == %ld\n", val); \
  } while (0)
    
#define PC(name) _PC_##name

int main(int argc, char *argv[])
{  
  if (argc < 2) {
    fprintf(stderr, "usage: pathconf path\n");
    return 0;
  }
  
  for (int i = 1; i < argc; i++) {
    printf("pathconf of \"%s\":\n", argv[i]);
    
    PRINT_PATHCONF(argv[i], PC(FILESIZEBITS));
    PRINT_PATHCONF(argv[i], PC(LINK_MAX));
    PRINT_PATHCONF(argv[i], PC(MAX_CANON));
    PRINT_PATHCONF(argv[i], PC(MAX_INPUT));
    PRINT_PATHCONF(argv[i], PC(NAME_MAX));
    PRINT_PATHCONF(argv[i], PC(PATH_MAX));
    PRINT_PATHCONF(argv[i], PC(PIPE_BUF));
    PRINT_PATHCONF(argv[i], PC(SYMLINK_MAX));
  }
  
  return 0;
}

[Simple glob to regex conversion](https://github.com/p-ranav/indicators/blob/e34840ab0d82cda89c31125c3290c5830d00f294/CMakeLists.txt#L76-L90)

> ```cmake
>     # Simple glob to regex conversion (.gitignore => CPACK_SOURCE_IGNORE_FILES)
>     file(READ ".gitignore" DOT_GITIGNORE)
>     string(REPLACE ";" "RANDOMSEQUENCE" DOT_GITIGNORE "${DOT_GITIGNORE}")
>     string(REPLACE "\n" ";" DOT_GITIGNORE "${DOT_GITIGNORE}")
>     string(REPLACE "RANDOMSEQUENCE" "\\;" DOT_GITIGNORE "${DOT_GITIGNORE}")
>     foreach(IGNORE_LINE ${DOT_GITIGNORE})
>       if(NOT IGNORE_LINE OR IGNORE_LINE MATCHES "^#")
>         continue()
>       endif()
>       string(REPLACE "\\" "\\\\" IGNORE_LINE "${IGNORE_LINE}")
>       string(REPLACE "." "\\\\." IGNORE_LINE "${IGNORE_LINE}")
>       string(REPLACE "*" ".*" IGNORE_LINE "${IGNORE_LINE}")
>       string(REPLACE "+" "\\\\+" IGNORE_LINE "${IGNORE_LINE}")
>       list(APPEND CPACK_SOURCE_IGNORE_FILES "${IGNORE_LINE}")
>     endforeach()
> ```


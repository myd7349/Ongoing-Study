cmake_minimum_required(VERSION 3.8)

project(macro_arg)

# Question: Can I rename `linkage_upper` to `linkage`?
macro(check_linkage linkage)
    message("linkage <<<: ${linkage}")
    string(TOUPPER "${linkage}" linkage_upper)
    message("linkage >>>: ${linkage_upper}")

    if (NOT ${linkage_upper} MATCHES "^(SHARED|STATIC)$")
        message("Invalid linkage: ${linkage}")
    endif ()
endmacro()

set(linkage "STATIC")

check_linkage(STATIC)
check_linkage(SHARED)
check_linkage(static)
check_linkage(dynamic)

cmake_minimum_required(VERSION 3.8)

project(function_vs_macro)

set(global_var "I'm the king!")

########################################################

set(var "Hello")

function(Foo arg)
    message(STATUS "global_var: ${global_var}")
    message(STATUS "arg: ${arg}")
    set(arg "Hello from Foo")
    message(STATUS "arg: ${arg}")
endfunction()

message("=== Call function Foo ===")

Foo(${var})

message(STATUS "var: ${var}")

########################################################

set(var "Hello")

function(Foo2 arg)
    message(STATUS "global_var: ${global_var}")
    message(STATUS "arg: ${arg}")
    set(arg "Hello from Foo2" PARENT_SCOPE)
    message(STATUS "arg: ${arg}")
endfunction()

message("=== Call function Foo2 ===")

Foo2(${var})

message(STATUS "var: ${var}")
message(STATUS "arg: ${arg}")

########################################################

set(var "Hello")

function(Foo3 var)
    message(STATUS "global_var: ${global_var}")
    message(STATUS "var: ${var}")
    set(var "Hello from Foo3" PARENT_SCOPE)
    message(STATUS "var: ${var}")
endfunction()

message("=== Call function Foo3 ===")

Foo3(${var})

message(STATUS "var: ${var}")

########################################################

set(var "Hello")

macro(Moo arg)
    message(STATUS "global_var: ${global_var}")
    message(STATUS "arg: ${arg}")
    set(arg "Hello from Moo")
    message(STATUS "arg: ${arg}")
endmacro()

message("=== Call macro ===")

Moo(${var})

message(STATUS "var: ${var}")

########################################################

set(var "Hello")

macro(Moo2 var)
    message(STATUS "global_var: ${global_var}")
    message(STATUS "var: ${var}")
    set(var "Hello from Moo2")
    message(STATUS "var: ${var}")
endmacro()

message("=== Call macro ===")

Moo2(${var})

message(STATUS "var: ${var}")

########################################################

# References:
# https://stackoverflow.com/questions/24297999/function-vs-macro-in-cmake
# https://stackoverflow.com/questions/12023879/let-cmake-not-detect-c-compiler
# https://stackoverflow.com/questions/14375519/how-to-write-a-nice-function-that-passes-variables-by-reference

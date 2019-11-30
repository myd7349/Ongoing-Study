package main

/*
#include <stdio.h>
#include <stdlib.h>
*/
import "C"
import "unsafe"

func main() {
	cstr := C.CString("Hello, world!");
	C.puts(cstr);
	C.free(unsafe.Pointer(cstr))
}

// References:
// https://stackoverflow.com/questions/6125683/call-go-functions-from-c
// https://karthikkaranth.me/blog/calling-c-code-from-go/
// https://stackoverflow.com/questions/12591773/error-could-not-determine-kind-of-name-for-c-stdout-when-building-example-from

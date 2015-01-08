// 2015-01-07T08:59+08:00

// Percent-encoding/decoding utility.
//
// Sometimes, when I downloaded something via my firefox, I may got a file with
// a strange name.
//
// After some exploration, I began to know "Percent-encoding" (or "URL encoding")
// and RFC 3986. Then I realised that what I need to do is unescaping those strange
// names according to RFC 3986.
//
// At the beginning, I planned to write a program with Python 3.x, since Python 3.x provides
// us two functions to complete this work: urllib.parse.quote, urllib.parse.unquote.
// However, I am so lazy that I never start this work.
//
// I also considered to write such a program with C. And libcurl also provides us two
// functions to do this work: curl_easy_escape, curl_easy_unescape. However, it is a little 
// difficult to deal with different character encodings in C(may be libiconv is a good choice). 
// And you know, I am lazy, so...
//
// Recently, I began to learn Go. So, I wrote this program as a practice.

package main

import (
	"bufio"
	"flag"
	"fmt"
	"net/url"
	"os"
	"path/filepath"
	"strings"
)

func unescape(s string) string {
	normname, err := url.QueryUnescape(s)

	if err == nil {
		return normname
	} else {
		fmt.Println(err)
		return s
	}
}

func main() {
	// -- Parse command line arguments.
	var path, method string

	flag.StringVar(&path, "f", "", "Specify the file name or path name to be processed")
	flag.StringVar(&method, "m", "unescape", "Specify the operation: \"escape\" or \"unescape\"")

	flag.Parse()

	// -- Decide the action we should take according to the "-m" option.
	var convert = func(string) string { return "" }
	switch method {
	case "escape":
		convert = url.QueryEscape
	case "unescape":
		convert = unescape
	default:
		fmt.Println("Unknown operation:", method)
		return
	}

	// -- Now, do something meaningful to make the life a little more easier.
	if len(path) == 0 {
		// If path name is empty, then read string from stdin.
		stdin := bufio.NewReader(os.Stdin)
		var line string
		var err error

		for {
			line, err = stdin.ReadString('\n')
			if err == nil {
				fmt.Println(convert(strings.TrimSuffix(line, "\r\n")))
			}
		}
	} else {
		// Otherwise, process the target file/path name.
		_, err := os.Stat(path)
		if err != nil {
			fmt.Printf("File or path \"%s\" doesn't exist.\n", path)
			return
		}

		// We just process the last pathname component.
		head, tail := filepath.Split(path)
		newpath := filepath.Join(head, convert(tail))

		if newpath != path {
			os.Rename(path, newpath)
			fmt.Println(path, "->", newpath)
		}
	}
}

// References:
// Check if file exists: http://golang-examples.tumblr.com/post/46579246576/check-if-file-exists
// Command-Line Flags: https://gobyexample.com/command-line-flags

// 2015-01-07T08:59+08:00

// Percent encoding/decoding utility.

package main

import (
	"bufio"
	"errors"
	"flag"
	"fmt"
	"net/url"
	"os"
	"path/filepath"
	"strings"
)

func unescape(s string) string {
	res, err := url.QueryUnescape(s)

	if err == nil {
		return res
	} else {
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
		fmt.Println(errors.New("Unknown operation: " + method))
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

		// In most cases, escaping/unescaping all files' name under given path recursively is not what we want to do.
		// So, make sure that "-m=escape" is not provided when a path name is given.
		/*
			if finfo.IsDir() && method == "escape" {
				fmt.Println(errors.New("Option \"-m=escape\" should not be provided when a path name is given."))
				return
			}
		*/

		// Define an visitor to process each file.
		var filevisitor = func(p string, info os.FileInfo, err error) error {
			if err != nil {
				fmt.Println(err)
				return nil
			}

			if !info.IsDir() {
				dir, file := filepath.Split(p)
				newpath := filepath.Join(dir, convert(file))

				if p != newpath {
					os.Rename(p, newpath)
					fmt.Println(p, "->", newpath)
				}
			}

			return nil
		}

		// filepath.Walk will always walk a directory recursively
		filepath.Walk(path, filevisitor)
	}
}

// References:
// Check if file exists: http://golang-examples.tumblr.com/post/46579246576/check-if-file-exists
// Command-Line Flags: https://gobyexample.com/command-line-flags
// Anonymous recursion: http://rosettacode.org/wiki/Anonymous_recursion#Go
// Walk a directory/Recursively: http://rosettacode.org/wiki/Walk_a_directory/Recursively#Go

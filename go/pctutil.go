// 2015-01-07T08:59+08:00

// Percent encoding/decoding utility.

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
	var recursive, verbose, stimulate bool

	flag.StringVar(&path, "f", "", "Specify the file name or path name to be processed")
	flag.StringVar(&method, "m", "unescape", "Specify the operation: \"escape\" or \"unescape\"(default operation)")
	flag.BoolVar(&recursive, "r", false, "Specify whether processing a directory recursively or not")
	flag.BoolVar(&verbose, "V", false, "Specify whether enabling verbose mode or not")
	flag.BoolVar(&stimulate, "s", false, "Specify whether rename the target file or not")

	flag.Parse()

	// -- Decide the action we should take according to the "-m" option.
	var convert func(string) string
	switch method {
	case "escape":
		// In most cases, escaping all files' name under given path recursively is not what we want to do.
		// So, make sure that "-r" option and "-m=escape" are not provided simultaneously.
		if recursive {
			fmt.Println("Option \"-r\" and \"-m=escape\" should not be provided simultaneously.")
			return
		}
		convert = url.QueryEscape
	case "unescape":
		convert = unescape
	default:
		fmt.Println("Unknown operation:", method)
		return
	}

	// -- If verbose mode is enabled, then more message will be printed.
	var echo = func(a ...interface{}) (int, error) { return 0, nil }
	if verbose {
		echo = fmt.Println
	}

	// -- If "stimulate" is true, it means that we just want to stimulate the processing procedure.
	var rename = func(_, _ string) error { return nil }
	if !stimulate {
		rename = os.Rename
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
		finfo, err := os.Stat(path)
		if err != nil {
			fmt.Printf("File or path \"%s\" doesn't exist.\n", path)
			return
		}

		var processFile = func(path string) {
			dir, file := filepath.Split(path)
			newpath := filepath.Join(dir, convert(file))
			rename(path, newpath)
			echo(path, "->", newpath)
		}

		if finfo.IsDir() {
			// Define an visitor to process each file encountered.
			var visitor = func(p string, info os.FileInfo, err error) error {
				if err != nil {
					echo(err)
					return nil
				}

				if info.IsDir() && recursive {
					// Bad idea! Go doesn't support recursive lambda.
					return filepath.Walk(p, visitor)
				}

				processFile(p)
				return nil
			}

			filepath.Walk(path, visitor)
		} else {
			processFile(path)
		}
	}
}

// References:
// Check if file exists: http://golang-examples.tumblr.com/post/46579246576/check-if-file-exists
// Command-Line Flags: https://gobyexample.com/command-line-flags
// Anonymous recursion: http://rosettacode.org/wiki/Anonymous_recursion#Go
// Walk a directory/Recursively: http://rosettacode.org/wiki/Walk_a_directory/Recursively#Go

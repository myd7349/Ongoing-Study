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

var convert = func(string) string { return "" }
var echo = func(a ...interface{}) (int, error) { return 0, nil }
var rename = func(_, _ string) error { return nil }
var recursive = false

func processfile(path string) {
	dir, file := filepath.Split(path)
	newpath := filepath.Join(dir, convert(file))
	rename(path, newpath)
	echo(path, "->", newpath)
}

// Define an visitor to process each file.
func filevisitor(p string, info os.FileInfo, err error) error {
	if err != nil {
		echo(err)
		return nil
	}

	if info.IsDir() {
		return nil
		// filepath.Walk will always walk the directory recursively, so code below is not needed.
		/*
			echo("p == ", p, recursive)
			if recursive {
				echo("----")
				return filepath.Walk(p, filevisitor)
			} else {
				return nil
			}
		*/
	} else {
		processfile(p)
	}

	return nil
}

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
	var verbose, stimulate bool

	flag.StringVar(&path, "f", "", "Specify the file name or path name to be processed")
	flag.StringVar(&method, "m", "unescape", "Specify the operation: \"escape\" or \"unescape\"")
	flag.BoolVar(&recursive, "r", false, "Specify whether processing a directory recursively or not")
	flag.BoolVar(&verbose, "V", false, "Specify whether enabling verbose mode or not")
	flag.BoolVar(&stimulate, "s", false, "Specify whether stimulating the processing procedure or not")

	flag.Parse()

	// -- If verbose mode is enabled, then more message will be printed.
	if verbose {
		echo = fmt.Println
	}

	// -- If "stimulate" is true, it means that we just want to stimulate the processing procedure.
	if !stimulate {
		rename = os.Rename
	}

	// -- Decide the action we should take according to the "-m" option.
	switch method {
	case "escape":
		// In most cases, escaping all files' name under given path recursively is not what we want to do.
		// So, make sure that "-r" option and "-m=escape" are not provided simultaneously.
		if recursive {
			fmt.Println(errors.New("Option \"-r\" and \"-m=escape\" should not be provided simultaneously."))
			return
		}
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

		filepath.Walk(path, filevisitor)
	}
}

// References:
// Check if file exists: http://golang-examples.tumblr.com/post/46579246576/check-if-file-exists
// Command-Line Flags: https://gobyexample.com/command-line-flags
// Anonymous recursion: http://rosettacode.org/wiki/Anonymous_recursion#Go
// Walk a directory/Recursively: http://rosettacode.org/wiki/Walk_a_directory/Recursively#Go

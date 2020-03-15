// File Checksum Integrity Verifier Clone
package main

import (
	"crypto/md5"
	"crypto/sha1"
	"crypto/sha256"
	"crypto/sha512"
	"encoding/hex"
	"errors"
	"fmt"
	"hash"
	"io"
	"os"
	"path/filepath"
	"strings"
)

func getProgramName() string {
	_, fileName := filepath.Split(os.Args[0])
	return strings.TrimSuffix(fileName, filepath.Ext(fileName))
}

const (
	checksumMD5    = 0
	checksumSHA1   = iota
	checksumSHA256 = iota
	checksumSHA512 = iota
)

func getFileChecksum(file *os.File, algorithm int) ([]byte, error) {
	var (
		pos int64
		err error
	)

	if pos, err = file.Seek(0, io.SeekCurrent); err != nil {
		return nil, err
	}

	if _, err = file.Seek(0, io.SeekStart); err != nil {
		return nil, err
	}

	defer file.Seek(pos, io.SeekStart)

	var ctx hash.Hash

	switch algorithm {
	case checksumMD5:
		ctx = md5.New()
	case checksumSHA1:
		ctx = sha1.New()
	case checksumSHA256:
		ctx = sha256.New()
	case checksumSHA512:
		ctx = sha512.New()
	default:
		return nil, errors.New("Invalid algorithm")
	}

	if _, err := io.Copy(ctx, file); err != nil {
		return nil, err
	}

	return ctx.Sum(nil), nil
}

func getFileChecksumString(file *os.File, algorithm int, upperCase bool) (string, error) {
	var (
		checksum []byte
		err      error
	)

	if checksum, err = getFileChecksum(file, algorithm); err != nil {
		return "", err
	}

	if upperCase {
		return fmt.Sprintf("%X", checksum), nil
	} else {
		//return fmt.Sprintf("%x", checksum), nil
		return hex.EncodeToString(checksum), nil
	}
}

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage:\n  %s <file>", getProgramName())
		os.Exit(1)
	}

	var (
		file     *os.File
		err      error
		checksum string
	)

	if file, err = os.Open(os.Args[1]); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to open file %v: %v\n", os.Args[1], err)
		os.Exit(1)
	}

	defer file.Close()

	if checksum, err = getFileChecksumString(file, checksumMD5, false); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to calculate MD5: %v\n", err)
		os.Exit(1)
	}

	fmt.Println("MD5:   ", checksum)

	if checksum, err = getFileChecksumString(file, checksumSHA1, false); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to calculate SHA1: %v\n", err)
		os.Exit(1)
	}

	fmt.Println("SHA1:  ", checksum)

	if checksum, err = getFileChecksumString(file, checksumSHA256, false); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to calculate SHA256: %v\n", err)
		os.Exit(1)
	}

	fmt.Println("SHA256:", checksum)

	if checksum, err = getFileChecksumString(file, checksumSHA512, false); err != nil {
		fmt.Fprintf(os.Stderr, "Failed to calculate SHA512: %v\n", err)
		os.Exit(1)
	}

	fmt.Println("SHA512:", checksum)
}

// References:
// https://stackoverflow.com/questions/13027912/trim-strings-suffix-or-extension
// https://en.wikibooks.org/wiki/File_Checksum_Integrity_Verifier_(FCIV)_Examples
// PS> Get-FilHash fcivc.go -algorithmorithm SHA1 | Format-List
// https://stackoverflow.com/questions/10901351/fgetpos-available-in-go-want-to-find-file-position
// https://stackoverflow.com/questions/14230145/how-to-convert-a-zero-terminated-byte-array-to-string
// https://stackoverflow.com/questions/6986944/does-the-go-language-have-function-method-overloading
// https://stackoverflow.com/questions/19328957/how-to-go-from-bytes-to-get-hexadecimal

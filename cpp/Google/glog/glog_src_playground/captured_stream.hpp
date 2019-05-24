// https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/googletest.h
#pragma once

#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>

using std::fflush;
using std::fread;
using std::fseek;
using std::ftell;
using std::string;

#include <fcntl.h>

#ifdef _MSC_VER
#include <direct.h>
#include <io.h>
#define open _open
#define close _close
#define dup _dup
#define dup2 _dup2
#else
#include <unistd.h>
#endif

#include "commandlineflags.h"


static inline string GetTempDir() {
#ifndef _WIN32
    return "/tmp";
#else
    _mkdir("tmp");
    return "tmp";

    //char tmp[MAX_PATH];
    //GetTempPathA(MAX_PATH, tmp);
    //return tmp;
#endif
}

#if defined(_WIN32) && defined(_MSC_VER) && !defined(TEST_SRC_DIR)
// The test will run in glog/vsproject/<project name>
// (e.g., glog/vsproject/logging_unittest).
static const char TEST_SRC_DIR[] = "../..";
#elif !defined(TEST_SRC_DIR)
# warning TEST_SRC_DIR should be defined in config.h
static const char TEST_SRC_DIR[] = ".";
#endif

static const uint32_t PTR_TEST_VALUE = 0x12345678;

DEFINE_string(test_tmpdir, GetTempDir(), "Dir we use for temp files");
DEFINE_string(test_srcdir, TEST_SRC_DIR,
    "Source-dir root, needed to find glog_unittest_flagfile");

// glog/src/windows/port.h
#ifndef __MINGW32__
enum { STDIN_FILENO = 0, STDOUT_FILENO = 1, STDERR_FILENO = 2 };
#endif
#define S_IRUSR S_IREAD
#define S_IWUSR S_IWRITE


// CHECK macro is defined in logging.h:
class NullStream
{
public:
};

#define CHECK(cond) assert((cond))

// ----------------------------------------------------------------------
// Golden file functions
// ----------------------------------------------------------------------

class CapturedStream {
public:
    CapturedStream(int fd, const string & filename) :
        fd_(fd),
        uncaptured_fd_(-1),
        filename_(filename) {
        Capture();
    }

    ~CapturedStream() {
        if (uncaptured_fd_ != -1) {
            CHECK(close(uncaptured_fd_) != -1);
        }
    }

    // Start redirecting output to a file
    void Capture() {
        // Keep original stream for later
        CHECK(uncaptured_fd_ == -1);
        uncaptured_fd_ = dup(fd_);
        CHECK(uncaptured_fd_ != -1);

        // Open file to save stream to
        int cap_fd = open(filename_.c_str(),
            O_CREAT | O_TRUNC | O_WRONLY,
            S_IRUSR | S_IWUSR);
        CHECK(cap_fd != -1);

        // Send stdout/stderr to this file
        fflush(NULL);
        CHECK(dup2(cap_fd, fd_) != -1);
        CHECK(close(cap_fd) != -1);
    }

    // Remove output redirection
    void StopCapture() {
        // Restore original stream
        if (uncaptured_fd_ != -1) {
            fflush(NULL);
            CHECK(dup2(uncaptured_fd_, fd_) != -1);
        }
    }

    const string & filename() const { return filename_; }

private:
    int fd_;             // file descriptor being captured
    int uncaptured_fd_;  // where the stream was originally being sent to
    string filename_;    // file where stream is being saved
};

static CapturedStream * s_captured_streams[STDERR_FILENO + 1];

// Redirect a file descriptor to a file.
//   fd       - Should be STDOUT_FILENO or STDERR_FILENO
//   filename - File where output should be stored
static inline void CaptureTestOutput(int fd, const string & filename) {
    CHECK((fd == STDOUT_FILENO) || (fd == STDERR_FILENO));
    CHECK(s_captured_streams[fd] == NULL);
    s_captured_streams[fd] = new CapturedStream(fd, filename);
}

static inline void CaptureTestStderr() {
    CaptureTestOutput(STDERR_FILENO, FLAGS_test_tmpdir + "/captured.err");
}

// Return the size (in bytes) of a file
static inline size_t GetFileSize(FILE * file) {
    fseek(file, 0, SEEK_END);
    return static_cast<size_t>(ftell(file));
}

// Read the entire content of a file as a string
static inline string ReadEntireFile(FILE * file) {
    const size_t file_size = GetFileSize(file);
    char * const buffer = new char[file_size];

    size_t bytes_last_read = 0;  // # of bytes read in the last fread()
    size_t bytes_read = 0;       // # of bytes read so far

    fseek(file, 0, SEEK_SET);

    // Keep reading the file until we cannot read further or the
    // pre-determined file size is reached.
    do {
        bytes_last_read = fread(buffer + bytes_read, 1, file_size - bytes_read, file);
        bytes_read += bytes_last_read;
    } while (bytes_last_read > 0 && bytes_read < file_size);

    const string content = string(buffer, buffer + bytes_read);
    delete[] buffer;

    return content;
}

// Get the captured stdout (when fd is STDOUT_FILENO) or stderr (when
// fd is STDERR_FILENO) as a string
static inline string GetCapturedTestOutput(int fd) {
    CHECK(fd == STDOUT_FILENO || fd == STDERR_FILENO);
    CapturedStream * const cap = s_captured_streams[fd];
    CHECK(cap);

    // Make sure everything is flushed.
    cap->StopCapture();

    // Read the captured file.
    FILE * const file = fopen(cap->filename().c_str(), "r");
    const string content = ReadEntireFile(file);
    fclose(file);

    delete cap;
    s_captured_streams[fd] = NULL;

    return content;
}

// Get the captured stderr of a test as a string.
static inline string GetCapturedTestStderr() {
    return GetCapturedTestOutput(STDERR_FILENO);
}


// References:
// https://stackoverflow.com/questions/13531677/stdin-fileno-undeclared-in-windows

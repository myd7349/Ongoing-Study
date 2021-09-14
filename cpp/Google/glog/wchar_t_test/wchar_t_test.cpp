#include <cstring>
#include <iostream>
#include <string>

#include <glog/logging.h>


#ifdef WCONV_SUPPORT
# include "wconv.h"
#endif

#ifdef WCHAR_LOGGING_SUPPORT
# include "wchar_logging.h"
#endif

#ifdef SET_LOCALE
# include <clocale>
#endif

#ifdef _MSC_VER
# include <direct.h>
# define mkdir(p) _mkdir((p))
#elif defined(__linux__)
# include <sys/stat.h>
# include <sys/types.h>
# define mkdir(p) mkdir((p), 0700)
#endif

#ifdef _WIN32
const char path_sep = '\\';
#else
const char path_sep = '/';
#endif


std::string get_app_path(const char *argv0)
{
    const char *slash = std::strrchr(argv0, path_sep);
    if (slash != nullptr)
        return std::string(argv0, slash + 1);
    
    return argv0;
}


int main(int argc, char **argv)
{
#ifdef SET_LOCALE
    std::setlocale(LC_ALL, "zh_CN.utf8");
#endif

    std::string app_path = get_app_path(argv[0]);
    std::cout << "App Path: " << app_path << std::endl;
    
    std::string log_dir = app_path + "Logs\\";
    mkdir(log_dir.c_str());

    FLAGS_log_dir = log_dir.c_str();
    FLAGS_alsologtostderr = 1;
    FLAGS_colorlogtostderr = 1;

    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "Good morning.";
    LOG(INFO) << "早上好！";
    LOG(INFO) << "おはよう";

#ifdef WCONV_SUPPORT
    LOG(INFO) << AnsiToUtf8("Good morning.");
    LOG(INFO) << AnsiToUtf8("早上好！");
    LOG(INFO) << AnsiToUtf8("おはよう");
#endif

    LOG(INFO) << L"Good morning.";
    LOG(INFO) << L"早上好！";
    LOG(INFO) << L"おはよう";

#ifdef WCONV_SUPPORT
    LOG(INFO) << WCharToAnsi(L"Good morning.");
    LOG(INFO) << WCharToAnsi(L"早上好！");
    LOG(INFO) << WCharToAnsi(L"おはよう");

    LOG(INFO) << WCharToUtf8(L"Good morning.");
    LOG(INFO) << WCharToUtf8(L"早上好！");
    LOG(INFO) << WCharToUtf8(L"おはよう");
#endif

    return 0;
}


// References:
// [Poco Logging with std::wstring or wchar_t](https://stackoverflow.com/questions/48945817/poco-logging-with-stdwstring-or-wchar-t)
// [wchar_t support](https://github.com/baysao/google-glog/issues/4)
// https://code.google.com/archive/p/google-glog/issues/4
// [glog  print wchar_t?](https://github.com/google/glog/issues/64)

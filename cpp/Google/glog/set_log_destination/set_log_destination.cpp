#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <glog/logging.h>
#include <glog/stl_logging.h>

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


int main(int argc, char *argv[])
{
    std::string app_path = get_app_path(argv[0]);
    std::cout << "App Path: " << app_path << std::endl;
    
    std::string log_dir = app_path + "Logs\\";
    mkdir(log_dir.c_str());

#ifdef SET_LOG_DIR_VIA_GLOBAL_FLAG
    FLAGS_log_dir = log_dir.c_str();
#endif

    google::InitGoogleLogging(argv[0]);

    //google::SetLogFilenameExtension("log.");

#ifndef SET_LOG_DIR_VIA_GLOBAL_FLAG
    // SetLogDestination is not meant to be used to set logging directory.
    // It is used to set the basename of the logging file.
    // For example, if you want to use one log file instead of four.
    // You can:
    //google::SetLogDestination(google::GLOG_WARNING, "");
    //google::SetLogDestination(google::GLOG_ERROR, "");
    //google::SetLogDestination(google::GLOG_FATAL, "");
    // Since the INFO log file will also record WARNING, ERROR, FATAL messages.
    //
    google::SetLogDestination(google::GLOG_INFO, log_dir.c_str());
    google::SetLogDestination(google::GLOG_WARNING, log_dir.c_str());
    google::SetLogDestination(google::GLOG_ERROR, log_dir.c_str());
    google::SetLogDestination(google::GLOG_FATAL, log_dir.c_str());
#endif

    FLAGS_alsologtostderr = 1;
    FLAGS_colorlogtostderr = 1;

    LOG(INFO) << "Hello, world!";
    LOG(WARNING) << "This is a test code. This is a real life.";
    LOG(ERROR) << "Error!";
    LOG(FATAL) << "Fatal error!";

    return 0;
}

// References:
// https://github.com/google/glog/blob/ce50c57b9e57e42b29851698055696c3a60fc68d/src/utilities.cc#L336-L348
// [logging with glog is not working properly](https://stackoverflow.com/questions/35572073/logging-with-glog-is-not-working-properly)
// >glog by default uses one log file for each severity to prevent two streams opening the same file.
// [glog源码解析一：整体结构 ](https://izualzhy.cn/glog-source-reading-notes)

#include <vector>

#include <glog/logging.h>
#include <glog/stl_logging.h>


int main(int argc, char *argv[])
{
    FLAGS_log_dir = "./Logs";

    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    google::SetLogFilenameExtension(".log");
    google::SetLogDestination(0, "hello_glog");
    google::SetLogDestination(google::GLOG_WARNING, "");

    FLAGS_alsologtostderr = 1;
    FLAGS_colorlogtostderr = 1;

    DLOG(INFO) << "Debug mode!";

    LOG(INFO) << "Hello, world!";
    LOG(WARNING) << "This is a test code. This is a real life.";
    LOG(ERROR) << "You can not see me!";

    std::vector<int> fibs { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };
    LOG(INFO) << fibs;

    return 0;
}

// References:
// https://stackoverflow.com/questions/20016036/glog-no-output-file-log-is-created

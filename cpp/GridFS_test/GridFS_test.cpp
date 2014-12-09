// 2014-11-13T11:36+08:00
#include <chrono>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
# include <WinSock2.h>
#endif

#include <mongo/client/dbclient.h>
#include <mongo/client/gridfs.h>

namespace Chrono = std::chrono;

//! Do benchmark test on a function object.
//!
//! \param func a function object with no arguments
//! \param times repeat times
//! \param os output stream where the result will be dumped
//! \return no return value
//!
//! If you want to do benchmark test on a function with one or more arguments, 
//! you can create a function object which receive no arguments with std::bind 
//! and then pass it to this function.
//! A more amazing function for doing similar thing by wichtounet is here:
//! https://github.com/wichtounet/articles/blob/master/include/bench.hpp
//! orz!
template <typename Ret>
void benchmark(const std::function<Ret ()> &func, 
    const std::size_t &times = 1, std::ostream &os = std::cout)
{
    using Clock = Chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    auto CalcTimeSpan = [](const TimePoint &start, const TimePoint &end) {
        return std::chrono::duration_cast<Chrono::duration<double>>(
            end - start).count();
    };

    //!< ----------------------------------------------------
    os << std::string(79, '-') << '\n';

    TimePoint t0 = Clock::now();

    for (std::size_t i = 0; i < times; ++i) {
        TimePoint tp0 = Clock::now();
        auto res = func();
        TimePoint tp1 = Clock::now();

        os << '[' << i << "] Return value: " << res
            << ", time elapsed: " << CalcTimeSpan(tp0, tp1) << " s\n";
    }

    TimePoint t1 = Clock::now();

    double timeElapsed = CalcTimeSpan(t0, t1);
    os << "Time totally used: " << timeElapsed  << " s, averagely used: " 
        << timeElapsed / (times > 0 ? times : 1) << " s\n";

    os << std::string(79, '-') << '\n';
    //!< ----------------------------------------------------
}

//! Do GridFS "put" test.
//!
//! \param client reference to a Mongo client connection instance
//! \param dbName root database name
//! \param collectionName target collection name
//! \param fileName name of local file to be put
//! \return true if successfully, otherwise false
bool putTest(mongo::DBClientBase &client, 
    const std::string &dbName, const std::string &collectionName, 
    const std::string &fileName)
{
    try {
        mongo::GridFS gridfs(client, dbName, collectionName);
        mongo::BSONObj file = gridfs.storeFile(fileName);
        mongo::GridFile gridFile = gridfs.findFile(file);
        std::cout << "\"put\" successfully! File MD5: " 
            << gridFile.getMD5() << std::endl;
    } catch (const mongo::OperationException &e) {
        std::cerr << "\"put\" failed! Caught: " << e.what() << '\n';
        return false;
    }

    return true;
}

bool putTest(mongo::DBClientBase &client, 
    const std::string &dbName, const std::string &fileName)
{
    return putTest(client, dbName, "fs", fileName);
}

//! Do GridFS "get" test.
//!
//! \param client reference to a Mongo client connection instance
//! \param dbName root database name
//! \param collectionName target collection name
//! \param remoteName name of the remote file to be get
//! \param targetName name of local file to be saved
//! \return true if successfully, otherwise false
bool getTest(mongo::DBClientBase &client, 
    const std::string &dbName, const std::string &collectionName,
    const std::string &remoteName, const std::string &targetName)
{
    try {
        mongo::GridFS gridfs(client, dbName, collectionName);
        mongo::GridFile gridout = gridfs.findFileByName(remoteName);
        mongo::gridfs_offset fileSize = gridout.write(targetName);
        std::cout << "\"get\" successfully. File size: " << fileSize << '\n';
    } catch (const mongo::OperationException &e) {
        std::cerr << "\"get\" failed! Caught: " << e.what() << '\n';
        return false;
    }

    return true;
}

bool getTest(mongo::DBClientBase &client, const std::string &dbName,
    const std::string &remoteName, const std::string &targetName)
{
    return getTest(client, dbName, "fs", remoteName, targetName);
}

int main(int argc, char *argv[])
{
    //!< Initialize the client driver
    mongo::Status res = mongo::client::initialize();
    if (!res.isOK()) {
        std::cerr << "Initializing failed: " << res.codeString() << '\n';
        return EXIT_FAILURE;
    }

    const std::string dbName = "mongo_GridFS_test";
    const std::string fileName = "d:\\a.dat";

    //!< Connect to MongoDB server
    mongo::DBClientConnection client;
    try {
        client.connect("localhost");
        std::cout << "Connected OK!\n";
    } catch (const mongo::DBException &e) {
        std::cerr << "Connected failed: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    //!< GridFS put test
    benchmark<bool>(
        std::bind(static_cast<bool(*)(mongo::DBClientBase &, 
                                      const std::string &, 
                                      const std::string &)>(putTest),
            std::ref(client), std::cref(dbName), std::cref(fileName)),
        1, std::cout);

    //!< GridFS get test
    benchmark<bool>(
        std::bind(static_cast<bool(*)(mongo::DBClientBase &, 
                                      const std::string &,
                                      const std::string &, 
                                      const std::string &)>(getTest), 
            std::ref(client), std::cref(dbName), std::cref(fileName), std::cref(fileName)), 
        1, std::cout);

    client.dropDatabase(dbName);

#if defined(_MSC_VER) && !defined(NDEBUG)
    std::system("pause");
#endif
    return EXIT_SUCCESS;
}

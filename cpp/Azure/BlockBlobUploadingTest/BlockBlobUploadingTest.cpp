// 2014-12-17T13:31+08:00
// 2015-01-23T09:15+08:00

// An example for testing Azure Storage CPP SDK. 
// Several official examples can be found here:
// https://github.com/Azure/azure-storage-cpp/blob/master/Microsoft.WindowsAzure.Storage/samples/

#include <cassert>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
//#include <locale>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/progress.hpp>

#include <cpprest/filestream.h>

#include <wascore/basic_types.h>
#include <was/blob.h>
#include <was/common.h>
#include <was/storage_account.h>

#ifdef _MSC_VER
# ifdef NDEBUG
#  pragma comment(lib, "cpprest120_2_3.lib") // cpprest SDK for VS2013
# else
#  pragma comment(lib, "cpprest120d_2_3.lib") // cpprest SDK for VS2013
# endif

# pragma comment(lib, "wastorage.lib")
#endif

#include "../../common.h"

namespace AS = azure::storage;
namespace Opt = boost::program_options;

struct Options {
    utility::string_t accountName;
    utility::string_t primaryAccessKey;
    utility::string_t secondaryAccessKey;
    utility::string_t endPoint;
    bool useHttps;
    bool useDevStorage;
};

template <typename charT>
int parseCmdlineArgs(const std::vector<std::basic_string<charT>> &vargs, Options &options)
{
    if (vargs.empty()) {
        ucerr << U("At least one command line argument is expected.\n");
        return EXIT_FAILURE;
    }

    try {
        // Declare a group of options that will be allowed only on command line.
        Opt::options_description genericOptions("Generic options");
        std::string configFileName;
        genericOptions.add_options()
            ("config-file,c", Opt::value<std::string>(&configFileName), "Configuration file path")
            ("help,h", "Display this information")
            ;

        // Declare a group of options that will be allowed both on command line and
        // in configuration file.
        Opt::options_description configOptions("Configuration options");
        configOptions.add_options()
            ("account-name,a", Opt::wvalue<utility::string_t>(&options.accountName), "Azure storage account name")
            ("primary-key,p", Opt::wvalue<utility::string_t>(&options.primaryAccessKey), "The primary access key")
            ("secondary-key,s", Opt::wvalue<utility::string_t>(&options.secondaryAccessKey), "The secondary access key")
#if 0
            ("end-point,e", Opt::wvalue<utility::string_t>(&options.endPoint)->default_value(U("core.windows.net")), "Endpoint suffix")
#else
            ("end-point,e", Opt::wvalue<utility::string_t>(&options.endPoint)->default_value(U("core.windows.net"), "core.windows.net"), "Endpoint suffix")
#endif
            ("use-https", Opt::value<bool>(&options.useHttps), "Use \"HTTPS\" rather than \"HTTP\"")
            ("use-dev-storage", Opt::value<bool>(&options.useDevStorage), "Use development storage account")
            ;

        Opt::variables_map argsMap;
        Opt::store(Opt::basic_command_line_parser<charT>(vargs).options(genericOptions).allow_unregistered().run(), argsMap);
        Opt::notify(argsMap);

        if (vargs.size() < 2 || argsMap.count("help")) {
            std::cout << "Usage: " << getProgName(vargs[0]) << " [options]\n";
            std::cout << Opt::options_description().add(genericOptions).add(configOptions) << std::endl;
            std::cout << "If \"--help\" is provided, then all other options will be ignored.\n"
                "If \"--config-file\" is provided, then all \"Configuration options\""
                " will be read from the specified configuration file.\n" << std::endl;
            return EXIT_FAILURE;
        }

        if (argsMap.count("config-file")) {
            std::ifstream configFileStream(configFileName);
            if (configFileStream) {
                Opt::store(Opt::parse_config_file(configFileStream, configOptions, true), argsMap);
                Opt::notify(argsMap);
            } else {
                std::cerr << "Open configuration file \"" << configFileName << "\" failed.\n";
            }
        } else {
            //Opt::store(Opt::parse_command_line<charT>(argc, argv, configOptions), argsMap);
            Opt::store(Opt::basic_command_line_parser<charT>(vargs).options(configOptions).run(), argsMap);
            Opt::notify(argsMap);
        }
    } catch (const std::exception &e) {
        RETURN_ON_FAILURE_MSG("exception");
    }

    return 0;
}

template <typename charT>
int parseCmdlineArgs(int argc, charT *argv[], Options &options)
{
    assert(argv != nullptr);
    std::vector<std::basic_string<charT>> vargs;
    for (int i = 0; i < argc; ++i) {
        vargs.push_back(argv[i]);
    }

    return parseCmdlineArgs(vargs, options);
}

void uploadBlockBlobFromFile(AS::cloud_blob_container &container, 
    const utility::string_t &filePath, utility::size64_t uploadSizeEachTime)
{
    if (!boost::filesystem::exists(filePath) || !boost::filesystem::is_regular_file(filePath)) {
        ucerr << U('"') << filePath << U('"') << U(" doesn't exist or is not a regular file.\n");
        return;
    }

    auto blob = container.get_block_blob_reference(
        boost::filesystem::path(filePath).filename().native());

    boost::progress_timer t;

#if 1
    utility::size64_t fileSize = boost::filesystem::file_size(filePath);
    if (0 == fileSize) {
        blob.upload_from_file(filePath);
        return;
    }

    assert(uploadSizeEachTime > 0);
    if (uploadSizeEachTime == 0 || uploadSizeEachTime > fileSize) {
        uploadSizeEachTime = fileSize;
    }

    std::vector<std::uint8_t> buffer(uploadSizeEachTime);

    utility::string_t blockId;
    std::uint64_t blockIndex = std::time(NULL);
    std::vector<AS::block_list_item> blockList;

    // Since concurrency::streams::basic_istream doesn't provide us a "read" method looks like this:
    //   istream& read (char* s, streamsize n);
    // so, I use std::ifstream instead.
    std::ifstream inFile(filePath, std::ifstream::binary);
    if (!inFile) {
        ucout << U("Opening file \"") << filePath << U("\" failed.\n");
        return;
    }

    // Now, start the uploading process. If we want to upload a single block each time, then:
    //   C#:     PutBlock, PutBlockList
    //   Python: put_block, put_block_list
    //   Java:   uploadBlock, commitBlockList
    //   C++:    upload_block, upload_block_list
    ucout << U("Uploading file: ") << filePath << U("...");
    boost::progress_display prog(fileSize);

    bool uploading = true;
    while (uploading) {
        // Generate an unique block id
        blockId = utility::conversions::to_base64(blockIndex++);
        // Read data
        inFile.read(reinterpret_cast<char *>(buffer.data()), uploadSizeEachTime);
        if (!inFile) {
            auto bytesRead = inFile.gcount();
            if (bytesRead > 0) {
                buffer.resize(bytesRead);
                uploading = false;
            } else {
                break;
            }
        }
        // Upload the current block
        auto tmpStream = concurrency::streams::bytestream::open_istream(buffer);
        blob.upload_block(blockId, tmpStream, U(""));
        // Record the block id for following upload_block_list call
        blockList.push_back(AS::block_list_item(blockId));
        // Upgrate the progress bar
        prog += inFile.gcount();
    }

    // The last step...
    blob.upload_block_list(blockList);
#elif 0
    blob.upload_from_file(filePath);
#elif 0
    auto inStream = concurrency::streams::fstream::open_istream(filePath).get();
    blob.upload_from_stream(inStream);
    inStream.close().wait();
#endif
}

void downloadBlockBlobToFile(AS::cloud_blob_container &container,
    const utility::string_t &blobName, const utility::string_t &targetFileName, 
    utility::size64_t downloadSizeEachTime)
{
    auto blob = container.get_block_blob_reference(blobName);
    if (!blob.exists()) {
        ucerr << U("Specified block blob \"") << blobName << U("\" doesn't exist.\n");
        return;
    }

    boost::progress_timer t;

    // Get blob's size(in bytes)
    auto properties = blob.properties();
    auto blobSize = properties.size();

    if (0 == blobSize) {
        blob.download_to_file(targetFileName);
        return;
    }

    assert(downloadSizeEachTime > 0);
    if (downloadSizeEachTime == 0 || downloadSizeEachTime > blobSize) {
        downloadSizeEachTime = blobSize;
    }

    std::ofstream outFile(targetFileName, std::ofstream::binary);
    if (!outFile) {
        ucout << U("Opening file \"") << targetFileName << U("\" failed.\n");
        return;
    }

    ucout << U("Downloading file to: ") << targetFileName << U("...");
    boost::progress_display prog(blobSize);

    utility::size64_t offset = 0;
    utility::size64_t bytesRead;
    while (offset < blobSize) {
        // Create a memory buffer
        concurrency::streams::container_buffer<std::vector<uint8_t>> buffer;
        // Read data
        concurrency::streams::ostream tmpOutStream(buffer);
        blob.download_range_to_stream(tmpOutStream, offset, downloadSizeEachTime);
        bytesRead = buffer.collection().size();
        // Write out...
        outFile.write(reinterpret_cast<char *>(buffer.collection().data()), bytesRead);
        //outFile.flush();
        // Upgrade the progress bar and other states
        prog += bytesRead;
        offset += bytesRead;
    }

    // The last step...
    blob.download_block_list();
}

int main(int argc, char *argv[])
{
    //std::locale::global(std::locale(""));

    try {
        Options options;
#ifdef NDEBUG
        if (int rc = parseCmdlineArgs(argc, argv, options)) {
            return rc;
        }
#else
        // _DEBUG
        std::vector<std::string> args {argv[0], std::string("--config-file=") + getProgName(argv[0]) + ".cfg"};
        if (int rc = parseCmdlineArgs(args, options)) {
            return rc;
        }
#endif

        AS::cloud_storage_account asAccount;
        // initialize the storage account
#if 1
        try {
            if (options.useDevStorage) {
                // If you want to use a development storage account, please read this article: 
                // Using the Azure Storage Emulator for Development and Testing
                // http://msdn.microsoft.com/en-us/library/azure/hh403989.aspx
                asAccount = AS::cloud_storage_account::development_storage_account();
            } else {
                AS::storage_credentials credential(options.accountName, options.primaryAccessKey);
                asAccount = AS::cloud_storage_account(credential, options.endPoint, options.useHttps);
            }
        } catch (const std::exception &e) {
            RETURN_ON_FAILURE_MSG("Creating storage account object failed");
        }
#else
        // The workflow of parse:
        //   1. parse_devstore_settings
        //   2. parse_defaults_settings
        //   3. parse_explicit_settings
        // In cloud_storage_account.cpp, we can see all the valid setting strings.
        utility::string_t connStr;
        if (options.useDevStorage) {
            connStr = U("UseDevelopmentStorage=true;DevelopmentStorageProxyUri=;");
        } else {
            connStr =
                utility::string_t(U("DefaultEndpointsProtocol=")) + (options.useHttps ? U("https;") : U("http;")) +
                U("AccountName=") + options.accountName + U(";") +
                U("AccountKey=") + options.primaryAccessKey + U(";") +
                U("EndpointSuffix=") + options.secondaryAccessKey + U(";");
        }

        try {
            asAccount = AS::cloud_storage_account::parse(connStr);
        } catch (const std::exception &e) {
            RETURN_ON_FAILURE_MSG("Parsing connection string failed");
        }
#endif

        AS::blob_request_options reqOptions;
        reqOptions.set_stream_read_size_in_bytes(1024 * 1024);
        reqOptions.set_stream_write_size_in_bytes(1024 * 1024 * 4);
        //reqOptions.set_server_timeout(std::chrono::seconds(5));

        AS::cloud_blob_client blobClient = asAccount.create_cloud_blob_client(reqOptions);
        // Caution:
        // A container name must be a valid DNS name. Please read the naming convention described here:
        // http://msdn.microsoft.com/en-us/library/azure/dd135715.aspx
        AS::cloud_blob_container container = blobClient.get_container_reference(U("myd7349"));

        container.create_if_not_exists();

        // Set access permission
        AS::blob_container_permissions permission;
        permission.set_public_access(AS::blob_container_public_access_type::blob);
        container.upload_permissions(permission);

#if 0
        // Upload files
        //for (int i = 1; i < argc; ++i) {
            //utility::string_t filePath = utility::conversions::to_utf16string(argv[i]);
        utility::string_t filePath = U("e:\\MIT_sixsense.mp4"); // U("d:\\20120929152243.dat");
            uploadBlockBlobFromFile(container, filePath, reqOptions.stream_write_size_in_bytes());
        //}
#else
        utility::string_t blobName = U("MIT_sixsense.mp4");
        utility::string_t targetFileName = U("d:\\MIT_sixsense.mp4");
        downloadBlockBlobToFile(container, blobName, targetFileName, 1024 * 1024);
#endif
    } catch (const AS::storage_exception &e) {
        RETURN_ON_FAILURE_MSG("storage_exception");
    } catch (const std::exception &e) {
        RETURN_ON_FAILURE_MSG("exception");
    } catch (...) {
        std::cerr << "Unknown exception!\n";
        return EXIT_FAILURE;
    }

    PAUSE();
    return EXIT_SUCCESS;
}

// References:
// [In Boost::Program_Options, how to set default value for wstring?](http://stackoverflow.com/questions/6921196/in-boostprogram-options-how-to-set-default-value-for-wstring)
// [istream and ostream with shared streambuf mutually thread-safe for duplex I/O?](http://stackoverflow.com/questions/9963413/istream-and-ostream-with-shared-streambuf-mutually-thread-safe-for-duplex-i-o)
// [Understanding Block Blobs and Page Blobs](http://msdn.microsoft.com/en-us/library/azure/ee691964.aspx)
// [Windows Azure: 使用Blob的PutBlock实现大文件断点续传](http://www.cnblogs.com/lijiawei/archive/2013/01/18/2866756.html)

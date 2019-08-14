#include <cassert>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#ifndef NDEBUG
# include <typeinfo>
#endif

#include <plf_nanotimer.h> // vcpkg install plf-nanotimer

#include "packed_data.pb.h"


namespace stdfs = std::experimental::filesystem;


#ifndef BASE_TYPE
# define BASE_TYPE std::int32_t
#endif


template <typename T>
std::vector<T> ReadData(const char *file)
{
    assert(file != nullptr);

    auto fileSize = std::experimental::filesystem::file_size(file);

    std::ifstream inStream(file, std::ios::binary);
    if (inStream.is_open())
    {
        auto howManyInts = static_cast<typename std::vector<T>::size_type>(fileSize / sizeof(T));
        std::vector<T> data(howManyInts);
        
        inStream.read(reinterpret_cast<char *>(data.data()), howManyInts * sizeof(T));
        inStream.close();

        return data;
    }
    else
    {
        return std::vector<T>();
    }
}


template <typename T>
PackedData PackData(const char *file)
{
    auto data = ReadData<T>(file);

    PackedData packedData;
    packedData.mutable_data()->Reserve(data.size());

    for (auto num : data)
        packedData.add_data(num);

    return packedData;
}


int main(int argc, char **argv)
{
#ifndef NDEBUG
    std::cout << "Base type: " << typeid(BASE_TYPE).name() << ", size: " << sizeof(BASE_TYPE) << "\n\n";
#endif

    for (int i = 1; i < argc; ++i)
    {
        std::vector<stdfs::path> files;

        auto isDir = stdfs::is_directory(argv[i]);
        if (isDir)
        {
            std::copy_if(
                stdfs::directory_iterator(argv[i]),
                stdfs::directory_iterator(),
                std::back_inserter(files),
                [](const stdfs::path &path) { return stdfs::is_regular_file(path); }
            );
        }
        else
        {
            files.push_back(argv[i]);
        }

        for (auto &filePath : files)
        {
            std::cout << '\n';

            plf::nanotimer timer;

            timer.start();
            auto packedData = PackData<BASE_TYPE>(filePath.string().c_str());
            auto elapsedMs = timer.get_elapsed_ms();

            std::cout << "It took " << elapsedMs << "ms to pack file " << filePath << '\n';

            auto packedFilePath = filePath;
            packedFilePath.remove_filename();
            packedFilePath /= "packed";
            if (!stdfs::exists(packedFilePath))
            {
                stdfs::create_directories(packedFilePath);
                std::cout << "Creating directory " << packedFilePath << '\n';
            }
            packedFilePath /= filePath.filename();
            packedFilePath.concat(".packed");
            
            std::ofstream outStream(packedFilePath, std::ios::binary);
            if (outStream.is_open())
            {
                timer.start();
                packedData.SerializeToOstream(&outStream);
                elapsedMs = timer.get_elapsed_ms();

                outStream.close();

                std::cout << "It took " << elapsedMs << "ms to serialize packed data to file " << packedFilePath << '\n';

                auto fileSize = stdfs::file_size(filePath);
                auto packedFileSize = stdfs::file_size(packedFilePath);

                std::cout << "Original: " << fileSize << " bytes.\n";

                if (fileSize > 0)
                {
                    std::cout << "Packed: " << packedFileSize << " bytes ("
                        << packedFileSize / static_cast<double>(fileSize) * 100.0 << "% of original)\n";
                }
                else
                {
                    std::cout << "Packed: " << packedFileSize << " bytes\n";
                }
            }
            else
            {
                std::cerr << "Failed to open file for writing: " << packedFilePath << '\n';
            }
        }
    }

    return 0;
}


// References:
// https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c
// https://stackoverflow.com/questions/4875482/how-to-turn-const-boostfilesystem2path-into-const-char

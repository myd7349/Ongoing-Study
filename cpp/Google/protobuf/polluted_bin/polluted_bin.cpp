#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>

#include <google/protobuf/util/json_util.h>

#include "person.pb.h"


std::vector<std::uint8_t> GenerateRandomBytes(std::random_device &rd, std::vector<std::uint8_t>::size_type count)
{
    std::vector<std::uint8_t> bytes(count);
    std::uniform_int_distribution<std::uint16_t> dist(0, std::numeric_limits<std::uint8_t>::max());
    std::generate(bytes.begin(), bytes.end(), [&rd, &dist]() { return static_cast<std::uint8_t>(dist(rd)); });
    return bytes;
}


int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    Person person;
    person.set_name("John Doe");
    person.set_id(1234);
    person.set_email("jdoe@example.com");

    auto phone = person.add_phone();
    phone->set_type(Person_PhoneType_HOME);
    phone->set_number("010-12345");

    phone = person.add_phone();
    phone->set_type(Person_PhoneType_MOBILE);
    phone->set_number("12345678910");

    int messageSize = -1;

    const char *fileName = "polluted_bin.dat";

    std::ofstream outStream(fileName, std::ios::binary);
    if (outStream.is_open())
    {
        person.SerializeToOstream(&outStream);

        std::cout << person.ByteSize() << std::endl;
        std::cout << outStream.tellp() << std::endl;

        // Now write some random bytes at the end
        std::random_device rd;
        auto randomBytes = GenerateRandomBytes(rd, 42);

#if 1
        messageSize = person.ByteSize();

        outStream.write(reinterpret_cast<const char *>(randomBytes.data()), randomBytes.size());

        outStream.close();
#elif 0
        outStream.close();

        messageSize = static_cast<int>(std::experimental::filesystem::file_size("polluted_bin.dat"));

        outStream.open(fileName, std::ios::in | std::ios::binary | std::ios::ate); // std::ios::in is important here!
        if (outStream.is_open())
        {
            outStream.write(reinterpret_cast<const char *>(randomBytes.data()), randomBytes.size());
            outStream.close();
        }
#else
        outStream.close();
#endif
    }

    auto PrintPersonAsJson = [](const Person &p)
    {
        std::string json;

        google::protobuf::util::JsonPrintOptions options;
        options.add_whitespace = true;
        options.always_print_primitive_fields = true;

        google::protobuf::util::MessageToJsonString(p, &json, options);

        std::cout << json << std::endl;
    };

    PrintPersonAsJson(person);

    std::ifstream inStream(fileName, std::ios::binary);
    if (inStream.is_open())
    {
        std::cout << inStream.tellg() << std::endl;

        if (person.ParseFromIstream(&inStream))
        {
            PrintPersonAsJson(person);
        }
        else
        {
            std::cerr << "Failed to read data from polluted data bin!\n";

            if (inStream.fail())
            {
                std::cerr << inStream.bad() << ", " << inStream.eof() << ", " << inStream.fail() << '\n';
                // If we do not call clear() here, seekg will reads -1.
                inStream.clear();
            }

            if (messageSize > 0)
            {
                std::cerr << "I will only read the first " << messageSize << " bytes and try again!\n";

                std::vector<std::uint8_t> rawMessage(messageSize);

                if (!inStream.seekg(0/*, std::ios::beg*/))
                    std::cerr << "Failed to seek to the beginning of the file!\n";

                inStream.read(reinterpret_cast<char *>(rawMessage.data()), rawMessage.size());
                if (!inStream)
                {
                    std::cerr << "Failed to read the first " << messageSize << " bytes!\n";
                }
                else
                {
                    if (person.ParseFromArray(rawMessage.data(), rawMessage.size()))
                        PrintPersonAsJson(person);
                    else
                        std::cerr << "Failed again! I have no idea what to do next.\n";
                }
            }
        }

        inStream.close();
    }

    return 0;
}


// References:
// https://stackoverflow.com/questions/28999745/stdofstream-with-stdate-not-opening-at-end
// https://stackoverflow.com/questions/37780120/protobuf-causes-segmentation-fault-on-parsefromistream

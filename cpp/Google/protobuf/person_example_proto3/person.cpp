#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include <google/protobuf/util/json_util.h>

#include "person.pb.h"


std::string ReadContents(const char *file)
{
    assert(file != nullptr);

    std::string contents;

    std::ifstream in_stream(file);
    if (in_stream.is_open())
    {
        std::string line;

        while (std::getline(in_stream, line))
            contents += line;
    }

    return contents;
}


int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    auto PrintPersonAsJson = [](const Person &p)
    {
        std::string json;

        google::protobuf::util::JsonPrintOptions options;
        options.add_whitespace = true;
        //options.always_print_primitive_fields = true;

        google::protobuf::util::MessageToJsonString(p, &json, options);

        std::cout << json << std::endl;
    };

    {
        Person person;
        person.set_name("John Doe");
        person.set_id(1234);
        person.set_email("jdoe@example.com");

        auto phone = person.add_phone();
        phone->set_type(Person_PhoneType_HOME);
        phone->set_number("010-12345");

        phone = person.add_phone();
        phone->set_type(Person_PhoneType_MOBILE); // MOBILE will not be printed.
        phone->set_number("12345678910");

        phone = person.add_phone();
        phone->set_type(Person_PhoneType_WORK);
        phone->set_number("010-11111");

        std::ofstream out_stream("person.dat", std::ios::binary);
        if (out_stream.is_open())
            person.SerializeToOstream(&out_stream);

        PrintPersonAsJson(person);
    }

    {
        std::ifstream in_stream("person.dat", std::ios::binary);
        if (in_stream.is_open())
        {
            Person person;
            person.ParseFromIstream(&in_stream);

            std::cout << "Name: " << person.name() << std::endl;
            std::cout << "Email: " << person.email() << std::endl;

            PrintPersonAsJson(person);
        }
    }

    return 0;
}


// References:
// https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c

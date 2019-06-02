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
    {
        Person person;
        person.set_name("John Doe");
        person.set_id(1234);
        person.set_email("jdoe@example.com");

        std::ofstream out_stream("person.dat", std::ios::binary);
        if (out_stream.is_open())
           person.SerializeToOstream(&out_stream);
   }

   {
        std::ifstream in_stream("person.dat", std::ios::binary);
        if (in_stream.is_open())
        {
            Person person;
            person.ParseFromIstream(&in_stream);
    
            std::cout << "Name: " << person.name() << std::endl;
            std::cout << "Email: " << person.email() << std::endl;

            std::string json;
            google::protobuf::util::MessageToJsonString(person, &json);
            std::cout << json << std::endl;
        }
    }

   {
       std::string contents = ReadContents("person_with_email.json");
       Person person;
       if (google::protobuf::util::JsonStringToMessage(contents, &person) != google::protobuf::util::Status::OK)
       {
           std::cerr << "Failed to parse message from json file.\n";
       }
       else
       {
           std::cout << "Name: " << person.name() << std::endl;
           std::cout << "Email: " << person.email() << std::endl;
           std::cout << "Id: " << person.id() << std::endl;
       }
   }

   {
       std::string contents = ReadContents("person_without_email.json");
       Person person;
       if (google::protobuf::util::JsonStringToMessage(contents, &person) != google::protobuf::util::Status::OK)
       {
           std::cerr << "Failed to parse message from json file.\n";
       }
       else
       {
           std::cout << "Name: " << person.name() << std::endl;
           std::cout << "Email: " << person.email() << std::endl;
           std::cout << "Id: " << person.id() << std::endl;
       }
   }

   {
       std::string contents = ReadContents("person_ill_formed.json");
       Person person;
       auto status = google::protobuf::util::JsonStringToMessage(contents, &person);
       if (status != google::protobuf::util::Status::OK)
           std::cerr << "Failed to parse message from json file: " << status.ToString() << '\n';
   }

    return 0;
}


// References:
// https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c

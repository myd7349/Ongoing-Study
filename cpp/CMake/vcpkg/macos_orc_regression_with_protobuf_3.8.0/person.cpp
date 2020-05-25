#include <fstream>
#include <iostream>
#include <string>

#include <google/protobuf/util/json_util.h>

#include "person.pb.h"


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

    return 0;
}

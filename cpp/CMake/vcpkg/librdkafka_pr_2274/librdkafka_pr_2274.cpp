#include <iostream>

#include <librdkafka/rdkafkacpp.h>


#define STR_IMPL(c) #c
#define STR(c) STR_IMPL(c)

#define TOPIC_MACRO_DUMP(macro) \
    std::cout << STR(macro) << ": " << RdKafka::Topic::macro << std::endl;


int main()
{
    TOPIC_MACRO_DUMP(PARTITION_UA);
    TOPIC_MACRO_DUMP(OFFSET_BEGINNING);
    TOPIC_MACRO_DUMP(OFFSET_END);
    TOPIC_MACRO_DUMP(OFFSET_STORED);
    TOPIC_MACRO_DUMP(OFFSET_INVALID);
    
    return 0;
}


// References:
// https://github.com/edenhill/librdkafka/pull/2274

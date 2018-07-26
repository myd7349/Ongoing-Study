#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"


namespace rapidjson
{
    typedef GenericDocument<rapidjson::UTF16<>>     WDocument;
    typedef GenericValue<rapidjson::UTF16<>>        WValue;
    typedef GenericStringBuffer<UTF16<>>            WStringBuffer;
    typedef Writer<WStringBuffer, UTF16<>, UTF16<>> WWriter;
}

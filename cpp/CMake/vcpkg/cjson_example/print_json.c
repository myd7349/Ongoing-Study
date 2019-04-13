#include <stdio.h>
#include <stdlib.h>

#include <cjson/cJSON.h>
#include <cjson/cJSON_Utils.h>


int main()
{
    const char *json_str =
        "{"
        "  \"DateTime\": \"2018-07-26 15:31:47\","
        "  \"Events\": ["
        "     {"
        "       \"ID\": 0,"
        "       \"Name\": \"Copy\""
        "     },"
        "     {"
        "       \"ID\": 1,"
        "       \"Name\": \"Paste\""
        "     }"
        "   ]"
        "}"
        ;

    cJSON *json = cJSON_Parse(json_str);
    if (json != NULL)
    {
        char *string = cJSON_Print(json);
        if (string != NULL)
        {
            puts(string);
            free(string);
        }

        cJSON *copy_object = cJSONUtils_GetPointer(json, "/Events/0");
        if (copy_object != NULL)
        {
            string = cJSON_Print(copy_object);
            if (string != NULL)
            {
                puts(string);
                free(string);
            }

            cJSON_Delete(copy_object);
        }

        cJSON_Delete(json);
        json = NULL;
    }

    return 0;
}

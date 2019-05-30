#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <json-c/json_c_version.h>
#include <json-c/json_pointer.h>
#include <json-c/json_util.h>


#if defined(__linux)
# include <linux/limits.h>
# define _MAX_PATH PATH_MAX
#elif defined(_MSC_VER)
#else
# error _MAX_PATH not defined!
#endif


const char *get_app_path(const char *argv0, char path[_MAX_PATH])
{
    const char* slash = strrchr(argv0, '/');
    size_t path_len;

    assert(argv0 != NULL);
    assert(path != NULL);

#ifdef _WIN32
    if (slash == NULL)
        slash = strrchr(argv0, '\\');
#endif

    if (slash == NULL)
    {
        path[0] = '\0';
        return path;
    }

    path_len = slash - argv0 + 1;
    if (path_len > _MAX_PATH - 1)
    {
        path[0] = '\0';
        return path;
    }

    strncpy(path, argv0, path_len);
    path[path_len] = '\0';

    return path;
}


int main(int argc, char **argv)
{
    struct json_object *json = NULL;
    struct json_object *obj = NULL;

    const char *json_str = NULL;

    char path[_MAX_PATH];

    printf("App path: %s\n", get_app_path(argv[0], path));
    printf("JSON path: %s\n", strcat(path, "example.json"));

    printf("json-c version: %s\n", json_c_version());

    json = json_object_from_file(path);
    if (json == NULL)
    {
        fprintf(stderr, "Failed to parse json file example.json.\n");
        return EXIT_FAILURE;
    }

    json_str = json_object_to_json_string_ext(json, JSON_C_TO_STRING_PRETTY);
    printf("%s\n", json_str);

    if (json_pointer_get(json, "/DateTime", &obj) == 0)
    {
        json_str = json_object_to_json_string(obj);
        printf("%s\n", json_str);
    }

    return 0;
}


// References:
// https://stackoverflow.com/questions/9449241/where-is-path-max-defined-in-linux
// https://github.com/google/glog/blob/ba8a9f6952d04d1403b97df24e6836227751454e/src/utilities.cc#L345-L358

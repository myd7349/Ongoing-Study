#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef HAVE_GETLINE
# include <string.h>
# define MAXMIMUM_LINE_LENGTH 4096
#endif

#ifdef _WIN32
# include <fcntl.h>
# include <io.h>
#endif

#include <yyjson.h>


#define ERROR_IMPL(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#define ERROR(fmt, ...) ERROR_IMPL("%s(%d)> " fmt, __FILE__, __LINE__, __VA_ARGS__)


char *prettify(yyjson_doc *json)
{
    yyjson_write_flag write_flags = YYJSON_WRITE_PRETTY | YYJSON_WRITE_ESCAPE_UNICODE;
    assert(json != NULL);
    return yyjson_write(json, write_flags, 0);
}


void prettify_json(yyjson_doc *json)
{
    char *output = prettify(json);
    if (output != NULL)
    {
        printf("%s", output);
        free(output);
    }
    else
    {
        ERROR("Failed to prettify input json document.\n");
    }
}


int main(int argc, char *argv[])
{
    yyjson_doc *document;
    yyjson_read_flag read_flags = YYJSON_READ_ALLOW_COMMENTS | YYJSON_READ_ALLOW_TRAILING_COMMAS;
    yyjson_read_err error;

    int i;

#ifdef HAVE_GETLINE
    char *line;
#else
    char line[MAXMIMUM_LINE_LENGTH];
#endif
    size_t line_length;

#ifdef _WIN32
    // Prevent Windows converting between CR+LF and LF
    _setmode(_fileno(stdin), _O_BINARY);
    _setmode(_fileno(stdout), _O_BINARY);
#endif

    if (argc > 1)
    {
        for (i = 1; i < argc; ++i)
        {
            document = yyjson_read_file(argv[i], read_flags, NULL, &error);
            if (document != NULL)
            {
                prettify_json(document);
                yyjson_doc_free(document);
            }
            else
            {
                ERROR("yyjson_read_file failed to read file \"%s\". Code: %u, message: %s, position: %ld.\n",
                    argv[i], error.code, error.msg, error.pos);
            }
        }
    }
    else
    {
#ifdef HAVE_GETLINE
        while (getline(&line, &line_length, stdin) >= 0)
#else
        while (fgets(line, MAXMIMUM_LINE_LENGTH, stdin) != NULL)
#endif
        {
#ifndef HAVE_GETLINE
            line_length = strlen(line);
#endif

            document = yyjson_read_opts(line, line_length, read_flags, NULL, &error);
            if (document != NULL)
            {
                prettify_json(document);
                yyjson_doc_free(document);
            }
            else
            {
                ERROR("yyjson_read_opts failed. Code: %u, message: %s, position: %ld.\n",
                    error.code, error.msg, error.pos);
            }

#ifdef HAVE_GETLINE
            free(line);
#endif        
        }
    }

    return EXIT_SUCCESS;
}


// References:
// https://github.com/Tencent/rapidjson/blob/0d4517f15a8d7167ba9ae67f3f22a559ca841e3b/example/prettyauto/prettyauto.cpp#L19-L23

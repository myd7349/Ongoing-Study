#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <pb_encode.h>
#include <pb_decode.h>

#include "person.pb.h"


bool write_callback(pb_ostream_t *stream, const uint8_t *buf, size_t count)
{
    FILE *fp = (FILE *)stream->state;
    return fwrite(buf, 1, count, fp) == count;
}


bool read_callback(pb_istream_t *stream, uint8_t *buf, size_t count)
{
    FILE *fp = (FILE *)stream->state;
    bool status;

    if (buf == NULL)
    {
        while (count-- && fgetc(fp) != EOF)
        {
            ;
        }

        return count == 0;
    }

    status = fread(buf, 1, count, fp) == count;

    if (feof(fp))
        stream->bytes_left = 0;

    return status;
}


int main()
{
    {
        Person person = Person_init_zero;
        strcpy(person.name, "John Doe");
        person.id = 1234;
        strcpy(person.email, "jdoe@example.com");

        FILE *fp = fopen("person.dat", "wb");
        if (fp != NULL)
        {
            pb_ostream_t out_stream = { &write_callback, fp, SIZE_MAX, 0 };
            if (pb_encode(&out_stream, Person_fields, &person))
                printf("Total bytes: %zu\n", out_stream.bytes_written);
            else
                fprintf(stderr, "Encoding failed: %s\n", PB_GET_ERROR(&out_stream));

            fclose(fp);
        }
   }

   {
        FILE *fp = fopen("person.dat", "rb");
        if (fp != NULL)
        {
            pb_istream_t in_stream = { &read_callback, fp, SIZE_MAX };
            Person person = Person_init_zero;
            if (pb_decode(&in_stream, Person_fields, &person))
            {
                printf("Name: %s\n", person.name);
                printf("ID: %" PRIi32 "\n", person.id);

            }
            else
            {
                fprintf(stderr, "Decoding failed: %s\n", PB_GET_ERROR(&in_stream));
            }

            fclose(fp);
        }
    }

    return 0;
}

// References:
// https://github.com/nanopb/nanopb/tree/master/examples/simple

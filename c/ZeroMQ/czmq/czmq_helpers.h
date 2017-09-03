// 2017-09-01T15:38+08:00
#ifndef CZMQ_HELPERS_H_
#define CZMQ_HELPERS_H_

#include <czmq.h>

// Deprecated! Use zsys_set_logstream + zframe_print instead.
// Based on those code in zframe_print
static void
zframe_dump(zframe_t *frame, const char *prefix, const char *suffix)
{
    assert(frame);
    assert(zframe_is(frame));

    byte *data = zframe_data(frame);
    size_t size = zframe_size(frame);

    //  Probe data to check if it looks like unprintable binary
    int is_bin = 0;
    uint char_nbr;
    for (char_nbr = 0; char_nbr < size; char_nbr++)
        if (data[char_nbr] < 9 || data[char_nbr] > 127)
            is_bin = 1;

    char buffer[256] = "";
    size_t max_size = is_bin ? 35 : 70;
    const char *ellipsis = "";
    if (size > max_size) {
        size = max_size;
        ellipsis = "...";
    }
    for (char_nbr = 0; char_nbr < size; char_nbr++) {
        if (is_bin)
            sprintf(buffer + strlen(buffer), "%02X", (unsigned char)data[char_nbr]);
        else
            sprintf(buffer + strlen(buffer), "%c", data[char_nbr]);
    }
    strcat(buffer, ellipsis);

    printf("%s%s%s", prefix ? prefix : "", buffer, suffix ? suffix : "");
}



// Deprecated! Use zsys_set_logstream + zmsg_print instead.
static void
zmsg_dump_ex(zmsg_t *msg, const char *prefix, const char *delimiter, const char *suffix)
{
    zframe_t *frame = NULL;

    assert(msg);
    assert(zmsg_is(msg));

    if (!delimiter)
        delimiter = "|";

    printf("%s", prefix ? prefix : "");

    frame = zmsg_first(msg);
    while (frame != NULL) {
        zframe_dump(frame, NULL, delimiter);
        frame = zmsg_next(msg);
    }

    printf("%s", suffix ? suffix : "");
}

#endif // CZMQ_HELPERS_H_

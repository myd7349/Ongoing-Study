#include "circular_buffer.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>


#define CIRCBUF_TYPEID (0xC1AC0B1F)


struct circbuf_impl_t
{
    unsigned magic;
    size_t capacity;
    size_t elem_size;
    size_t head;
    size_t tail;
    void *data;
};


circbuf_t circbuf_new(size_t capacity, size_t elem_size)
{
    circbuf_t buf;

    assert(capacity >= 0 && capacity != CIRCBUF_INVALID_SIZE);
    assert(elem_size > 0);

    if (SIZE_MAX / elem_size < capacity)
        return NULL;

    buf = calloc(1, sizeof(struct circbuf_impl_t));
    if (buf == NULL)
        return NULL;

    buf->magic = CIRCBUF_TYPEID;

    if (capacity > 0)
    {
        buf->capacity = capacity;
        buf->data = calloc(capacity, elem_size);
        if (buf->data == NULL)
        {
            free(buf);
            return NULL;
        }
    }

    buf->elem_size = elem_size;

    return buf;
}


void circbuf_free(circbuf_t *pbuf)
{
    circbuf_t buf;

    if (pbuf != NULL)
    {
        buf = *pbuf;

        if (buf != NULL)
        {
            if (buf->data != NULL)
            {
                free(buf->data);
                buf->data = NULL;
            }

            free(buf);
            buf = NULL;
        }
    }
}


bool circbuf_is_valid(circbuf_t buf)
{
    return buf != NULL && buf->magic == CIRCBUF_TYPEID && buf->elem_size > 0;
}


size_t circbuf_capacity(circbuf_t buf)
{
    return circbuf_is_valid(buf) ? buf->capacity : CIRCBUF_INVALID_SIZE;
}


// References:
// https://en.wikipedia.org/wiki/Circular_buffer
// https://embedjournal.com/implementing-circular-buffer-embedded-c/
// https://github.com/EmbedJournal/c-utils
// https://www.boost.org/doc/libs/1_60_0/doc/html/atomic/usage_examples.html#boost_atomic.usage_examples.example_spinlock
// https://www.boost.org/doc/libs/1_39_0/libs/circular_buffer/doc/circular_buffer.html
// C Interfaces and Implementations, Chapter 12
// https://github.com/drh/cii/blob/master/src/ring.c
// E:\Qt\Qt5.9.0\5.9\Src\qtwebengine\src\3rdparty\chromium\third_party\webrtc\modules\audio_processing\echo_detector\circular_buffer.h
// processhacker-2.39-src\phlib\circbuf.c
// https://www.codeproject.com/articles/2880/circular-buffer-2

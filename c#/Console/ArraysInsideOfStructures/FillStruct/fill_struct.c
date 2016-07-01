#define FILL_STRUCT_EXPORTS
#include "fill_struct.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void FillStruct(struct Data *data)
{
    assert(data != NULL);

    data->header = 42;
    for (int i = 0; i < _countof(data->data); ++i)
        data->data[i] = _countof(data->data) - i;
}
#ifndef LRC_H_
#define LRC_H_

#include <stddef.h>
#include <stdint.h>

#include "../../algutils.h"


C_API_BEGIN

uint8_t lrc8(const void *buffer, size_t length);

C_API_END

#endif // LRC_H_

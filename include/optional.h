#pragma once

#include "common.h"

typedef struct Optional_t {
    void  *val;
    bool8  hasValue;
} Optional_t;

Optional_t NewOptional(void *val);
Optional_t NewOptionalWithNoValue();
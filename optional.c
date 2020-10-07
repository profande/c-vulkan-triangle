#include "optional.h"

Optional_t NewOptional(void *val) {
    Optional_t opt = { 0 };
    opt.val      = val;
    opt.hasValue = true;

    return opt;
}
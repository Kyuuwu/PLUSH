#ifndef PLUSH_CORE_EXCEPTIONS
#define PLUSH_CORE_EXCEPTIONS

#include <iostream>

namespace PLUSH {
    enum Exception{
        ENTITY_NOT_FOUND,
        INSTANCE_NOT_FOUND,
        LAYER_NOT_FOUND
    };

    void elaborateException(Exception e);
}

#endif
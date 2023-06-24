#ifndef PLUSH_HELPERS_EXCEPTIONS
#define PLUSH_HELPERS_EXCEPTIONS

namespace PLUSH_helpers {
    enum Exception{
        UNEXPECTED_EXCEPTION,
        FILE_READ_ERROR,
        FILE_INCOMPLETE,
        OUT_OF_RANGE,
        UNRECOGNIZED_KEY
    };
}

#endif
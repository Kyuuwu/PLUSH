#ifndef PLUSHGRAPHICSEXCEPTION_HPP
#define PLUSHGRAPHICSEXCEPTION_HPP

#include "PlushGraphics.hpp"

namespace PlushGraphics {
    enum class PlushGraphicsException{
        FAILED_TO_CREATE_WINDOW,
        OPENGL_TYPE_NOT_FOUND,
        OPENGL_VALUE_GET_INVALID_TYPE
    };
}

#endif // PLUSHGRAPHICSEXCEPTION_HPP

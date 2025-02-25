#ifndef READFILE_HPP
#define READFILE_HPP

#include "PlushUtil.hpp"

#include <string>
#include <sstream>

namespace PlushUtil {
    class ReadFile{
        public:
            static std::stringstream readFileIntoStringStream(std::string filePath);
            static std::string readFileIntoString(std::string filePath);
    };
}

#endif // READFILE_HPP

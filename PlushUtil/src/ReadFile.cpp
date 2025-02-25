#include "ReadFile.hpp"

#include "PlushUtilException.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace PlushUtil {
    std::stringstream ReadFile::readFileIntoStringStream(std::string filePath){
        std::ifstream fileStream;
        std::stringstream outputStream;

        // ensure ifstream objects can throw exceptions:
        fileStream.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            fileStream.open(filePath);
            // read file's buffer contents into streams
            outputStream << fileStream.rdbuf();
            // close file handlers
            fileStream.close();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
            throw(PlushUtil::PlushUtilException::FILE_READ_ERROR);
        }

        return outputStream;

    }

    std::string ReadFile::readFileIntoString(std::string filePath){
        return readFileIntoStringStream(filePath).str();
    }
}
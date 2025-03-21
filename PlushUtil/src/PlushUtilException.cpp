#include "PlushUtilException.hpp"
#include <iostream>

void PlushUtil::describeException(PlushUtilException e) {
    switch (e) {
        case PlushUtilException::CANNOT_CREATE_NULL_MANAGED_OBJECT:{
            std::cout << "Cannot create a ManagedObject with no stored object." << std::endl;
            return;
        }
        case PlushUtilException::CANNOT_MOVE_ASSIGN_ORIGINAL_INTO_CLONE:{
            std::cout << "Cannot use move assign from an original ManagedObject into a cloned ManagedObject." << std::endl;
            return;
        }
        case PlushUtilException::CANNOT_MOVE_ASSIGN_CLONE_INTO_ORIGINAL:{
            std::cout << "Cannot use move assign from a cloned ManagedObject into an original ManagedObject." << std::endl;
            return;
        }
        case PlushUtilException::CANNOT_COPY_ORIGINAL_MANAGED_OBJECT:{
            std::cout << "Cannot copy directly from an original ManagedObject." << std::endl;
            return;
        }
        case PlushUtilException::CANNOT_COPY_ASSIGN_INTO_ORIGINAL_MANAGED_OBJECT:{
            std::cout << "Cannot copy assign into an original ManagedObject." << std::endl;
            return;
        }
        case PlushUtilException::MANAGED_OBJECT_EXPIRED:{
            std::cout << "Attempted to access an expired ManagedObject." << std::endl;
            return;
        }
        case PlushUtilException::FILE_READ_ERROR:{
            std::cout << "Error reading file." << std::endl;
            return;
        }
        case PlushUtilException::ITEM_NOT_LOADED_IN_REGISTRY:{
            std::cout << "Requested item is not loaded in registry." << std::endl;
            return;
        }
        default:{
            std::cout << "This PlushUtil exception is not documented, requires update to describeException(PlushUtilException e)." << std::endl;
            return;
        }
    }
}

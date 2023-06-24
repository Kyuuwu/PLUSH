#include "RotationHandler.h"
#include <glm/gtx/transform.hpp>

#include <iostream>

namespace PLUSH {
    glm::mat4 RotationHandler::getRotationMatrix(){
        return rotationMatrix;
    }

    void RotationHandler::resetUpdateCheck(bool value){
        rotationUpdated = value;
    }

    bool RotationHandler::wasUpdated(){
        return rotationUpdated;
    }

    void RotationHandler::resetRotation(){
        rotationMatrix = glm::mat4(1.0f);
        rotationUpdated = true;
    }

    void RotationHandler::rotate(float radians, glm::vec3 direction){
        rotationMatrix = glm::rotate(rotationMatrix, radians, direction);
        rotationUpdated = true;
    }

    void RotationHandler::setToRotation(float radians, glm::vec3 direction){
        resetRotation();
        rotate(radians, direction);
    }

    std::shared_ptr<RotationHandler> RotationHandler::copy(){
        std::shared_ptr<RotationHandler> copied(new RotationHandler);

        copied->setRotationMatrix(rotationMatrix);

        return copied;
    }

    void RotationHandler::setRotationMatrix(glm::mat4 rotMat){
        rotationMatrix = rotMat;

        rotationUpdated = true;
    }
}
#include <glm/glm.hpp>
#include <memory>

namespace PLUSH {
    class RotationHandler{
        public:
            glm::mat4 getRotationMatrix();
            void setRotationMatrix(glm::mat4 rotMat);

            void resetUpdateCheck(bool value = false);

            bool wasUpdated();

            void resetRotation();
            void rotate(float radians, glm::vec3 direction);
            void setToRotation(float radians, glm::vec3 direction);

            std::shared_ptr<RotationHandler> copy();

        private:
            glm::mat4 rotationMatrix = glm::mat4(1.0f);

            bool rotationUpdated = true;
    };
}
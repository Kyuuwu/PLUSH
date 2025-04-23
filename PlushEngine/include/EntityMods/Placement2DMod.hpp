#include "EngineInterfaces/BaseEntityMod.hpp"
#include "EngineInterfaces/ControlsCoordinateState2D.hpp"
#include "OpenGL_Type.hpp"
#include "OpenGL_Value.hpp"
#include "PlushEngine.hpp"
#include "Shader/ManagedShader.hpp"
#include "Shader/ShaderUniformPayload.hpp"
#include "Shader/ShaderUniformSlotIdentifier.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

namespace PlushEngine {
    namespace EntityMods{
        class Placement2DMod : public EngineInterfaces::BaseEntityMod, public EngineInterfaces::ControlsCoordinateState2D{
            public:
                virtual void setPosition2D(double x, double y) override{
                    if(!owningEntity.has_value()){  // if no entity assigned yet, queue up update
                        setPosToFirstEntity = true;
                        _x = x;
                        _y = y;
                        return;
                    }

                    DataStructures::CoordinateState2D& coords = owningEntity->status().Coords2D();
                    coords.position.x = x;
                    coords.position.y = y;
                }

                virtual void setRotation2D(double angle) override{
                    if(!owningEntity.has_value()){ // if no entity assigned yet, queue up update
                        setRotToFirstEntity = true;
                        _angle = angle;
                        return;
                    }

                    DataStructures::CoordinateState2D& coords = owningEntity->status().Coords2D();
                    coords.rotation.angle = angle;
                }

                virtual void processNewOwningEntity() override{
                    // if a position or rotation update is queued inside the mod for the first Entity it is assigned to,
                    // perform those updates.

                    if(setPosToFirstEntity){
                        setPosition2D(_x, _y);
                        setPosToFirstEntity = false;
                    }

                    if(setRotToFirstEntity){
                        setRotation2D(_angle);
                        setRotToFirstEntity = false;
                    }
                }

                virtual void resolveUniformRequirements(PlushGraphics::ManagedShader shader) override{
                    DataStructures::CoordinateState2D& coords = owningEntity->status().Coords2D();

                    glm::mat4 modelMatrix = glm::mat4(1.0f);
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(coords.position.x, coords.position.y, 0.0f));

                    modelMatrix = glm::rotate(modelMatrix, (float)coords.rotation.angle,  glm::vec3(0.0f, 0.0f, 1.0f));

                    PlushGraphics::ShaderMetadata::ShaderUniformPayload modelMatrixPayload(
                        PlushGraphics::ShaderMetadata::ShaderUniformSlotIdentifier("modelMatrix", PlushGraphics::OpenGL_Type::FLOAT_MAT_4),
                        PlushGraphics::OpenGL_Value::create_mat4(modelMatrix)
                    );

                    shader.setUniformNew(modelMatrixPayload);
                }

            private:

                bool setPosToFirstEntity = false;
                double _x, _y;

                bool setRotToFirstEntity = false;
                double _angle;
        };
    }
}
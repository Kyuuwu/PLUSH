#ifndef WINDOWUNIFORMRESOLVER_HPP
#define WINDOWUNIFORMRESOLVER_HPP

#include "OpenGL_Type.hpp"
#include "OpenGL_Value.hpp"
#include "PlushGraphics.hpp"
#include "UniformResolver.hpp"
#include "Window/ManagedWindow.hpp"
#include <optional>

namespace PlushGraphics {
    namespace UniformResolvers {
        class WindowUniformResolver : public UniformResolver{
            public:
                WindowUniformResolver(ManagedWindow _window):
                window(_window)
                {}

                WindowUniformResolver(){}

                void resolveUniformRequirements(ManagedShader shader)override {
                    if(!window.has_value()){
                        return;
                    }

                    ShaderMetadata::ShaderUniformPayload aspectRatioPayload(
                        ShaderMetadata::ShaderUniformSlotIdentifier(
                            "aspectRatio",
                            OpenGL_Type::FLOAT
                        ),
                        OpenGL_Value::create_float(window->getAspectRatio())
                    );

                    shader.setUniformNew(aspectRatioPayload);
                }

                UniquePtrUniformResolver duplicateSelf() const override{
                    return UniquePtrUniformResolver(new WindowUniformResolver(*this)); // copy construct new copy
                }

                void setWindow(ManagedWindow _window){
                    window = _window;
                }

            private:
                std::optional<ManagedWindow> window;
        };
    }
}

#endif // WINDOWUNIFORMRESOLVER_HPP

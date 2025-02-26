#ifndef MANAGEDSHADER_HPP
#define MANAGEDSHADER_HPP

#include "PlushGraphics.hpp"
#include "ManagedObject.hpp"
#include "Shader.hpp"

namespace PlushGraphics {
    class ManagedShader : public PlushUtil::ManagedObject<Shader>{
        public:
            template <typename T>
            ManagedShader(T&& arg):
                PlushUtil::ManagedObject<Shader>(std::forward<T>(arg)){}

            template <typename T>
            ManagedShader& operator=(T&& arg){
                return PlushUtil::ManagedObject<Shader>::operator=(std::forward<T>(arg));
            }

            using Object = Shader;
        
        private:
    };
}

#endif // MANAGEDSHADER_HPP

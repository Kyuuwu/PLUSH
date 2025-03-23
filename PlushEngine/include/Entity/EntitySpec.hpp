#ifndef ENTITYSPEC_HPP
#define ENTITYSPEC_HPP

#include "PlushEngine.hpp"

namespace PlushEngine {
    class EntitySpec{
        public:
            void fuckOff(){
                i++;
            }

        private:
            unsigned int i = 0;
    };
}

#endif // ENTITYSPEC_HPP

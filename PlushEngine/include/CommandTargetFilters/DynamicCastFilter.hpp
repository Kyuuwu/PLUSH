#ifndef DYNAMICCASTFILTER_HPP
#define DYNAMICCASTFILTER_HPP

#include "PlushEngine.hpp"
#include "EngineInterfaces/CommandTargetFilter.hpp"
#include <iostream>
#include "EngineInterfaces/BaseEntityMod.hpp"

namespace PlushEngine {
    namespace CommandTargetFilters {
        template<typename TargetClass>
        class DynamicCastFilter : public CommandTargetFilter{
            public:
                DynamicCastFilter(){}

                virtual bool testMod(SharedPtrEntityMod _mod) override{
                    // std::cout << "hi" << std::endl;
                    // std::cout << "type wanted: " << typeid(TargetClass).name() << std::endl;
                    // std::cout << "type had: " << typeid(*_mod.get()).name() << std::endl;
                    // std::cout << "mod: " << _mod.get() << std::endl;

                    if(dynamic_cast<TargetClass*>(_mod.get()) != nullptr){ // if cross-cast is valid
                        return true;
                    }
                    return false;
                }

        };
    }
}

#endif // DYNAMICCASTFILTER_HPP

#include "PlushEngine.hpp"
#include "EngineInterfaces/CommandTargetFilter.hpp"
#include "EngineInterfaces/BaseEntityMod.hpp"
#include <typeinfo>

namespace PlushEngine {
    namespace CommandTargetFilters {
        class TypeFilter : public CommandTargetFilter{
            public:
                TypeFilter(const std::type_info& _type):
                targetType(_type) {}

                // UniquePtrFilter copy() override{
                //     return UniquePtrFilter(new TypeFilter(targetType));
                // }

                bool testMod(SharedPtrEntityMod _mod) override{
                    EngineInterfaces::BaseEntityMod& temp = *_mod;

                    if(typeid(temp) == targetType){
                        return true;
                    }
                    return false;
                }

            private:
                const std::type_info& targetType;
        };
    }
}
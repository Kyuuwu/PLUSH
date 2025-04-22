#include "PlushEngine.hpp"
#include "EngineInterfaces/CommandTargetFilter.hpp"

namespace PlushEngine {
    namespace CommandTargetFilters {
        template<typename TargetClass>
        class DynamicCastFilter : public CommandTargetFilter{
            public:
                DynamicCastFilter(){}

                virtual bool testMod(SharedPtrEntityMod _mod) override{
                    if(dynamic_cast<TargetClass*>(_mod.get()) != nullptr){ // if cross-cast is valid
                        return true;
                    }
                    return false;
                }

        };
    }
}
#include "PlushEngine.hpp"
#include "EngineInterfaces/Command.hpp"

namespace PlushEngine {
    namespace Commands {
        class NoOpCommand : public EngineInterfaces::Command{
            protected:
                virtual void executeCommand(SharedPtrEntityMod mod) override{
                    #pragma unused(mod)
                }
        };
    }
}
#ifndef NOOPCOMMAND_HPP
#define NOOPCOMMAND_HPP

#include "PlushEngine.hpp"
#include "EngineInterfaces/Command.hpp"

namespace PlushEngine {
    namespace Commands {
        class NoOpCommand : public EngineInterfaces::Command{
            protected:
                virtual void executeCommandOnMod(SharedPtrEntityMod mod) override{
                    #pragma unused(mod)
                }
        };
    }
}

#endif // NOOPCOMMAND_HPP

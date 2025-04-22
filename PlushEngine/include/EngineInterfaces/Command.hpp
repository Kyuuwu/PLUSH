#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Entity/ManagedEntity.hpp"
#include "PlushEngine.hpp"
#include "CommandTargetFilter.hpp"
#include <cstddef>
#include <vector>

namespace PlushEngine {
    namespace EngineInterfaces {
        class Command{
            public:
                virtual ~Command(){}

                virtual Command& expectsNumRecipients(size_t _numRecipients){
                    expectedNumRecipients = _numRecipients;
                    return *this;
                }

                template<typename Self, typename Filter>
                Self&& filterBy(this Self&& self, Filter&& _filter){
                    self.filters.push_back(_filter.copy());
                    return self;
                }
    
                virtual void executeCommand(ManagedEntity targetEntity){
                    std::vector<SharedPtrEntityMod> mods = targetEntity.getEntityMods();

                    mods = filterMods(mods);

                    if(isRecipientsListValid(mods)){
                        for(SharedPtrEntityMod _mod : mods){
                            executeCommand(_mod);
                        }
                    }
                }
    
            protected:
                virtual std::vector<SharedPtrEntityMod> filterMods(std::vector<SharedPtrEntityMod> mods){ // currently by copy, could easily be by ref eventually
                    for(SharedPtrFilter _filter : filters){
                        mods = _filter->filterMods(mods); // apply each filter, then return the result
                    }

                    return mods;
                }

                virtual bool isRecipientsListValid(const std::vector<SharedPtrEntityMod>& recipientMods){
                    if(expectedNumRecipients == 0){ // 0 allows any number of recipients
                        return true;
                    }

                    if(recipientMods.size() == expectedNumRecipients){
                        return true;
                    }

                    return false;
                }

                // virtual bool isRecipientValid(SharedPtrEntityMod mod){
                //     // if(dynamic_cast<TargetInterface*>(mod.get()) != nullptr){ // if cross-cast is valid
                //     //     return true;
                //     // }
                //     #pragma unused(mod)
                //     return false;
                // }

                virtual void executeCommand(SharedPtrEntityMod mod) = 0;

                size_t expectedNumRecipients = 0; // 0 ie any number of recipients
                std::vector<SharedPtrFilter> filters;
        };
    }
}

#endif // COMMAND_HPP

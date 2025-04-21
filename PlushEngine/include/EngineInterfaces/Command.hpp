#include "Entity/ManagedEntity.hpp"
#include "PlushEngine.hpp"
#include "CommandTargetFilter.hpp"
#include <cstddef>
#include <vector>

namespace PlushEngine {
    namespace EngineInterfaces {
        class Command{
            public:
                virtual Command& expectsNumRecipients(size_t _numRecipients){
                    expectedNumRecipients = _numRecipients;
                    return *this;
                }
                virtual Command& filterBy(CommandTargetFilter&& _filter){
                    filters.push_back(_filter.copy());
                    return *this;
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
                    std::vector<SharedPtrEntityMod> validMods;

                    for(SharedPtrEntityMod _mod : mods){ // filter by interface filter before or after? idk uwu
                        if(isRecipientValid(_mod)){
                            validMods.push_back(_mod);
                        }
                    }

                    return validMods;
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

                virtual bool isRecipientValid(SharedPtrEntityMod mod) = 0;
                virtual void executeCommand(SharedPtrEntityMod mod) = 0;

                size_t expectedNumRecipients = 0; // 0 ie any number of recipients
                std::vector<SharedPtrFilter> filters;
        };
    }
}
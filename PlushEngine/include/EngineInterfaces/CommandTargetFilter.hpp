#ifndef COMMANDTARGETFILTER_HPP
#define COMMANDTARGETFILTER_HPP

#include "PlushEngine.hpp"
#include <vector>

namespace PlushEngine {
    class CommandTargetFilter{
        public:
            template<typename Self>
            UniquePtrFilter copy(this const Self& self){
                return UniquePtrFilter(new Self(self));
            }

            virtual ~CommandTargetFilter(){}

            virtual bool testMod(SharedPtrEntityMod _mod) = 0;
            virtual std::vector<SharedPtrEntityMod> filterMods(std::vector<SharedPtrEntityMod> mods){
                std::vector<SharedPtrEntityMod> filteredMods;

                for(SharedPtrEntityMod _mod : mods){
                    if(testMod(_mod)){
                        filteredMods.push_back(_mod);
                    }
                }

                return filteredMods;
            }
    };
}

#endif // COMMANDTARGETFILTER_HPP

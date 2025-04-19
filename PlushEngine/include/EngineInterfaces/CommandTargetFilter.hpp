#include "PlushEngine.hpp"
#include <vector>

namespace PlushEngine {
    class CommandTargetFilter{
        public:
            virtual UniquePtrFilter copy() = 0;
            virtual bool testMod(SharedPtrEntityMod _mod) = 0;
            virtual std::vector<SharedPtrEntityMod> filterMods(std::vector<SharedPtrEntityMod> mods){
                std::vector<SharedPtrEntityMod> filteredMods;

                for(SharedPtrEntityMod _mod : mods){
                    if(testMod(_mod)){
                        filteredMods.push_back(_mod);
                    }
                }

                return mods;
            }
    };
}
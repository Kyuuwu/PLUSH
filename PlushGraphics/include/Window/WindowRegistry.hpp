#ifndef WINDOWREGISTRY_HPP
#define WINDOWREGISTRY_HPP

#include "Registry.hpp"
#include "ManagedWindow.hpp"
#include "Window/WindowIdentifier.hpp"
#include "Window/WindowSpec.hpp"

namespace PlushGraphics {
    class WindowRegistry : public PlushUtil::Registry<ManagedWindow>{
        public:
            WindowIdentifier loadItem(WindowSpec spec) override{
                WindowIdentifier id = PlushUtil::Registry<ManagedWindow>::loadItem(spec);
                ManagedWindow managed = getItem(id);


                pointer_to_indexMap[managed->windowPointer] = indexMap.at(id);

                return id;
            }

            ManagedWindow getManagedWindowFromWindowPtr(GLFWwindow* windowptr){
                if (!(pointer_to_indexMap.count(windowptr) > 0)){
                    throw(PlushUtil::PlushUtilException::ITEM_NOT_LOADED_IN_REGISTRY);
                }
        
                return items.at(pointer_to_indexMap.at(windowptr)).clone(); // use map to get index and retrieve item
            }
        
            private:
                std::map<GLFWwindow*, size_t> pointer_to_indexMap;
    };
}

#endif // WINDOWREGISTRY_HPP

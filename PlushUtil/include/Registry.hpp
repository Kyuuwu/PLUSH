#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <type_traits>
#include <vector>
#include <map>

#include "PlushUtil.hpp"

namespace PlushUtil {
    template<HasIDAndSpec ManagedX> class Registry{
        public:
            ManagedX getItem(typename ManagedX::Identifier identifier);
            bool isItemLoaded(typename ManagedX::Identifier identifier);
            void loadItem(typename ManagedX::Spec spec);

        private:
            std::vector<ManagedX> shaders;
            std::map<typename ManagedX::Identifier, size_t> indexMap;
    };

    template<HasIDAndSpec ManagedX>
    ManagedX Registry<ManagedX>::getItem(typename ManagedX::Identifier identifier){
        return shaders.at(indexMap.at(identifier));
    }
}

#endif // REGISTRY_HPP

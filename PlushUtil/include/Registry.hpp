#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <type_traits>
#include <vector>
#include <map>

#include "PlushUtil.hpp"

namespace PlushUtil {
    template<ImplementsManagedObject ManagedX> class Registry{
        public:
            ManagedX getItem(typename ManagedX::Object::Identifier identifier);
            bool isItemLoaded(typename ManagedX::Object::Identifier identifier);
            void loadItem(typename ManagedX::Object::Spec spec);

        private:
            std::vector<ManagedX> items;
            std::map<typename ManagedX::Object::Identifier, size_t> indexMap;
    };

    template<ImplementsManagedObject ManagedX>
    ManagedX Registry<ManagedX>::getItem(typename ManagedX::Object::Identifier identifier){
        return items.at(indexMap.at(identifier)).clone(); // use map to get index and retrieve item
    }

    template<ImplementsManagedObject ManagedX>
    bool Registry<ManagedX>::isItemLoaded(typename ManagedX::Object::Identifier identifier){
        return (indexMap.count(identifier) > 0); // check if key exists in map
    }

    template<ImplementsManagedObject ManagedX>
    void Registry<ManagedX>::loadItem(typename ManagedX::Object::Spec spec){
        ManagedX newItem(spec); // create new item from spec
        indexMap[newItem.getIdentifier()] = items.size(); // add end index to map with identifier
        items.push_back(std::move(newItem)); // add new item to vector
    }
}

#endif // REGISTRY_HPP

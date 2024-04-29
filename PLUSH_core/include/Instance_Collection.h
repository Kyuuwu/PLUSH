#ifndef __INSTANCECOLLECTION_H__
#define __INSTANCECOLLECTION_H__

#include <vector>
#include <memory>

namespace PLUSH {
    class Instance;

    class InstanceCollection{
        public:
            void addInstance(std::weak_ptr<Instance> newInstance, int group = -1);

        private:
            std::vector<std::weak_ptr<Instance>> defaultGroup;
            std::vector<std::vector<std::weak_ptr<Instance>>> extraGroups;


    };
}

#endif // __INSTANCECOLLECTION_H__
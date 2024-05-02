#ifndef __INSTANCECOLLECTION_H__
#define __INSTANCECOLLECTION_H__

#include <vector>
#include <memory>

namespace PLUSH {

    class Instance;
    
    struct Instance_Group_Pair{
        std::shared_ptr<Instance> instance;
        size_t group = 0; 
        int32_t layerorder = 0;
    };

    bool comparePairLayerOrder(const Instance_Group_Pair& a, const Instance_Group_Pair& b);

    class InstanceCollection{
        public:
            void addInstance(std::weak_ptr<Instance> newInstance, size_t groupnum);

            std::vector<Instance_Group_Pair> getSortedInstanceGroupPairs();

        private:
            std::vector<Instance_Group_Pair> convertInstanceListToGroupPairList(size_t groupnum);

            void sortAllGroups();
            void sortGroup(size_t groupnum);

            std::vector<std::vector<std::weak_ptr<Instance>>> groups;
    };
}

#endif // __INSTANCECOLLECTION_H__
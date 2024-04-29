#include "Instance_Collection.h"

namespace PLUSH
{
    void InstanceCollection::addInstance(std::weak_ptr<Instance> newInstance, size_t group)
    {
        
        if (groups.size() < group + 1){
            for (size_t i = groups.size(); i < group + 1; i++){
                groups.push_back(std::vector<std::weak_ptr<Instance>>());
            }
        }

        groups[group].push_back(newInstance);
        
    }
    
    std::vector<Instance_Group_Pair> InstanceCollection::getSortedInstanceGroupPairs()
    {
        std::vector<Instance_Group_Pair> sortedInstances;

        for(size_t groupnum = 0; groupnum < groups.size(); groupnum++){
            for (size_t i = 0; i < groups.size();){
                std::shared_ptr<Instance> locked_instance = groups[groupnum][i].lock();
                if(locked_instance == nullptr){
                    groups[groupnum].erase(groups[groupnum].begin() + i);
                }else{
                    Instance_Group_Pair pair;
                    pair.group = groupnum;
                    pair.instance = locked_instance;

                    sortedInstances.push_back(pair);

                    i++;
                }
            }
        }

        // TODO: sort them!!

        return sortedInstances;
    }
}
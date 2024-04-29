#include "Instance_Collection.h"

namespace PLUSH
{
    void InstanceCollection::addInstance(std::weak_ptr<Instance> newInstance, int group)
    {
        if (group < 0){
            defaultGroup.push_back(newInstance);
        }else{
            if (extraGroups.size() < group + 1){
                for (int i = extraGroups.size(); i < group + 1; i++){
                    extraGroups.push_back(std::vector<std::weak_ptr<Instance>>());
                }
            }

            extraGroups[group].push_back(newInstance);
        }
    }
}
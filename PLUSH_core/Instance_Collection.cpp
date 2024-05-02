#include "Instance_Collection.h"
#include "Instance.h"
#include <iostream>
#include <algorithm>

namespace PLUSH
{
    bool comparePairLayerOrder(const Instance_Group_Pair& a, const Instance_Group_Pair& b)
    {
        return a.layerorder < b.layerorder;
    }

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
        sortAllGroups(); //For now, sorts every time

        if(groups.size() == 0){
            return std::vector<Instance_Group_Pair>();
        }
        else if(groups.size() == 1){
            return convertInstanceListToGroupPairList(0);
        }
        else {
            std::vector<Instance_Group_Pair> outputlist = convertInstanceListToGroupPairList(0);
            
            for(size_t i = 1; i < groups.size(); i++){
                std::vector<Instance_Group_Pair> inputlist1 = outputlist;
                std::vector<Instance_Group_Pair> inputlist2 = convertInstanceListToGroupPairList(i);

                outputlist.clear();

                std::merge(
                    inputlist1.begin(), inputlist1.end(), 
                    inputlist2.begin(), inputlist2.end(), 
                    std::back_inserter(outputlist), 
                    comparePairLayerOrder);
            }

            return outputlist;
        }
    }
    
    std::vector<Instance_Group_Pair> InstanceCollection::convertInstanceListToGroupPairList(size_t groupnum)
    {
        std::vector<Instance_Group_Pair> grouppairlist;

        for(std::weak_ptr<Instance> inst: groups.at(groupnum)){
            std::shared_ptr<Instance> instance = inst.lock();
            Instance_Group_Pair pair;
            pair.instance = instance;
            pair.group = groupnum;
            pair.layerorder = instance->getLayerOrder();
            grouppairlist.push_back(pair);
        }

        return grouppairlist;
    }
    
    void InstanceCollection::sortAllGroups()
    {
        for (size_t i = 0; i < groups.size(); i++){
            sortGroup(i);
        }
    }
    
    void InstanceCollection::sortGroup(size_t groupnum)
    {
        //CHECK NO DEAD PTRS

        std::sort(groups.at(groupnum).begin(),groups.at(groupnum).end(), Instance::compareLayerOrderWeak);
    }
}
//
// Created by Joshua McDonagh on 09/05/2024.
//

#ifndef MODEL_RESULTS_H
#define MODEL_RESULTS_H


#include <functional>
#include <vector>
#include <variant>
#include <string>
#include "MemoryMappedTable.h"

using StoredType = std::variant<int, double, std::string, bool>;
using MergeFunc = std::function<std::vector<StoredType>(std::string, std::vector<StoredType>, std::vector<StoredType>)>;

class ModelResults {
public:
    ModelResults(int coreNumber,
                 MergeFunc mergeAgentPhysiologyPropertyResultsWithModelResultsFunc,
                 MergeFunc mergeAgentBehaviourPropertyResultsWithModelResultsFunc,
                 MergeFunc mergeAgentPhysiologyEventResultsWithModelResultsFunc,
                 MergeFunc mergeAgentBehaviourEventResultsWithModelResultsFunc,
                 MergeFunc mergePhysiologyPropertyResultsFunc,
                 MergeFunc mergeBehaviourPropertyResultsFunc,
                 MergeFunc mergePhysiologyEventResultsFunc,
                 MergeFunc mergeBehaviourEventResultsFunc);

private:
    std::string physiologyPropertyResultsFilename_Suffix_m = "model_physiology_property_results.dat";
    std::string behaviourPropertyResultsFilename_Suffix_m = "model_behaviour_property_results.dat";
    std::string physiologyEventResultsFilename_Suffix_m = "model_physiology_event_results.dat";
    std::string behaviourEventResultsFilename_Suffix_m = "model_behaviour_event_results.dat";
    std::string physiologyPropertyResultsFilename_m;
    std::string behaviourPropertyResultsFilename_m;
    std::string physiologyEventResultsFilename_m;
    std::string behaviourEventResultsFilename_m;
    MergeFunc mergeAgentPhysiologyPropertyResultsWithModelResultsFunc_m;
    MergeFunc mergeAgentBehaviourPropertyResultsWithModelResultsFunc_m;
    MergeFunc mergeAgentPhysiologyEventResultsWithModelResultsFunc_m;
    MergeFunc mergeAgentBehaviourEventResultsWithModelResultsFunc_m;
    MergeFunc mergePhysiologyPropertyResultsFunc_m;
    MergeFunc mergeBehaviourPropertyResultsFunc_m;
    MergeFunc mergePhysiologyEventResultsFunc_m;
    MergeFunc mergeBehaviourEventResultsFunc_m;
};



#endif //MODEL_RESULTS_H

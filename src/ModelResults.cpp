//
// Created by Joshua McDonagh on 09/05/2024.
//

#include <utility>

#include "../include/ModelResults.h"

ModelResults::ModelResults(int coreNumber, int numOfPhysiologyProperties, int numOfBehaviourProperties,
                           int numOfPhysiologyEvents, int numOfBehaviourEvents,
                           MergeFunc mergeAgentPhysiologyPropertyResultsWithModelResultsFunc,
                           MergeFunc mergeAgentBehaviourPropertyResultsWithModelResultsFunc,
                           MergeFunc mergeAgentPhysiologyEventResultsWithModelResultsFunc,
                           MergeFunc mergeAgentBehaviourEventResultsWithModelResultsFunc,
                           MergeFunc mergePhysiologyPropertyResultsFunc, MergeFunc mergeBehaviourPropertyResultsFunc,
                           MergeFunc mergePhysiologyEventResultsFunc, MergeFunc mergeBehaviourEventResultsFunc) {
    physiologyPropertyResultsFilename_m = std::to_string(coreNumber) + "_" + physiologyPropertyResultsFilename_Suffix_m;
    behaviourPropertyResultsFilename_m = std::to_string(coreNumber) + "_" + behaviourPropertyResultsFilename_Suffix_m;
    physiologyEventResultsFilename_m = std::to_string(coreNumber) + "_" + physiologyEventResultsFilename_Suffix_m;
    behaviourEventResultsFilename_m = std::to_string(coreNumber) + "_" + behaviourEventResultsFilename_Suffix_m;

    mergeAgentPhysiologyPropertyResultsWithModelResultsFunc_m = std::move(mergeAgentPhysiologyPropertyResultsWithModelResultsFunc);
    mergeAgentBehaviourPropertyResultsWithModelResultsFunc_m = std::move(mergeAgentBehaviourPropertyResultsWithModelResultsFunc);
    mergeAgentPhysiologyEventResultsWithModelResultsFunc_m = std::move(mergeAgentPhysiologyEventResultsWithModelResultsFunc);
    mergeAgentBehaviourEventResultsWithModelResultsFunc_m = std::move(mergeAgentBehaviourEventResultsWithModelResultsFunc);

    mergePhysiologyPropertyResultsFunc_m = std::move(mergePhysiologyPropertyResultsFunc);
    mergeBehaviourPropertyResultsFunc_m = std::move(mergeBehaviourPropertyResultsFunc);
    mergePhysiologyEventResultsFunc_m = std::move(mergePhysiologyEventResultsFunc);
    mergeBehaviourEventResultsFunc_m = std::move(mergeBehaviourEventResultsFunc);

    physiologyPropertyData_m = new MemoryMappedTable(physiologyPropertyResultsFilename_m, 0, numOfPhysiologyProperties);
    behaviourPropertyData_m = new MemoryMappedTable(behaviourPropertyResultsFilename_m, 0, numOfBehaviourProperties);
    physiologyEventData_m = new MemoryMappedTable(physiologyEventResultsFilename_m, 0, numOfPhysiologyEvents);
    behaviourEventData_m = new MemoryMappedTable(behaviourEventResultsFilename_m, 0, numOfBehaviourEvents);

}

ModelResults::~ModelResults() {
    free(physiologyPropertyData_m);
    free(behaviourPropertyData_m);
    free(physiologyEventData_m);
    free(behaviourEventData_m);
}

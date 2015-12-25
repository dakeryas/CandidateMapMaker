#include "MapGrabber.hpp"

namespace CandidateMapMaker{

  MapGrabber::MapGrabber(const SelectionLabels& selectionLabels):selectionLabels(selectionLabels){
    
    auto dataBase = FileDB::GetME();
    dataBase->UseQCInfo(true);
    dataBase->UseTaggedTable(selectionLabels.runList);
    dataBase->GenQuery();
    runNumbers = dataBase->LoadRuns();
    

  }
  
  std::unordered_map<unsigned, std::vector<unsigned>> MapGrabber::getMap() const{
    
    std::unordered_map<unsigned, std::vector<unsigned>> candidatesMap;
    
    for(auto runNumber : runNumbers){
      
      CandidateIdentifiersGrabber candidateIdentifiersGrabber(runNumber, selectionLabels.production, selectionLabels.dataType);
      auto candidateIdentifiers = candidateIdentifiersGrabber.getCandidateIdentifiers();
      if(!candidateIdentifiers.empty()) candidatesMap[runNumber] = candidateIdentifiers;
    
    }
    
    return candidatesMap;

  }
  
}

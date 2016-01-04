#include "MapMaker.hpp"

namespace CandidateMapMaker{

  MapMaker::MapMaker(RunFilter::SelectionLabels selectionLabels):selectionLabels(std::move(selectionLabels)),runNumbers(RunFilter::getRunNumbers(this->selectionLabels)){
    
  }
  
  std::unordered_map<unsigned, std::vector<unsigned>> MapMaker::getMap() const{
    
    std::unordered_map<unsigned, std::vector<unsigned>> candidatesMap;
    
    for(auto runNumber : runNumbers){
      
      CandidateIdentifiersGrabber candidateIdentifiersGrabber(runNumber, selectionLabels.production, selectionLabels.dataType);
      auto candidateIdentifiers = candidateIdentifiersGrabber.getCandidateIdentifiers();
      if(!candidateIdentifiers.empty()) candidatesMap[runNumber] = candidateIdentifiers;
    
    }
    
    return candidatesMap;

  }
  
}

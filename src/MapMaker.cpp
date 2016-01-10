#include "MapMaker.hpp"

namespace CandidateMapMaker{

  MapMaker::MapMaker(RunFilter::SelectionLabels selectionLabels, CosmogenicHunter::Bounds<double> candidateEnergyBounds)
  :selectionLabels(std::move(selectionLabels)),runNumbers(RunFilter::getRunNumbers(this->selectionLabels)),candidateIdentifiersGrabber(this->selectionLabels.production, this->selectionLabels.dataType, std::move(candidateEnergyBounds)){
    
  }
  
  std::unordered_map<unsigned, std::vector<unsigned>> MapMaker::getMap(){
    
    std::unordered_map<unsigned, std::vector<unsigned>> candidatesMap;
    
    for(auto runNumber : runNumbers){
      
      auto candidateIdentifiers = candidateIdentifiersGrabber.getCandidateIdentifiers(runNumber);
      if(!candidateIdentifiers.empty()) candidatesMap[runNumber] = candidateIdentifiers;
    
    }
    
    return candidatesMap;

  }
  
}

#ifndef CANDIDATE_MAP_MAKER_MAP_MAKER_H
#define CANDIDATE_MAP_MAKER_MAP_MAKER_H

#include <unordered_map>
#include "RunFilter.hpp"
#include "CandidateIdentifiersGrabber.hpp"

namespace CandidateMapMaker{

  class MapMaker{
    
    RunFilter::SelectionLabels selectionLabels;
    std::vector<unsigned> runNumbers;
    CandidateIdentifiersGrabber candidateIdentifiersGrabber;
    
  public:
    MapMaker(RunFilter::SelectionLabels selectionLabels, CosmogenicHunter::Bounds<double> candidateEnergyBounds);
    std::unordered_map<unsigned, std::vector<unsigned>> getMap();
    
  };
  
}

#endif
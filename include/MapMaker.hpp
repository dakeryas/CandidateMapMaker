#ifndef CANDIDATE_MAP_MAKER_MAP_MAKER_H
#define CANDIDATE_MAP_MAKER_MAP_MAKER_H

#include <unordered_map>
#include "RunFilter.hpp"
#include "IdentifiersGrabber.hpp"

namespace CandidateMapMaker{

  class MapMaker{
    
    RunFilter::SelectionLabels selectionLabels;
    std::vector<unsigned> runNumbers;
    
  public:
    MapMaker(RunFilter::SelectionLabels selectionLabels);
    std::unordered_map<unsigned, std::vector<unsigned>> getMap() const;
    
  };
  
}

#endif
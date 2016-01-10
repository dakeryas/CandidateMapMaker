#ifndef CANDIDATE_MAP_MAKER_CANDIDATE_IDENTIFIERS_GRABBER_H
#define CANDIDATE_MAP_MAKER_CANDIDATE_IDENTIFIERS_GRABBER_H

#include "DCCalib-TypeDef.hh"
#include "Cosmogenic/Event.hpp"
#include "Cosmogenic/Point.hpp"

namespace CandidateMapMaker{

  class CandidateIdentifiersGrabber {
    
    std::string production;
    std::string dataType;
    CosmogenicHunter::Bounds<double> candidateEnergyBounds;
    EnDep energyDeposit;
    void UpdateCandidateIdentifiers(std::vector<unsigned>& candidateIdentifiers);
    
  public:
    CandidateIdentifiersGrabber(std::string production, std::string dataType, CosmogenicHunter::Bounds<double> candidateEnergyBounds);
    std::vector<unsigned> getCandidateIdentifiers(unsigned runNumber);
    
  };
  
}

#endif
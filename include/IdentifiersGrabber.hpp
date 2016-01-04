#ifndef CANDIDATE_MAP_MAKER_IDENTIFIERS_GRABBER_H
#define CANDIDATE_MAP_MAKER_IDENTIFIERS_GRABBER_H

#include "DCCalib-TypeDef.hh"

namespace CandidateMapMaker{

  class CandidateIdentifiersGrabber {
    
    EnDep energyDeposit;
    
  public:
    CandidateIdentifiersGrabber(unsigned runNumber, const std::string& production, const std::string& dataType);
    std::vector<unsigned> getCandidateIdentifiers();
    
    
  };
  
}

#endif
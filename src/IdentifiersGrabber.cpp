#include "IdentifiersGrabber.hpp"

namespace CandidateMapMaker{

  CandidateIdentifiersGrabber::CandidateIdentifiersGrabber(unsigned runNumber, const std::string& production, const std::string& dataType){

    EnDep::AddFileDBINFO(production, std::to_string(runNumber),"");
    EnDep::SetLabelINPUT(dataType);
    energyDeposit.CancelAllInfoCapsule_Tree();
    energyDeposit.UncancelInfoCapsule_Tree(DC::kGlobalIT);
    energyDeposit.RetrieveME();
    
  }

  std::vector<unsigned> CandidateIdentifiersGrabber::getCandidateIdentifiers(){
    
    std::vector<unsigned> candidateIdentifiers;
    
    const GlobalInfo* globalInfo;
    
    while(energyDeposit.Next()){
	
      globalInfo = energyDeposit.GetGlobalInfo();
      unsigned identifier = globalInfo->GetTriggerID();
      candidateIdentifiers.emplace_back(identifier);
      
    }
    
    return candidateIdentifiers;

  }

  
}

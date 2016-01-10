#include "CandidateIdentifiersGrabber.hpp"

namespace CandidateMapMaker{

  CandidateIdentifiersGrabber::CandidateIdentifiersGrabber(std::string production, std::string dataType, CosmogenicHunter::Bounds<double> candidateEnergyBounds)
  :production(std::move(production)),dataType(std::move(dataType)),candidateEnergyBounds(std::move(candidateEnergyBounds)){
    
  }
  
  void CandidateIdentifiersGrabber::UpdateCandidateIdentifiers(std::vector<unsigned>& candidateIdentifiers){
    
    auto globalInfo = energyDeposit.GetGlobalInfo();
    auto recoBAMAInfo = energyDeposit.GetRecoBAMAInfo();
    
    CosmogenicHunter::Point<double> position(recoBAMAInfo->GetRecoX()[0], recoBAMAInfo->GetRecoX()[1], recoBAMAInfo->GetRecoX()[2]);
    auto numberOfPhotoElectrons = globalInfo->GetCaloPEID(DC::kCaloPEDefaultDC);
    auto energy = Calib::GetME(energyDeposit.GetVldContext())->EvisID(numberOfPhotoElectrons, globalInfo->GetNGoodChID(), position.getR(), position.getZ(), DCSimFlag::kDATA, DC::kESv10);
    
    CosmogenicHunter::Event<double> currentEvent{globalInfo->GetTrigTime(), energy, globalInfo->GetTriggerID()};
    
    if(currentEvent.hasVisibleEnergyWithin(candidateEnergyBounds)) candidateIdentifiers.emplace_back(currentEvent.getIdentifier());

  }

  std::vector<unsigned> CandidateIdentifiersGrabber::getCandidateIdentifiers(unsigned runNumber){
    
    EnDep::AddFileDBINFO(production, std::to_string(runNumber),"");
    EnDep::SetLabelINPUT(dataType);
    energyDeposit.CancelAllInfoCapsule_Tree();
    energyDeposit.UncancelInfoCapsule_Tree(DC::kGlobalIT);
    energyDeposit.UncancelInfoCapsule_Tree(DC::kRunIT);
    energyDeposit.UncancelInfoCapsule_Tree(DC::kRecoBAMAIT);
    energyDeposit.RetrieveME();
    
    std::vector<unsigned> candidateIdentifiers;
    while(energyDeposit.Next())
      if(energyDeposit.GetN() % 2) UpdateCandidateIdentifiers(candidateIdentifiers); //GetN() starts at 1 and we want prompts only so the rest of division by 2 should be 1 (hence 'true')
    return candidateIdentifiers;

  }
  
}

#include "CandidateIdentifiersGrabber.hpp"

namespace CandidateMapMaker{

  CandidateIdentifiersGrabber::CandidateIdentifiersGrabber(std::string production, std::string dataType, CosmogenicHunter::Bounds<double> candidateEnergyBounds)
  :production(std::move(production)),dataType(std::move(dataType)),candidateEnergyBounds(std::move(candidateEnergyBounds)){
    
  }
  
  void CandidateIdentifiersGrabber::UpdateCandidateIdentifiers(const EnDep& currentEnergyDeposit, std::vector<unsigned>& candidateIdentifiers){
    
    auto globalInfo = currentEnergyDeposit.GetGlobalInfo();
    auto recoBAMAInfo = currentEnergyDeposit.GetRecoBAMAInfo();
    
    CosmogenicHunter::Point<double> position(recoBAMAInfo->GetRecoX()[0], recoBAMAInfo->GetRecoX()[1], recoBAMAInfo->GetRecoX()[2]);
    auto numberOfPhotoElectrons = globalInfo->GetCaloPEID(DC::kCaloPEDefaultDC);
    auto energy = Calib::GetME(currentEnergyDeposit.GetVldContext())->EvisID(numberOfPhotoElectrons, globalInfo->GetNGoodChID(), position.getR(), position.getZ(), DCSimFlag::kDATA, DC::kESv10);
    
    if(candidateEnergyBounds.contains(energy)) candidateIdentifiers.emplace_back(globalInfo->GetTriggerID());

  }

  std::vector<unsigned> CandidateIdentifiersGrabber::getCandidateIdentifiers(unsigned runNumber){
    
    EnDep::AddFileDBINFO(production, std::to_string(runNumber),"");
    EnDep::SetLabelINPUT(dataType);
    
    EnDep currentEnergyDeposit;
    currentEnergyDeposit.CancelAllInfoCapsule_Tree();
    currentEnergyDeposit.UncancelInfoCapsule_Tree(DC::kGlobalIT);
    currentEnergyDeposit.UncancelInfoCapsule_Tree(DC::kRunIT);
    currentEnergyDeposit.UncancelInfoCapsule_Tree(DC::kRecoBAMAIT);
    currentEnergyDeposit.RetrieveME();
    
    std::vector<unsigned> candidateIdentifiers;
    while(currentEnergyDeposit.Next())
      if(currentEnergyDeposit.GetN() % 2) UpdateCandidateIdentifiers(currentEnergyDeposit, candidateIdentifiers); //GetN() starts at 1 and we want prompts only so the rest of division by 2 should be 1 (hence 'true')
    
    return candidateIdentifiers;

  }
  
}

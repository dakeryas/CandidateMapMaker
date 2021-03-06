#include "RunFilter.hpp"

namespace CandidateMapMaker{

  namespace RunFilter{
    
    std::string getDetector(const std::string& runListLabel){
      
      std::regex regex("_([N|F]D)_");
      std::smatch regexMatches;
      if(std::regex_search(runListLabel, regexMatches, regex)) return regexMatches.str(1);
      else return "FD";
      
    }
    
    unsigned getRunNumber(const std::string& runFilePath){
      
      unsigned runNumber{};
      std::regex regex("/?[\\D|0]*([1-9][0-9]{4,6})(?:\\D\\w+)?\\.root$");
      std::smatch regexMatches;
      if(std::regex_search(runFilePath, regexMatches, regex)) runNumber = std::stoul(regexMatches.str(1));
      
      return runNumber;
      
    }
    
    std::vector<unsigned> getRunNumbers(const SelectionLabels& selectionLabels){
      
      auto dataBase = FileDB::GetME();
      dataBase->SetDetector(getDetector(selectionLabels.runList));
      dataBase->UseQCInfo(true);
      dataBase->SetLABEL(selectionLabels.dataType);
      dataBase->UseTaggedTable(selectionLabels.runList);
      dataBase->Request(selectionLabels.production, "0-10000000", "");

      auto runFiles = dataBase->LoadFiles();

      std::vector<unsigned> runNumbers;
      runNumbers.reserve(runFiles.size());
      for(const auto& runFile : runFiles) runNumbers.emplace_back(getRunNumber(runFile.Data()));
      
      return runNumbers;
      
    }
    
  }

}

#ifndef CANDIDATE_MAP_MAKER_RUN_FILTER_H
#define CANDIDATE_MAP_MAKER_RUN_FILTER_H

#include <regex>
#include "DCEFileDB.hh"

namespace CandidateMapMaker{

  namespace RunFilter{
    
    struct SelectionLabels{
      
      std::string runList;
      std::string production;
      std::string dataType;
      
    };
    
    unsigned getRunNumber(const std::string& runFilePath);
    std::vector<unsigned> getRunNumbers(const SelectionLabels& selectionLabels);
    
  }

}


#endif
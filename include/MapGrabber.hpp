#include <unordered_map>
#include "IdentifiersGrabber.hpp"

namespace CandidateMapMaker{

  struct SelectionLabels{
    
    std::string runList;
    std::string production;
    std::string dataType;
    
  };
  
  class MapGrabber{
    
    SelectionLabels selectionLabels;
    std::vector<unsigned> runNumbers;
    
  public:
    MapGrabber(const SelectionLabels& selectionLabels);
    std::unordered_map<unsigned, std::vector<unsigned>> getMap() const;
    
  };
  
}

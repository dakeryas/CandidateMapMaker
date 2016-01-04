#include <iostream>
#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/vector.hpp"
#include "MapMaker.hpp"

namespace bpo = boost::program_options;

namespace CandidateMapMaker{
  
  void makeMap(const RunFilter::SelectionLabels& selectionLabels, const boost::filesystem::path& outputPath){

    Message::SetLevelMSG(DC::kMERROR);
    
    MapMaker mapMaker(selectionLabels);
    auto candidatesMap = mapMaker.getMap();
    
    std::ofstream outputStream(outputPath.string(), std::ios::binary);
    cereal::BinaryOutputArchive outputArchive(outputStream);
    outputArchive(candidatesMap);

  }
  
}

int main(int argc, char* argv[]){
 
  std::string runListLabel, productionLabel, dataSelectionLabel;
  boost::filesystem::path outputPath;
  
  bpo::options_description optionDescription("CandidateMapMaker usage");
  optionDescription.add_options()
  ("help,h", "Display this help message")
  ("run-list,r", bpo::value<std::string>(&runListLabel)->required(), "Label of the tagged run list")
  ("production,p", bpo::value<std::string>(&productionLabel)->required(), "Label of the production in the file database")
  ("data-selection,d", bpo::value<std::string>(&dataSelectionLabel)->required(), "Label of the data selection")
  ("output,o", bpo::value<boost::filesystem::path>(&outputPath)->required(), "Output file where to save the candidate trees");

  bpo::positional_options_description positionalOptions;//to use arguments without "--"
  positionalOptions.add("run-list-label", 1);
  
  bpo::variables_map arguments;
  try{
    
    bpo::store(bpo::command_line_parser(argc, argv).options(optionDescription).positional(positionalOptions).run(), arguments);
    
    if(arguments.count("help") || argc == 1){
      
      std::cout<<optionDescription<<std::endl;
      return 0;
      
    }
      
    bpo::notify(arguments);//the arguments are ready to be used
    
  }
  catch(bpo::error& e){
    
    std::cout<<e.what()<<std::endl;
    return 1;
    
  }

  CandidateMapMaker::makeMap(CandidateMapMaker::RunFilter::SelectionLabels{runListLabel, productionLabel, dataSelectionLabel}, outputPath);

  
}

#include "../include/parser.hpp"


Parser::Parser(){

}

Parser::MapString_t* Parser::parse_file(std::string filename){

    if(!filename.empty()){
        std::ifstream csvFile(filename);
        MapString_t* dataMap = new MapString_t();


        if(csvFile.is_open()){
            std::string line;
            std::string entryFName;
            while(std::getline(csvFile,line)){
                std::stringstream lineStream(line);
                std::string cell;

                //get the filename for the map
                std::getline(lineStream,entryFName,',');

                dataMap->insert(std::pair<std::string,std::vector<float>>(entryFName,std::vector<float>()));

                while(std::getline(lineStream,cell,',')){
                    dataMap->at(entryFName).push_back(std::stof(cell));
                }
            }

            csvFile.close();
            return NULL;
        }
        throw std::runtime_error("Couldn't open file\n");
        return NULL;
    }
    throw std::runtime_error("Filename Can't be empty\n");
    return NULL;

}

Parser::~Parser(){

}
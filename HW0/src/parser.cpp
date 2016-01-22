#include "../include/parser.hpp"


Parser::Parser(){

}

int Parser::parse_file(std::string filename, std::chrono::duration<double>* time_elapse){

    if(!filename.empty()){
        std::chrono::time_point<std::chrono::system_clock> start, end;

        std::ifstream csvFile(filename);


        if(csvFile.is_open()){
            std::string line;
            std::string entryFName;
            start = std::chrono::system_clock::now();
            while(std::getline(csvFile,line)){
                std::stringstream lineStream(line);
                std::string cell;

                //get the filename for the map
                std::getline(lineStream,entryFName,',');

                dataMap.insert(std::pair<std::string,std::vector<float>>(entryFName,std::vector<float>()));

                while(std::getline(lineStream,cell,',')){
                    dataMap.at(entryFName).push_back(std::stof(cell));
                }
            }

            end = std::chrono::system_clock::now();

            *time_elapse = end - start;

            csvFile.close();
            return 1;
        }
        std::cerr<<"Couldn't open file\n";
        return 0;
    }
    std::cerr<<"Filename Can't be empty\n";
    return 0;

}

Parser::~Parser(){

}
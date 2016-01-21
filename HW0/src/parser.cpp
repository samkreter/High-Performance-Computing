#include "../include/parser.hpp"


Parser::Parser(){

}

Parser::MapString_t* Parser::parse_file(std::string filename){

    if(!filename.empty()){
        std::ifstream csvFile(filename);


        if(csvFile.is_open()){
            std::cout<<"got it\n";
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
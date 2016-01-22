#ifndef PARSER_HPP__
#define PARSER_HPP__

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
// #include <exception>



class Parser
{

public:
    //don't have to write out the declaration everytime
    using MapString_t = std::map<std::string,std::vector<float>>;
    Parser();
    ~Parser();
    MapString_t* parse_file(std::string filename);

};

#endif
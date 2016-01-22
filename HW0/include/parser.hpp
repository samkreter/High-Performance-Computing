#ifndef PARSER_HPP__
#define PARSER_HPP__

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>
// #include <exception>



class Parser
{

public:
    //don't have to write out the declaration everytime
    using MapString_t = std::map<std::string,std::vector<float>>;
    Parser();
    ~Parser();
    int parse_file(std::string filename, std::chrono::duration<double>* time_elapse);
private:
    MapString_t dataMap;


};

#endif
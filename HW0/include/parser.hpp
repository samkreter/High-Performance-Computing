#ifndef PARSER_HPP__
#define PARSER_HPP__

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cfloat>
// #include <exception>



class Parser
{

public:
    //don't have to write out the declaration everytime
    using MapString_t = std::map<std::string,std::vector<float>>;
    Parser();
    ~Parser();
    int parse_file(std::string filename, std::chrono::duration<double>* time_elapse);
    size_t num_of_entries();
    size_t num_of_lines();
    int find_column_bounds_asGo();
    int output_vector_to_file(std::string filename, std::vector<float> vec, std::vector<float> vec2);
    int find_column_bounds_rowbyrow();
private:
    MapString_t dataMap;


};

#endif
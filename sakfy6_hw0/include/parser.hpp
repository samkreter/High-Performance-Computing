#ifndef PARSER_HPP__
#define PARSER_HPP__

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>
//used for floats max and mins
#include <cfloat>
// #include <exception>



class Parser{

public:
    //don't have to write out the declaration everytime
    using MapString_t = std::map<std::string,std::vector<float>>;

    /// parse the actual contents of the file
    /// \param filename: name of the file to read and parse
    /// \param time_elapse: chrono duration to hold how much time it took
    /// \return error code
    int parse_file(std::string filename, std::chrono::duration<double>* time_elapse);

    /// count the number of entires in the file (each cell)
    /// \return: size_t of the number of entires
    size_t num_of_entries();

    /// Counts number of lines that where parsed succesfully
    /// \return: return number of lines parsed
    size_t num_of_lines();

    /// outs the given vectors to a file in csv format
    /// \param filename: name of file to output to
    /// \param vec; first vector to output
    /// \param vec2: second vec to output
    /// \return error codes
    int output_vector_to_file(std::string filename, std::vector<float> vec, std::vector<float> vec2);

    /// find bouns of each column in the file
    /// \return: error codes
    int find_column_bounds_rowbyrow();
private:
    //store the map of the data
    MapString_t dataMap;


};

#endif
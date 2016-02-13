#ifndef VECTORMATCH_HPP__
#define VECTORMATCH_HPP__

#include <vector>
#include <iostream>
#include <cmath>
#include <map>

class VectorMatch{

    using MapString_t = std::map<std::string,std::vector<float>>;

public:
    VectorMatch(MapString_t* data):dataMap(data){};

    int computVectorMatch(std::string cmpFile, int k, int p);
private:
    MapString_t* dataMap;

    int findDist(std::vector<float> vec1, std::vector<float> vec2, float* dist);

};



#endif
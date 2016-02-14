#ifndef VECTORMATCH_HPP__
#define VECTORMATCH_HPP__

#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <iterator>
#include <algorithm>

//sys ipc stuff, you know the real stuff
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

class VectorMatch{

    using MapString_t = std::map<std::string,std::vector<float>>;

public:

    using shmKeyPair = struct{
        float dist;
        int lineNum;
    };


    VectorMatch(MapString_t* data):dataMap(data){};
    int computVectorMatch(std::string cmpFile, int k, int p);
private:
    MapString_t* dataMap;

    float findDist(std::vector<float>* vec1, std::vector<float>* vec2);

};



#endif
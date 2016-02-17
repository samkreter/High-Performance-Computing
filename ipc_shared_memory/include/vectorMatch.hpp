#ifndef VECTORMATCH_HPP__
#define VECTORMATCH_HPP__

#include <vector>
#include <iostream>
#include <memory>
#include <cmath>
#include <map>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cfloat>

//sys ipc stuff, you know the real stuff
#include <unistd.h>
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


    VectorMatch(std::shared_ptr<MapString_t> data):dataMap(data){};
    int computVectorMatch(std::string cmpFile, int k, int p,std::chrono::duration<double>* time_elapse);
private:
    std::shared_ptr<MapString_t> dataMap;

    float findDist(std::vector<float>* vec1, std::vector<float>* vec2);

};



#endif
#include "../include/vectorMatch.hpp"

int VectorMatch::findDist(std::vector<float> vec1, std::vector<float> vec2, float* dist){

    int vSize = vec1.size();
    float sum = 0;

    if(vSize == vec2.size()){
        for(int i = 0; i < vSize; i++){
            sum += std::abs(vec1.at(i) - vec2.at(i));
        }

        *dist = sum / (float) vSize;
        return 1;
    }
    std::cerr<<"Vectors are not the same size";
    return -1;
}


int VectorMatch::computVectorMatch(std::string cmpFile, int k, int p){

}

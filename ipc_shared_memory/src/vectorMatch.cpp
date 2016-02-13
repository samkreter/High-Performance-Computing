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

    //get all that shared mem stuff set up
    int shmId;          // ID of shared memory segment
    key_t shmKey = 123460;      // key to pass to shmget(), key_t is an IPC key type defined in sys/types
    //int shmFlag = IPC_CREAT | 0666; // Flag to create with rw permissions
    //_fileLine * shm;
    pid_t pid;
    unsigned long * sharedIndexPtr = NULL;


    int divNum = k / p;
    //this loops through and forks enough procs to process each file
    // 1 proc per file
    for(int i = 0; i < p; i++){
        pid = fork();

        if ( pid < 0 ){
            std::cerr << "Could not fork!!! ("<< pid <<")" << std::endl;
            return -1;
        }

        //this is the child taking over
        else if (pid == 0){

            std::cout<<i;

            exit(1);

        }
        //parent proc
        else{


        }

    }

    //wait for all the child procs to finish
    for(int i = 0; i < p; i++){
        //probably not enough checks for the procs waiting but
        // it works good for something like this
        wait(NULL);
    }

    return 1;

}

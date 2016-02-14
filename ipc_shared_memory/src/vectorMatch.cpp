#include "../include/vectorMatch.hpp"


float VectorMatch::findDist(std::vector<float>* vec1, std::vector<float>* vec2){

    int vSize = vec1->size();
    float sum = 0;

    if(vSize == vec2->size()){
        for(int i = 0; i < vSize; i++){
            sum += std::abs((vec1+i) - (vec2+i));
        }

        return sum / (float) vSize;
    }
    std::runtime_error("Vectors are not the same size");
    exit(-1);
}


bool shmKeyPairSort(const VectorMatch::shmKeyPair& pair1, const VectorMatch::shmKeyPair& pair2){
    return pair1.dist < pair2.dist;
}


int VectorMatch::computVectorMatch(std::string cmpFile, int k, int p){

    //get all that shared mem stuff set up
    int shmId;          // ID of shared memory segment
    key_t shmKey = 123460;      // key to pass to shmget(), key_t is an IPC key type defined in sys/types
    int shmFlag = IPC_CREAT | 0666; // Flag to create with rw permissions
    pid_t pid;
    unsigned long * sharedIndexPtr = NULL;

    std::vector<float>* cmpVec = &(dataMap->at(cmpFile));

    int divNum = dataMap->size() / p;

    if(k > divNum){
        std::cerr<<"K is bigger than the div number so offs in shared memeory\n";
        return -1;
    }

    //create the shared memeory
    if ((shmId = shmget(shmKey, (p * k * sizeof(shmKeyPair)) , shmFlag)) < 0){
        std::cerr << "Init: Failed to initialize shared memory (" << shmId << ")" << std::endl;
        return -1;
    }




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

            int procNum = i;
            //store the results of the vector
            std::map<float,int> results;
            //map iterator to make it seem like random access
            MapString_t::iterator it = dataMap->begin();

            //advance the iterator to the right line
            std::advance(it,(i*divNum));


            //get the distances and store them into a map that auto sorts by distance
            for(int j = procNum * divNum; j < (procNum + divNum); j++){

                //add the distance to the results map
                results.insert(std::pair<float,int>(findDist(cmpVec,&(it->second)),j));

                //advance the iterator to the next line
                std::advance(it,1);
            }


            shmKeyPair* shm;
            //get the shared memory in the right address space
            if ((shm = (shmKeyPair *)shmat(shmId, NULL, 0)) == (shmKeyPair *) -1){
                std::cerr << "Init: Failed to attach shared memory (" << shmId << ")" << std::endl;
                return -1;
            }

            //add the results to the proper segment of the shared memory
            int count = procNum * k;
            int kcount = 0;
            for(auto& pair : results){
                //i'll work on this latter, super bad
                if(kcount >= k){
                    break;
                }
                shm[count].dist = pair.first;
                shm[count].lineNum = pair.second;
                count++;
                kcount++;
            }


            exit(1);

        }
    }

    //wait for all the child procs to finish
    for(int i = 0; i < p; i++){
        //probably not enough checks for the procs waiting but
        // i'll come back later and fix it
        wait(NULL);
    }


    shmKeyPair* shm;
    //get the shared memory in the right address space
    if ((shm = (shmKeyPair *)shmat(shmId, NULL, 0)) == (shmKeyPair *) -1){
        std::cerr << "Init: Failed to attach shared memory (" << shmId << ")" << std::endl;
        return -1;
    }


    std::vector<shmKeyPair> finalResults(shm,shm+(k*p));

    std::sort(finalResults.begin(),finalResults.end(),shmKeyPairSort);

    finalResults.resize(k);

    for(int i = 0; i < 20; i++){
        std::cout<<finalResults.at(i).dist<<std::endl;
    }

    //delete the shrared mem, that stuff is scary
    if ((shmctl(shmId,IPC_RMID,0))==-1){
        std::cerr<<"shared mem couldn't be deleted"<<std::endl;
        return -1;
    }

    return 1;

}

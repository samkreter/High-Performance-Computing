#include "../include/vectorMatch.hpp"


# define ROWMATRIXPOS(rowSize , row, col) (rowSize * row) + col
# define LINENUM(rowSize , index) (rowSize / index)
# define LTOI(rowSize, lineNumber) (lineNumber * rowSize)


VectorMatch::VectorMatch(std::shared_ptr<MapString_t> nameMap, float* rawData, long lineLength){
    this->nameMap = nameMap;
    this->rawData = rawData;
    this->lineLength = lineLength;

    //create the line number to name map
    for(auto& pair : *(this->nameMap)){
        (*lineNumMap).insert(std::pair<long,std::string>(pair.second,pair.first));
    }

}

float VectorMatch::findDist(long start1, long start2){

    float sum = 0;


    //run the l1 norm formula
    for(int i = 0; i < lineLength; i++){

        sum += std::abs(rawData[ROWMATRIXPOS(lineLength,start1,i)] - rawData[ROWMATRIXPOS(lineLength,start2,i)]);
    }

    return sum / (float) lineLength;

}

/// print the vectors to a file, for the final output
int output_vector_to_file(std::string filename, std::vector<VectorMatch::nameKeyPair>* vec){

    std::ofstream outputFile(filename);
    std::ostringstream ossVec;


    if(outputFile.is_open()){

        for(auto& elem : *vec){
            ossVec<<elem.filename<<","<<elem.dist<<std::endl;
        }

        outputFile<<ossVec.str();

        outputFile.close();
        return 1;
    }
    return 0;
}


//just a helper function for the sort with my custom structs
bool shmKeyPairSort(const VectorMatch::shmKeyPair& pair1, const VectorMatch::shmKeyPair& pair2){
    return pair1.dist < pair2.dist;
}


//this is really slow but it'll work for now till I get to optimizing this
int createMapToLineNumber(std::map<long, std::string>* newMap, std::shared_ptr<VectorMatch::MapString_t> dMap){
    long lineCounter = 0;
    for(auto& data : *dMap){
        (*newMap).insert(std::pair<long,std::string>(lineCounter,data.first));
        lineCounter++;
    }

    return 1;
}


int VectorMatch::computVectorMatch(std::string cmpFile, int k, int p,std::chrono::duration<double>* time_elapse){


    //get all that shared mem stuff set up
    int shmId;          // ID of shared memory segment
    key_t shmKey = 123460;      // key to pass to shmget(), key_t is an IPC key type defined in sys/types
    int shmFlag = IPC_CREAT | 0666; // Flag to create with rw permissions
    pid_t pid;
    unsigned long * sharedIndexPtr = NULL;

    //store the pids for the procs
    std::vector<pid_t> minvan;

    //start and end for times the proc work
    std::chrono::time_point<std::chrono::system_clock> start, end;



    long cmpVecPos = nameMap->at(cmpFile);



    //get the number of lines each proc gets to process
    int divNum = nameMap->size() / p;


    //create the shared memeory
    if ((shmId = shmget(shmKey, (p * k * sizeof(shmKeyPair)) , shmFlag)) < 0){
        std::cerr << "Init: Failed to initialize shared memory (" << shmId << ")" << std::endl;
        return -1;
    }

    shmKeyPair* shm;
    //get the shared memory in the right address space
    if ((shm = (shmKeyPair *)shmat(shmId, NULL, 0)) == (shmKeyPair *) -1){
        std::cerr << "Init: Failed to attach shared memory (" << shmId << ")" << std::endl;
        return -1;
    }



    start = std::chrono::system_clock::now();
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
            long lineStatus = 0;
            int procNum = i;
            //store the results of the vector
            std::map<float,int> results;


            int topBound = ((procNum * divNum) + divNum);
            if(i == (p-1)){
                topBound += nameMap->size() % p;
            }

            std::cout<<"topboud: "<<topBound<<"j: "<<procNum*divNum;

            //get the distances and store them into a map that auto sorts by distance
            for(long j = procNum * divNum; j < topBound -1; j++){


                //add the distance to the results map
                results.insert(std::pair<float,long>(findDist(cmpVecPos,LTOI(lineLength,j)),j));


            }

            if(results.size() > k){
                std::cerr<<"the results var is greater than the k size"<<std::endl;
            }

            //add the results to the proper segment of the shared memory
            int count = procNum * k;

            for(auto& pair : results){
                shm[count].dist = pair.first;
                shm[count].lineNum = pair.second;
                count++;
            }

            //not usre if this is going to work but lets try
            //zero out the contents
            for(;count <= k; count++){
                shm[count].dist = FLT_MAX;
            }


            exit(1);

        }
        //parent
        else{
            minvan.push_back(pid);
        }
    }


    int status;
    //wait for all the child procs to finish
    for(int i = 0; i < p; i++){
        //probably not enough checks for the procs waiting but
        // i'll come back later and fix it
        waitpid(minvan.at(i),&status, 0);
    }


    //store the final results with line numbers
    std::vector<shmKeyPair> finalResultsNum(shm,shm+(k*p));

    //hold the final filname matches
    std::vector<nameKeyPair> finalResultsName(k);

    //sort the final results
    std::sort(finalResultsNum.begin(),finalResultsNum.end(),shmKeyPairSort);

    //cut them off at the knees
    finalResultsNum.resize(k);




    int indexer = 0;
    for(auto elem : finalResultsNum){
        finalResultsName.push_back(nameKeyPair());
        finalResultsName.at(indexer).filename = (*lineNumMap).at(elem.lineNum);
        finalResultsName.at(indexer).dist = elem.dist;
        indexer++;
    }


    //final cut off at the knees
    finalResultsName.resize(k);

    end = std::chrono::system_clock::now();

    //get the output out to that csv, yea
    output_vector_to_file("results.csv",&finalResultsName);

    *time_elapse = end - start;

    std::cout<<"Time for parent processing: "<<(*time_elapse).count()<<std::endl;


    //delete the shrared mem, that stuff is scary
    //but its actually working great this time around
    if ((shmctl(shmId,IPC_RMID,0))==-1){
        std::cerr<<"shared mem couldn't be deleted"<<std::endl;
        return -1;
    }

    return 1;

}







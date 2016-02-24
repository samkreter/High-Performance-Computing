#include "../include/parser.hpp"
#include "../include/vectorMatch.hpp"

#include <iterator>

using namespace std;

using MapString_t = std::map<std::string,long>;



int output_vector_to_file(std::string filename, std::vector<double> vec, int append);

int main(int argc, char** argv){


    //set up for the number of process
    vector<double> procs{1, 2, 4, 6, 8, 12, 16};
    vector<double> times;

    //just set up vars for the run trhoughs
    vector<string> inputFileNames;
    inputFileNames.push_back("../../../2100_HPC.csv");
    inputFileNames.push_back("../../../4200_HPC.csv");
    inputFileNames.push_back("../../../6300_HPC.csv");
    inputFileNames.push_back("../../../8400_HPC.csv");

    //you know just more set up stuff
    vector<string> inputFileFirsts;
    inputFileFirsts.push_back("agricultural/agricultural00.tif");
    inputFileFirsts.push_back("agricultural/agricultural00_rot_000.tif");
    inputFileFirsts.push_back("agricultural/agricultural00_rot_090.tif");
    inputFileFirsts.push_back("agricultural/agricultural00_rot_000.tif");

    chrono::duration<double> read_time_elapse;

    string filename("../../../6300_HPC.csv");



#if 1
    if(argc != 5){
        cerr<<"Arguments not correct, <query/_filename_line_to_match> <dataFile> <K> <P>"<<endl;
        exit(-1);
    }

    int k = 0;
    int pNumuser = 0;
    try{
        k = atoi(argv[3]);
        pNumuser = atoi(argv[4]);
    }
    catch(...){
        cerr<<"Arguments not correct, <query/_filename_line_to_match> <dataFile> <K> <P>"<<endl;
        exit(-1);
    }

    shared_ptr<MapString_t> nameMap(new MapString_t);
    shared_ptr<vector<float>> dataVector(new vector<float>);
    Parser p(nameMap,dataVector);


    if(p.parse_file(argv[2],&read_time_elapse)){
        VectorMatch v(nameMap,(*dataVector).data(),p.get_line_length());
        if(v.computVectorMatch(argv[1],k,pNumuser,&read_time_elapse)){
            cout<<"\noutput was writen to results.csv, thanks and I hope you have a decent day today"<<endl;
        }
    }

    #endif


//multi proc tests - only works if you change the above file locatoins to show
    //where the files are
#if 0
    {
        shared_ptr<MapString_t> nameMap(new MapString_t);
        shared_ptr<vector<float>> dataVector(new vector<float>);
        Parser p(nameMap,dataVector);

        if(p.parse_file(filename,&read_time_elapse)){
            cout<<"Time to load data struct: "<<read_time_elapse.count()<<"s"<<endl;


            VectorMatch v(nameMap,(*dataVector).data(),p.get_line_length());
            for(int i = 0; i < procs.size(); i++){
                chrono::duration<double> proc_time_elapse;
                cout<<procs.at(i)<<" procs"<<endl;
                v.computVectorMatch("agricultural/agricultural00_rot_090.tif",100,procs.at(i),&proc_time_elapse);
                //v.computVectorMatch("agricultural/agricultural00_rot_000.tif",100,procs.at(i),&proc_time_elapse);
                //v.computVectorMatch("agricultural/agricultural00.tif",100,procs.at(i),&proc_time_elapse);
                times.push_back(proc_time_elapse.count());
                cout<<endl<<endl;
            }

            //write the times to a file
            output_vector_to_file("test.csv",procs,0);
            output_vector_to_file("test.csv",times,1);


        }
    }

#endif

//multi file tests - only works if you change the above file locatoins to show
    //where the files are
#if 0


    //clear the times in the vector
    times.clear();
    vector<double> fileReadTimes;
    for(int i = 0; i < inputFileNames.size(); i++){

        shared_ptr<MapString_t> nameMap(new MapString_t);
        shared_ptr<vector<float>> dataVector(new vector<float>);
        Parser p(nameMap,dataVector);


        chrono::duration<double> proc_time_elapse;
        if(p.parse_file(inputFileNames.at(i),&read_time_elapse)){
            fileReadTimes.push_back(read_time_elapse.count());
            VectorMatch v(nameMap,(*dataVector).data(),p.get_line_length());
            v.computVectorMatch(inputFileFirsts.at(i),100,4,&proc_time_elapse);
            times.push_back(proc_time_elapse.count());
        }
        else{
            cerr<<"failed to parse file: "<<inputFileNames.at(i)<<endl;
            exit(-1);
        }
    }

    vector<double> inputNums;
    inputNums.push_back(2100);
    inputNums.push_back(4200);
    inputNums.push_back(6300);
    inputNums.push_back(8400);

    output_vector_to_file("multiFile.csv",inputNums,0);
    output_vector_to_file("multiFile.csv",times,1);
    output_vector_to_file("multiFile.csv",fileReadTimes,1);

#endif
    //run python scripts for graphing
    //cout<<"system output: "<<system("python ../plotter.py");


    return 0;

}



int output_vector_to_file(std::string filename, std::vector<double> vec, int append){
    std::fstream outputFile;
    std::ostringstream ossVec;

    if(append == 0){
        outputFile.open(filename,std::fstream::out);
    }
    else{
        outputFile.open(filename, std::fstream::out | std::fstream::app);
    }

    if(outputFile.is_open()){

        std::copy(vec.begin(), vec.end()-1,
        std::ostream_iterator<float>(ossVec, ","));
        ossVec << vec.back();
        outputFile<<ossVec.str()<<"\n";

        outputFile.close();
        return 1;
    }
    return 0;
}
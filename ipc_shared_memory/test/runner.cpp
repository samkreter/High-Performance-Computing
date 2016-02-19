#include "../include/parser.hpp"
#include "../include/vectorMatch.hpp"

#include <iterator>

using namespace std;

using MapString_t = std::map<std::string,std::vector<float>>;



int output_vector_to_file(std::string filename, std::vector<int> vec, std::vector<double> vec2);

int main(int argc, char** argv){



    vector<int> procs{1, 2, 4, 6, 8, 12, 16};
    vector<double> times;


    vector<string> inputFileNames;
    inputFileNames.push_back("../../../2100_HPC.csv");
    inputFileNames.push_back("../../../4200_HPC.csv");
    inputFileNames.push_back("../../../6300_HPC.csv");
    inputFileNames.push_back("../../../8400_HPC.csv");

    vector<string> inputFileFirsts;
    inputFileFirsts.push_back("agricultural/agricultural00.tif");
    inputFileFirsts.push_back("agricultural/agricultural00_rot_000.tif");
    inputFileFirsts.push_back("agricultural/agricultural00_rot_090.tif");
    inputFileFirsts.push_back("agricultural/agricultural00_rot_000.tif");

    chrono::duration<double> read_time_elapse;

    string filename("../../../6300_HPC.csv");
    //have to remeber to free it from the heap
    // cout<<"Please enter the file path relative to this execting program, for example '../test/HPC_DATA.csv': ";
    // cin>>filename;



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

    shared_ptr<MapString_t> dataMap(new MapString_t);
    Parser p(dataMap);

    if(p.parse_file(argv[2],&read_time_elapse)){
         VectorMatch v(dataMap);
         v.computVectorMatch(argv[1],k,pNumuser,&read_time_elapse);

    }

    cout<<"\noutput was writen to results.csv, thanks and I hope you have a decent day today"<<endl;

//multi proc tests
#if 0
    {
        shared_ptr<MapString_t> dataMap(new MapString_t);

        Parser p(dataMap);

        if(p.parse_file(filename,&read_time_elapse)){
            cout<<"Time to load data struct: "<<read_time_elapse.count()<<"s"<<endl;

            VectorMatch v(dataMap);
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
            output_vector_to_file("test.csv",procs,times);


        }
    }

#endif

//multi file tests
#if 0


    //clear the times in the vector
    times.clear();
    for(int i = 0; i < inputFileNames.size(); i++){
        shared_ptr<MapString_t> dataMap(new MapString_t);

        Parser p(dataMap);


        chrono::duration<double> proc_time_elapse;
        if(p.parse_file(inputFileNames.at(i),&read_time_elapse)){
            VectorMatch v(dataMap);
            v.computVectorMatch(inputFileFirsts.at(i),100,4,&proc_time_elapse);
            times.push_back(proc_time_elapse.count());
        }
        else{
            cerr<<"failed to parse file: "<<inputFileNames.at(i)<<endl;
            exit(-1);
        }
    }

    vector<int> inputNums;
    inputNums.push_back(2100);
    inputNums.push_back(4200);
    inputNums.push_back(6300);
    inputNums.push_back(8400);

    output_vector_to_file("multiFile.csv",inputNums,times);


    //run python scripts for graphing
    cout<<"system output: "<<system("python ../plotter.py");
#endif

    return 0;

}



int output_vector_to_file(std::string filename, std::vector<int> vec, std::vector<double> vec2){
    std::ofstream outputFile(filename);
    std::ostringstream ossVec, ossVec2;

    if(outputFile.is_open()){

        std::copy(vec.begin(), vec.end()-1,
        std::ostream_iterator<float>(ossVec, ","));
        ossVec << vec.back();
        outputFile<<ossVec.str()<<"\n";

        std::copy(vec2.begin(), vec2.end()-1,
        std::ostream_iterator<float>(ossVec2, ","));
        ossVec2 << vec2.back();
        outputFile<<ossVec2.str()<<"\n";


        outputFile.close();
        return 1;
    }
    return 0;
}
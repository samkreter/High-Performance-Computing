#include "../include/parser.hpp"
#include "../include/vectorMatch.hpp"

#include <iterator>

using namespace std;

using MapString_t = std::map<std::string,std::vector<float>>;



int output_vector_to_file(std::string filename, std::vector<int> vec, std::vector<double> vec2);

int main(){

    shared_ptr<MapString_t> dataMap(new MapString_t);

    Parser p(dataMap);

    vector<int> procs{1, 2, 4, 6, 8, 12, 16};
    vector<double> times;

    chrono::duration<double> read_time_elapse;

    string filename("../../../4200_HPC.csv");
    //have to remeber to free it from the heap
    // cout<<"Please enter the file path relative to this execting program, for example '../test/HPC_DATA.csv': ";
    // cin>>filename;

    if(p.parse_file(filename,&read_time_elapse)){
        cout<<"Time to load data struct: "<<read_time_elapse.count()<<"s"<<endl;

        VectorMatch v(dataMap);
        for(int i = 0; i < procs.size(); i++){
            chrono::duration<double> proc_time_elapse;
            cout<<procs.at(i)<<" procs"<<endl;
            v.computVectorMatch("agricultural/agricultural00_rot_000.tif",100,procs.at(i),&proc_time_elapse);
            //v.computVectorMatch("agricultural/agricultural00.tif",100,procs.at(i),&proc_time_elapse);
            times.push_back(proc_time_elapse.count());
            cout<<endl<<endl;
        }


        output_vector_to_file("test.csv",procs,times);

        cout<<"system output: "<<system("python ../plotter.py");

    }
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
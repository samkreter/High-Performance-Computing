#include "../include/parser.hpp"
#include "../include/vectorMatch.hpp"

#include <iterator>

using namespace std;




int main(){


    Parser p;

    chrono::duration<double> read_time_elapse;
    string filename("../test/HPC_DATA.csv");
    //have to remeber to free it from the heap
    // cout<<"Please enter the file path relative to this execting program, for example '../test/HPC_DATA.csv': ";
    // cin>>filename;

    if(p.parse_file(filename,&read_time_elapse)){

        VectorMatch v(p.getDataRef());

        v.computVectorMatch("agricultural/agricultural00.tif",100,2);

        cout<<"Time to load data struct: "<<read_time_elapse.count()<<"s"<<endl;
    }
    return 0;
}
#include "../include/parser.hpp"
#include "../include/vectorMatch.hpp"


using namespace std;




int main(){

    VectorMatch v(NULL);
    v.computVectorMatch("test",3,2);

    exit(-1);

    Parser p;

    chrono::duration<double> read_time_elapse;
    string filename("../test/HPC_DATA.csv");
    //have to remeber to free it from the heap
    // cout<<"Please enter the file path relative to this execting program, for example '../test/HPC_DATA.csv': ";
    // cin>>filename;

    if(p.parse_file(filename,&read_time_elapse)){

        auto test = p.getDataRef();

        cout<<test->at("agricultural/agricultural00.tif").at(0);

        exit(-1);
        cout<<"Time to load data struct: "<<read_time_elapse.count()<<"s"<<endl;
        if(p.find_column_bounds_rowbyrow()){
            cout<<"The program parsed "<<p.num_of_lines()<<" lines and "<<p.num_of_entries()<<" entries"<<endl;
            return 1;
        }
    }
    return 0;
}
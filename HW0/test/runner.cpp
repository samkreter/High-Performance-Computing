#include "../include/parser.hpp"


using namespace std;



int main(){

    Parser p;
    chrono::duration<double> read_time_elapse;
    //have to remeber to free it from the heap
    if(p.parse_file("../test/HPC_DATA.csv",&read_time_elapse)){
        cout<<"Time to load data struct: "<<read_time_elapse.count()<<"s"<<endl;

        p.find_column_bounds_rowbyrow();

        return 1;
    }
    return 0;
}
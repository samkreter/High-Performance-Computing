#include <iostream>

#include "../include/parser.hpp"

using namespace std;

int main(){

    Parser p;
    //watch out that the object stays in memory or the map will be deleted since it is
    // only a reference to the object that is reutrn
    Parser::MapString_t* dataMap = p.parse_file("../test/HPC_DATA.csv");

    // auto& start = (*dataMap).begin()->second;

    // for(auto i : start){
    //     cout<<i<<" ";
    // }

    // cout<<endl;

    cout<<"done";

    return 0;
}
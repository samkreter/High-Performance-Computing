#include "../include/parser.hpp"


Parser::Parser(){

}

int Parser::parse_file(std::string filename, std::chrono::duration<double>* time_elapse){

    if(!filename.empty()){
        std::chrono::time_point<std::chrono::system_clock> start, end;

        std::ifstream csvFile(filename);


        if(csvFile.is_open()){
            std::string line;
            std::string entryFName;
            start = std::chrono::system_clock::now();
            while(std::getline(csvFile,line)){
                std::stringstream lineStream(line);
                std::string cell;

                //get the filename for the map
                std::getline(lineStream,entryFName,',');

                dataMap.insert(std::pair<std::string,std::vector<float>>(entryFName,std::vector<float>()));

                while(std::getline(lineStream,cell,',')){
                    dataMap.at(entryFName).push_back(std::stof(cell));
                }
            }

            end = std::chrono::system_clock::now();

            *time_elapse = end - start;

            csvFile.close();
            return 1;
        }
        std::cerr<<"Couldn't open file\n";
        return 0;
    }
    std::cerr<<"Filename Can't be empty\n";
    return 0;

}


size_t Parser::num_of_entries(){
    size_t num_entries = 0;
    for(auto& row : dataMap){
        num_entries += row.second.size();
    }

    return num_entries;
}

size_t Parser::num_of_lines(){
    return dataMap.size();
}


int Parser::find_column_bounds_rowbyrow(){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::vector<float> holderMax;
    std::vector<float> holderMin;

    size_t size = dataMap.begin()->second.size();

    start = std::chrono::system_clock::now();
    for(int i = 1; i < size; i++){
        float colMin = FLT_MAX, colMax = FLT_MIN;
        for(auto& row : dataMap){
            if(row.second.at(i) > colMax){
                colMax = row.second.at(i);
            }
            if(row.second.at(i) < colMin){
                colMin = row.second.at(i);
            }
        }
        holderMax.push_back(colMax);
        holderMin.push_back(colMin);
    }
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> time_elapse = end - start;

    output_vector_to_file("outputfile.csv",holderMin, holderMax);

    std::cout<<"Time to find bounds: "<<time_elapse.count()<<"s\n"<<std::endl;
    std::cout<<"Output can be found in outputfile.csv for bounds"<<std::endl;

    return 1;


}


int Parser::output_vector_to_file(std::string filename, std::vector<float> vec, std::vector<float> vec2){
    std::ofstream outputFile(filename);
    std::ostringstream ossVec, ossVec2;

    if(outputFile.is_open()){

        outputFile<<"Mins,";
        std::copy(vec.begin(), vec.end()-1,
        std::ostream_iterator<float>(ossVec, ","));
        ossVec << vec.back();
        outputFile<<ossVec.str()<<"\n";

        outputFile<<"Maxs,";
        std::copy(vec2.begin(), vec2.end()-1,
        std::ostream_iterator<float>(ossVec2, ","));
        ossVec2 << vec2.back();
        outputFile<<ossVec2.str()<<"\n";



        outputFile.close();
        return 1;
    }
    return 0;
}

Parser::~Parser(){

}
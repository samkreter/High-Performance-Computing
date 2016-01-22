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
    return dataMap.size();
}


int Parser::find_column_bounds_rowbyrow(){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::vector<float> holderMax;
    std::vector<float> holderMin;


    size_t size = dataMap.begin()->second.size();

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

    output_vector_to_file("outputfile.csv",holderMax);

    return 1;


}

int Parser::find_column_bounds_asGo(){
    //initlize the holder vector to the correct size to stop the overhead costs of resizing
    std::vector<float> holderMax(dataMap.begin()->second.size(),FLT_MIN);
    std::vector<float> holderMin(dataMap.begin()->second.size(),FLT_MAX);


    std::chrono::time_point<std::chrono::system_clock> start, end;
    int size = 0;

    start = std::chrono::system_clock::now();

    for(auto& row : dataMap){
        size = row.second.size();
        for(int i = 1; i < size; i++){
            if(row.second.at(i) < holderMin.at(i)){
                holderMin.at(i) = row.second.at(i);
            }
            if(row.second.at(i) > holderMax.at(i)){
                holderMin.at(i) = row.second.at(i);
            }
        }
    }
    end = std::chrono::system_clock::now();

    output_vector_to_file("outputfile.csv",holderMin);


    std::chrono::duration<double> time_elapse = end - start;
    std::cout<<"Last execution "<<time_elapse.count()<<std::endl;
    return 0;
}

int Parser::output_vector_to_file(std::string filename, std::vector<float> vec){
    std::ofstream outputFile(filename);
    std::ostringstream oss;

    if(outputFile.is_open()){
        std::copy(vec.begin(), vec.end()-1,
        std::ostream_iterator<int>(oss, ","));
        oss << vec.back();
        outputFile<<oss.str()<<"\n";

        outputFile.close();
        return 1;
    }
    return 0;
}

Parser::~Parser(){

}
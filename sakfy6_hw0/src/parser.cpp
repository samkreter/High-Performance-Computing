#include "../include/parser.hpp"



int Parser::parse_file(std::string filename, std::chrono::duration<double>* time_elapse){

    if(!filename.empty()){
        //set up the chono vars
        std::chrono::time_point<std::chrono::system_clock> start, end;
        //open the input file
        std::ifstream csvFile(filename);

        //make sure all good in the file
        if(csvFile.is_open()){

            std::string line;
            std::string entryFName;
            //get the start time to find time elapse
            start = std::chrono::system_clock::now();
            //read a line at a time from the file
            while(std::getline(csvFile,line)){
                std::stringstream lineStream(line);
                std::string cell;

                //get the filename for the map
                std::getline(lineStream,entryFName,',');

                //insert the file name as the key for a vector of floats into the map
                dataMap.insert(std::pair<std::string,std::vector<float>>(entryFName,std::vector<float>()));

                //use a string stream to separte the columns
                while(std::getline(lineStream,cell,',')){
                    //I love try catches, that c++ life
                    try{
                        dataMap.at(entryFName).push_back(std::stof(cell));
                    }
                    //not so good to just catch all but it'll have to do for now
                    catch(...){
                        std::cerr<<"Could not convert string to float or rows are not the same length"<<std::endl;
                        return 0;
                    }
                }
            }
            //get the end time
            end = std::chrono::system_clock::now();

            //do math good
            *time_elapse = end - start;

            //always close that file
            csvFile.close();
            return 1;
        }
        std::cerr<<"Couldn't open file\n";
        return 0;
    }
    std::cerr<<"Filename Can't be empty\n";
    return 0;

}

//I think this is what is wanted with the number of entries
size_t Parser::num_of_entries(){
    size_t num_entries = 0;
    //loop through references of each row in the ordered map and get the size
    for(auto& row : dataMap){
        //just use the vector size function to get the number of entries besiseds the filename
        num_entries += row.second.size();

        //this accounts for the file names that are not counted in the vector size()
        num_entries++;
    }

    return num_entries;
}

//there is a map entry for each line so let the map struct do the actual work.
// its alot more efficent, smart people wrote that, not just some random kid in comp sci
// college. Probably some nice person in a basement that is covered with arduinos and doritos.
size_t Parser::num_of_lines(){
    return dataMap.size();
}


int Parser::find_column_bounds_rowbyrow(){
    //set up all those holder vars
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::vector<float> holderMax;
    std::vector<float> holderMin;

    //so we know how many columns there are,
    // this is assuming that each line has something, dangous ut i'll fix it next iterations
    size_t size = dataMap.begin()->second.size();

    start = std::chrono::system_clock::now();
    //go down the columns and find the maxes and mins
    for(int i = 1; i < size; i++){

        //set min to max for float and max to min for float
        float colMin = FLT_MAX, colMax = FLT_MIN;

        try{
            //gotta love the c++11 foreach loop with references
            for(auto& row : dataMap){
                if(row.second.at(i) > colMax){
                    colMax = row.second.at(i);
                }
                if(row.second.at(i) < colMin){
                    colMin = row.second.at(i);
                }
            }
        }
        catch(...){
            std::cerr<<"Not all rows are the same length"<<std::endl;
            return 0;
        }
        //add the maxes and mins to the holder vectors
        holderMax.push_back(colMax);
        holderMin.push_back(colMin);
    }
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> time_elapse = end - start;

    //print the vectors to and output csv
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

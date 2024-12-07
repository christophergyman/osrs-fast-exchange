#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

// function to print full json
void print_full_json(const std::fstream &file_stream){
    file_stream.seekp(0);
    std::cout << file_stream.rdbuf();
    return;
}


// function that returns json as a filestream object
nlohmann::json get_json_obj(const std::string &&filename){
    // read file into data stream
    const char *cstr = filename.c_str();
    std::ifstream stream{cstr};

    // convert datastream to nlohmann json object
    nlohmann::json data (nlohmann::json::parse(stream));
    return data;
}


int main (){

    std::string empty_string; [] 

    std::string filename = "api_call.json";
    nlohmann::json json_data = get_json_obj(filename);

    return 0;
}

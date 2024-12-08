#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <curl/curl.h>


// function that returns json as a filestream object
nlohmann::json get_json_obj(const std::string &filename){
    // read file into data stream
    const char *cstr = filename.c_str();
    std::ifstream stream{cstr};

    // convert datastream to nlohmann json object
    nlohmann::json data (nlohmann::json::parse(stream)); return data;
}

// function to print out json value
void json_dump(const nlohmann::json &json_data){
    std::cout << json_data.dump();
    return;
}

// WriteCallBack used for curl function
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// curl request
nlohmann::json curl_request(const int &item_id){
    // update request string to include the item_id
    std::string string_item_id = std::to_string(item_id);
    std::string request_string = "http://services.runescape.com/m=itemdb_oldschool/api/catalogue/detail.json?item=8";

    
    // curl request objects
    CURL *curl;
    CURLcode res;
    std::string read_buffer;

    // empty header list
    struct curl_slist *list = NULL;

    curl = curl_easy_init();
    if(curl){
        // curl options
        curl_easy_setopt(curl, CURLOPT_URL, "http://services.runescape.com/m=itemdb_oldschool/api/catalogue/detail.json?item=8");

        list = curl_slist_append(list, "Accept: application/json");
        list = curl_slist_append(list, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36");

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, &list);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        nlohmann::json response_json = read_buffer;
        return response_json;
        // std::cout << read_buffer << std::endl;
    } 
    else{
        std:: cout << "[error]: failed to create curl response request";
        return -1;
    }
}


int main (){
    int item_id = 8;
    nlohmann::json json_data = curl_request(item_id);
    //std::cout << json_data.at("icon");
    return 0;
}

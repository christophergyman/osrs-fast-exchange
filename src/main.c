// C program to illustrate the use of printf function
#include <stdio.h>
#include <string.h>
#include <cjson/cJSON.h> 

// function read json object 
int read_json(char *filename, char *key){
    // open the file 
    FILE *fp = fopen(filename, "r"); 
    if (fp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    } 
    // read the file contents into a string 
    char buffer[1024]; 
    int len = fread(buffer, 1, sizeof(buffer), fp); 
    fclose(fp); 
    // put json data into json pointer
    cJSON *json = cJSON_Parse(buffer); 
    if (json == NULL){
        printf("[error]: failed to parse json \n");
        return -1;
    }
    // Get pair from key in the cJson object  
    cJSON *json_keypair = cJSON_GetObjectItemCaseSensitive(json, key);

    // check keypair value and return it
    if (cJSON_IsString(json_keypair)){
        printf("it is a string: %s \n", json_keypair->valuestring);
    }
    if (cJSON_IsNumber(json_keypair)){
        printf("it is a integer: %d \n", json_keypair->valueint);
    }
    if (cJSON_IsObject(json_keypair)){
        printf("it is an object: \n");
    }
}

int main(){
    char *key = "name";
    char *filename = "data.json";
    read_json(filename, key);
    return 0;
}

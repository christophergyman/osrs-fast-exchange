// C program to illustrate the use of printf function
#include <stdio.h>
#include <string.h>
#include <cjson/cJSON.h> 

int create_json(){
    // create a cJSON object 
    cJSON *json = cJSON_CreateObject(); 
    cJSON_AddNumberToObject(json, "id", 11832); 
    cJSON_AddStringToObject(json, "name", "Bandos Chestplate"); 

    // convert the cJSON object to a JSON string 
    char *json_str = cJSON_Print(json); 

    // write the JSON string to a file 
    FILE *fp = fopen("data.json", "w"); 
    if (fp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    } 
    printf("%s\n", json_str); 
    fputs(json_str, fp); 
    fclose;
    // free the JSON string and cJSON object 
    cJSON_free(json_str); 
    cJSON_Delete(json); 
    return 1;
}

struct ReturnStruct{
    int integer_value;
    char string_value[1024];
};

// function read json object 
struct ReturnStruct *read_json(char *filename ,char *request_datatype, char *key){
    // initialise return struct
    struct ReturnStruct *return_struct;
    return_struct.string_value = json_keypair->valuestring;


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

    char *datatype_string = "string";

    // check type being requested 'string' 'id' 'substring'
    if (strcmp(request_datatype, datatype_string) == 0 ){
        printf("[log]: request_datatype: %s \n", datatype_string);

        // access the JSON data "name value"
        cJSON *json_keypair = cJSON_GetObjectItemCaseSensitive(json, key); 
        if (cJSON_IsString(json_keypair) && (json_keypair->valuestring != NULL)) { 
            // printf("json_keypair: %s\n", json_keypair->valuestring); 
            return_struct.string_value = json_keypair->valuestring;
            return return_struct;
        } 
    }
  

    // // access the Id value from the json
    // cJSON *id = cJSON_GetObjectItemCaseSensitive(json, "id");
    // printf("ID: %d\n", id->valueint);

    // // access the subitem value from the json
    // cJSON *subitem = cJSON_GetObjectItemCaseSensitive(json, "sub_item");
    // cJSON *child_element = subitem->child;
    // printf("special: %s \n", child_element->valuestring);
  
    // // delete the JSON object 
    // cJSON_Delete(json); 
    return 0; 
}

int main()
{
    char *type = "string";
    char *key = "name";
    char *filename = "data.json";
    read_json(filename, type, key);
    return 0;
}

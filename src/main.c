// C program to illustrate the use of printf function
#include <stdio.h>
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
    return 0;
}

int read_json(){
    // open the file 
    FILE *fp = fopen("data.json", "r"); 
    if (fp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    } 
  
    // read the file contents into a string 
    char buffer[1024]; 
    int len = fread(buffer, 1, sizeof(buffer), fp); 
    fclose(fp); 
  
    // parse the JSON data 
    cJSON *json = cJSON_Parse(buffer); 
    if (json == NULL) { 
        const char *error_ptr = cJSON_GetErrorPtr(); 
        if (error_ptr != NULL) { 
            printf("Error: %s\n", error_ptr); 
        } 
        cJSON_Delete(json); 
        return 1; 
    } 
  
    // access the JSON data "name value"
    cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name"); 
    if (cJSON_IsString(name) && (name->valuestring != NULL)) { 
        printf("Name: %s\n", name->valuestring); 
    } 

    // access the Id value from the json
    cJSON *id = cJSON_GetObjectItemCaseSensitive(json, "id");
    printf("ID: %d\n", id->valueint);

    // access the subitem value from the json
    cJSON *subitem = cJSON_GetObjectItemCaseSensitive(json, "sub_item");
    cJSON *child_element = subitem->child;
    printf("special: %s \n", child_element->valuestring);
  
    // delete the JSON object 
    cJSON_Delete(json); 
    return 0; 
}

int main()
{
    printf(" \n");
    read_json();
    return 0;
}

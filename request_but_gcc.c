#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
void httpsGet(char url[]);
int main(void)
{
    char firstname[30], lastname[30];
    char second_string[20]; //
    char name[60];
        
    char url[] = "https://api.genius.com/search?q=";
    char geniusToken[] = "mXWeiTbMTOxwTP87bXlHJtTKcaam60Njvfb5OsR8XAHflIqFKvGEgGuAkXZ2dtkC";
    printf("Hello and welcome to the music finder thingy!\nPlease input the name of the artist you would like to view...\n");
    scanf("%s", firstname);

    int i; 


    for(i=0;url[i]!='\0';i++);   
      
      
    for(int j=0;firstname[j]!='\0';j++)  
    {  
        
        url[i]=firstname[j];  
        i++;  
    }  
    url[i]='\0';  
    printf("%s\n", firstname);
    //strcat(url, firstname);
    httpsGet(url);
return 0;
}


void httpsGet(char url[])
{
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    //char* auth = "Authorization: Bearer ";
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist* headers = NULL;
        //strcat("Authorization: Bearer ",  "mXWeiTbMTOxwTP87bXlHJtTKcaam60Njvfb5OsR8XAHflIqFKvGEgGuAkXZ2dtkC");
        headers = curl_slist_append(headers, "Authorization: Bearer mXWeiTbMTOxwTP87bXlHJtTKcaam60Njvfb5OsR8XAHflIqFKvGEgGuAkXZ2dtkC");
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);


}

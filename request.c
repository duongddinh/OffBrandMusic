#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
char* httpsGet(char token[], char url[]);
int testCode();
int main(void)
{
    char firstname[30], lastname[30], url[60];
    char name[60];
    char genius[] = "https://api.genius.com/search?q=";
    strcpy(url, genius);
    char space[] = "%20";
    char geniusToken[] = "mXWeiTbMTOxwTP87bXlHJtTKcaam60Njvfb5OsR8XAHflIqFKvGEgGuAkXZ2dtkC";
    printf("Hello and welcome to the music finder thingy!\nPlease input the name of the artist you would like to view...\n");
    scanf("%s %s", firstname, lastname);
    strcpy(name, firstname);
    strcat(name, space);
    strcat(name, lastname);
    strcat(url, name);
    httpsGet(geniusToken, url);
}


char* httpsGet(char token[], char url[])
{
    CURL* curl;
    CURLcode res;
    char auth[100];
    curl = curl_easy_init();
    char authBLEH[] = "Authorization: Bearer ";
    strcpy(auth, authBLEH);
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist* headers = NULL;
        strcat(auth, token);
        headers = curl_slist_append(headers, auth);
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
}


//Hard Coded Http Request
//int testCode()
//{
//    CURL* curl;
//    CURLcode res;
//    curl = curl_easy_init();
//    if (curl)
//    {
//        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
//        curl_easy_setopt(curl, CURLOPT_URL, "https://api.genius.com/search?q=Kendrick%20Lamar");
//        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
//        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
//        struct curl_slist* headers = NULL;
//        headers = curl_slist_append(headers, "Authorization: Bearer mXWeiTbMTOxwTP87bXlHJtTKcaam60Njvfb5OsR8XAHflIqFKvGEgGuAkXZ2dtkC");
//        headers = curl_slist_append(headers, "Accept: application/json");
//        headers = curl_slist_append(headers, "Content-Type: application/json");
//        headers = curl_slist_append(headers, "charset: utf-8");
//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//        res = curl_easy_perform(curl);
//    }
//    curl_easy_cleanup(curl);
//}
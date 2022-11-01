#include <stdio.h>
#include <curl/curl.h>
char* httpsGet(char* code, char* url);
int main(void)
{
    char firstname[30], lastname[30];
    char name[60];
    char* url = "https://api.genius.com/search?q=";
    char* geniusToken = "mXWeiTbMTOxwTP87bXlHJtTKcaam60Njvfb5OsR8XAHflIqFKvGEgGuAkXZ2dtkC";
    printf("Hello and welcome to the music finder thingy!\nPlease input the name of the artist you would like to view...\n");
    scanf_s("%s %s", firstname, _countof(firstname), lastname, _countof(lastname));
    strcat(name, firstname);
    strcat(name, lastname);
    strcat(url, name);
    httpsGet(geniusToken, name);

}


char* httpsGet(char* code, char* url)
{
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    char* auth = "Authorization: Bearer ";
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist* headers = NULL;
        strcat(auth, code);
        headers = curl_slist_append(headers, auth);
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
}
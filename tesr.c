#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "mjson.h"

char* httpsGet(char token[], char url[]);
int testCode();

  struct MemoryStruct chunk;

struct MemoryStruct {
  char *memory;
  size_t size;
};

struct my_object {
    char text[100];
    char flag[100];
    int count;
    char next[100];
    char next2[100];
};


/* 
struct my_object_list {
    int nobjects;
    struct my_object list[100];
};
*/
int json_myobj_read(const char *buf, struct my_object *myobj) {

       const struct json_attr_t json_attrs[] = {
         {"annotation_count", t_integer, .addr.integer = &(myobj->count),
                    .len = sizeof(myobj->count)},
                     {"api_path", t_string, .addr.string = &(myobj->next),
                    .len = sizeof(myobj->next)},
        {"artist_names", t_string, .addr.string = myobj->text,
                .len = sizeof(myobj->text)},
       {"full_title", t_string, .addr.string = &(myobj->flag), 
                   .len = sizeof(myobj->flag)},
                   {NULL},
        
    };


/*
  
    const struct json_attr_t json_attrs_subobject[] = {
        {"index", t_string, STRUCTOBJECT(struct my_object, text),
                .len = sizeof(obj_list->list[0].text)},
         {"flag", t_integer, STRUCTOBJECT(struct my_object, flag)},
        {"count", t_integer, STRUCTOBJECT(struct my_object, count)},
        {NULL},
    };
*/

  /*
    const struct json_attr_t json_attrs_objects[] = {
        {"class", t_check, .dflt.check = "OBJECTS"},
        {"hits", t_array, STRUCTARRAY(obj_list->list,
                json_attrs_subobject,
                &(obj_list->nobjects))},
        {NULL},
    };*/

    //memset(obj_list, '\0', sizeof(*obj_list));

    return json_read_object(buf, json_attrs, NULL);
}

 
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}


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
    return 0;
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
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        res = curl_easy_perform(curl);
    }

    //struct my_object *myobj = malloc(sizeof(struct my_object));

       // struct my_object_list *obj_list = malloc(sizeof(struct my_object_list));
 //char test[] = "{\"hits\": [{\"index\": \"sample zero\", \"flag\": 3, \"count\": 2}, {\"index\": \"sample one\", \"flag\": 3, \"count\": 5}]}}}}}";
    /* Call object list parsing function */

    //char test[] = "{\"text\": \"sample message\", \"flag\": \"true\", \"count\": \"5\"}}}}{\"text\": \"sample message\", \"flag\": \"true\", \"count\": \"5\"}{\"text\": \"sample message\", \"flag\": \"true\", \"count\": \"5\" [][][]}{}{}";
    //char test[] = "{\"annotation_count\": 20,\"api_path\": \"/songs/3039923\",\"artist_names\": \"Kendrick Lamar\",\"full_title\": \"HUMBLE. by Kendrick Lamar\", \"lol\" : {\"hello\" : 3}";
        // memmove(chunk.memory, chunk.memory+34+55+9, strlen(chunk.memory));
        
    //printf(chunk.memory);

char *memory2 = chunk.memory;
    char w[10] = "full";  
int totall = 0;
   int i2=0,k2=0,c2,index2;
 const char deli[] = "\""; 
/*
while (totall < 10){

    int clol = 0;

           while(memory2[i2]!='\0' && clol == 0)
    {
        
        if(memory2[i2]==w[0])
        {
            k2=1;
            for(c2=1;w[c2]!='\0';c2++)
            {
                if(memory2[i2+c2]!=w[c2])
                {
                 k2=0;
                 break;
                }
            }
        
        }
        if(k2==1)
        {
                index2=i2;
                clol = 1;
                totall++;
        }
        i2++;
        k2=0;    
    }
        memmove(memory2, memory2+index2+13 ,strlen(memory2));
        strtok(memory2, deli); 
}
printf("%d",totall);
*/


int numbersong = 4;
int countsong = 0;
    int i=0,k=0,c,index;
while (countsong < numbersong){

    int clol = 0;

           while(chunk.memory[i]!='\0' && clol == 0)
    {
        
        if(chunk.memory[i]==w[0])
        {
            k=1;
            for(c=1;w[c]!='\0';c++)
            {
                if(chunk.memory[i+c]!=w[c])
                {
                 k=0;
                 break;
                }
            }
        
        }
        if(k==1)
        {
                index=i;
                clol = 1;
        }
        i++;
        k=0;    
    }
   // printf("%d",index);
    memmove(chunk.memory, chunk.memory+index+13 ,strlen(chunk.memory));
    
     // deli could also be declared as [2] or as const char *. Take your pick...
    char *token2;
    //printf(chunk.memory);
    token2 = strtok(chunk.memory, deli); 
    printf("%s\n", token2);   //int status = json_myobj_read(test, myobj);
    countsong++;
   // doAgain();
}
    //if (status == 0) {
        //printf("text: %s\n", myobj->text);
      //  printf("flag: %s\n", myobj->flag);
        //printf("count: %s\n", myobj->count);
        //int i;
        //for (i = 0; i < obj_list->nobjects; i++) {
            //printf("Object %d:\n", i);
          //  printf("  text: %s\n", obj_list->list[i].text);
           //printf("  flag: %s\n", obj_list->list[i].flag);
           //printf("  count: %d\n", obj_list->list[i].count);

        //}
    //} else {
       // puts(json_error_string(status));
  //  } 
 //printf(chunk.memory);
  free(chunk.memory);

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

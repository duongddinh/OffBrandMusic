#define _GNU_SOURCE
#include <gtk/gtk.h>
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/* Variable Declarations */
int testCode();
char *token2;
char *token3;
char *finalest;
    char genioslink[200] = "https://genius.com";

GtkWidget *firstnameLabel, *firstnameEntry, *lastnameLabel, *lastnameEntry, *searchBtn, *grid, *showLyricBtn;
struct MemoryStruct chunk;

/* Function Prototypes */
int main2(const gchar *, const gchar *);
void parseJson();
void getLyric() ;
void httpsGet(char token[], char url[]);

struct MemoryStruct {
    char *memory;
    size_t size;
};

bool file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp); // close the file
    }
    return is_exist;
}

void open_website_part(char* i) {

    char *filename = "lyricart.py";
            char *cmd;

    if (file_exists(filename)){
            char *tokentest = strdup(finalest);
            asprintf(&cmd, "python3 lyricart.py \"%s\"", tokentest);
            system(cmd);

        }
    else {
    #ifdef  __linux__
    asprintf(&cmd, "xdg-open %s", i);
    system(cmd);
    #elif __APPLE__
    asprintf(&cmd, "OPEN %s", i);
    system(cmd);
    #elif __WIN32__
    asprintf(&cmd, "START %s", i);
    system(cmd);
    #endif
}
    free(cmd);
}


void search_button_clicked(GtkWidget *wid,gpointer data) {
    const gchar *searchData = gtk_entry_get_text(GTK_ENTRY(firstnameEntry));
    const gchar *searchData2 = gtk_entry_get_text(GTK_ENTRY(lastnameEntry));
            gtk_widget_show(showLyricBtn);

    main2(searchData, searchData2);
    
    gtk_label_set_text(GTK_LABEL(data), finalest);
    gtk_entry_set_text(GTK_ENTRY(firstnameEntry),"");
    gtk_entry_set_text(GTK_ENTRY(lastnameEntry),"");
}



void Lyric_button_clicked(GtkWidget *wid,gpointer data) {
        char *tokentest = strdup(finalest);

        printf("%s", tokentest);

   open_website_part(genioslink);
    /*
    GtkApplication* app2 = gtk_application_new ("xyz.null0verflow", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app2, "activate", G_CALLBACK(NULL), NULL);

    GtkWidget *window2;
    window2 = gtk_application_window_new (app2);
    gtk_window_set_title (GTK_WINDOW (window2), "Lyric");
    gtk_window_set_default_size (GTK_WINDOW (window2), 250, 600);
    GtkWidget *box2; 
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);
    gtk_container_add(GTK_CONTAINER(window2),box2);
    gtk_widget_show_all (window2);
    */

}

static void activate (GtkApplication* app, gpointer user_data) {
    GtkWidget *window;
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "one of the top hits by artist");
    gtk_window_set_default_size (GTK_WINDOW (window), 500, 400);
    
    GtkWidget *showSearch;
    firstnameLabel = gtk_label_new("First name:");
    firstnameEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(firstnameEntry),"first name");
    //GIcon *icon; 
    //GFile *path;
    //path = g_file_new_for_path("");
    //icon = g_file_icon_new(path);
    //gtk_entry_set_icon_from_gicon(GTK_ENTRY(firstnameEntry),GTK_ENTRY_ICON_PRIMARY,icon);
    
    lastnameLabel = gtk_label_new("Lastname:");
    lastnameEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(lastnameEntry),"last name");
    //gtk_entry_set_visibility(GTK_ENTRY(lastnameEntry),FALSE);
    searchBtn = gtk_button_new_with_label("search");

    showLyricBtn = gtk_button_new_with_label("Show Lyric");

    showSearch = gtk_label_new("");
    
    g_signal_connect(searchBtn,"clicked",G_CALLBACK(search_button_clicked),showSearch);

    g_signal_connect(showLyricBtn,"clicked",G_CALLBACK(Lyric_button_clicked),showSearch);

    
    GtkWidget *box; box = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);
    gtk_box_pack_start(GTK_BOX(box),firstnameLabel,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),firstnameEntry,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),lastnameLabel,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),lastnameEntry,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),searchBtn,FALSE,FALSE,0);


    gtk_box_pack_start(GTK_BOX(box),showSearch,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),showLyricBtn,FALSE,FALSE,0);

    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_widget_show_all (window);
        gtk_widget_hide(showLyricBtn);

}

static size_t

WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
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

int main(int argc,char **argv) {
    GtkApplication *app;
    int status;
    app = gtk_application_new ("xyz.null0verflow", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    return status;
}

 int main2(const gchar firstname[30], const gchar lastname[30]) {
    char genius[60] = "https://api.genius.com/search?q=";
    char geniusToken[] = "mXWeiTbMTOxwTP87bXlHJtTKcaam60Njvfb5OsR8XAHflIqFKvGEgGuAkXZ2dtkC";
    strcat(genius, firstname);
    strcat(genius, "%20");
    strcat(genius, lastname);   
    httpsGet(geniusToken, genius);
    return 0;
}

void httpsGet(char token[], char url[]) {
    CURL* curl;
    CURLcode res;
    char auth[100];
    curl = curl_easy_init();
    char authBLEH[] = "Authorization: Bearer ";
    strcpy(auth, authBLEH);
    
    if (curl) {
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
    
  //  printf("%s", chunk.memory);
    parseJson();
    free(chunk.memory);
    
    curl_easy_cleanup(curl);
}


void getLyric() {
    char url[20];
    char nexttt[200];
//char *memory3 = chunk.memory;
char *memory2 = strdup(chunk.memory);
//strcpy(memory2, chunk.memory);

    char w2[10] = "\"path";  

int totall = 0;
   int i2=0,k2=0,c2,index2;
 const char deli[] = "\""; 



    int clol2 = 0;

           while(memory2[i2]!='\0' && clol2 == 0)
    {
        
        if(memory2[i2]==w2[0])
        {
            k2=1;
            for(c2=1;w2[c2]!='\0';c2++)
            {
                if(memory2[i2+c2]!=w2[c2])
                {
                 k2=0;
                 break;
                }
            }
        
        }
        if(k2==1)
        {
                index2=i2;
                clol2 = 1;
        }
        i2++;
        k2=0;    
    }
        memmove(memory2, memory2+index2+8 ,strlen(memory2));
           //char *token3;
      token3=  strtok(memory2, deli); 
strcat(genioslink,token3);
      printf("%s\n", genioslink);

}
void parseJson() {
    memmove(chunk.memory, chunk.memory+34+55+9, strlen(chunk.memory));
      getLyric() ;

    char w[10] = "full";
    int i=0,k=0,c,index;
    int clol=0;
    while(chunk.memory[i]!='\0' && clol == 0) {
        if(chunk.memory[i]==w[0]) {
            k=1;
            for(c=1;w[c]!='\0';c++) {
                if(chunk.memory[i+c]!=w[c]) {
                    k=0;
                    break;
                }
            }
        }
        if(k==1) {
            index=i;
            clol=1;
        }
        
        i++;
        k=0;
    }
    
    //printf (index);
    memmove(chunk.memory, chunk.memory+index+13 ,strlen(chunk.memory));
    const char deli[] = "\""; 
    
    token2 = strtok(chunk.memory, deli); 
    finalest = strdup(token2);
}

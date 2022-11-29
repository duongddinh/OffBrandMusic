#define _GNU_SOURCE
#include <gtk/gtk.h>
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


struct MemoryStruct {
    char *memory;
    size_t size;
};
struct MemoryStruct chunk;
struct SongStruct
{
    struct SongStruct* next;
    char Song[100];

};

struct ArtistStruct
{
    struct ArtistStruct* next;
    char ArtistName[100];

};

struct LyricStruct
{
    struct LyricStruct* next;
    char LyricURL[200];
};

struct All
{
    struct All* next;
    char ArtistName[100];
    char Song[100];
    char LyricURL[200];

} *temp2;

/* Variable Declarations */
int testCode();
char *token2;
char *token3;
char *finalest;
char genioslink[200] = "https://genius.com";
struct All* AllHead = NULL;
struct All* AllTemp = NULL;
char *song1;
char *song2;
char *song3;
char *lyric1;
char *lyric2;
char *lyric3;
GtkWidget *firstnameLabel, *firstnameEntry, *lastnameLabel, *lastnameEntry, *searchBtn, *grid, *showLyricBtn, *showLyricBtn1, *showLyricBtn2;

/* Function Prototypes */
int main2(const gchar *, const gchar *);
void parseJson();
void getLyric() ;
void httpsGet(char token[], char url[]);


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

void open_website_part(char* i, char *songname) {

    char *filename = "lyricart.py";
            char *cmd;

    if (file_exists(filename)){
          //  char *tokentest = strdup(finalest);
            asprintf(&cmd, "python3 lyricart.py \"%s\"", songname);
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
    struct All* temp;
    const gchar *searchData2, *searchData = NULL;
    searchData = gtk_entry_get_text(GTK_ENTRY(firstnameEntry));
    searchData2 = gtk_entry_get_text(GTK_ENTRY(lastnameEntry));
    gtk_widget_show(showLyricBtn2);
    gtk_widget_show(showLyricBtn1);
    gtk_widget_show(showLyricBtn);
    main2(searchData, searchData2);
    
    gtk_label_set_text(GTK_LABEL(data), "Click on each song to see the lyric");
    gtk_button_set_label(GTK_BUTTON(showLyricBtn), song1);
    gtk_button_set_label(GTK_BUTTON(showLyricBtn1), song2);
    gtk_button_set_label(GTK_BUTTON(showLyricBtn2), song3);
    gtk_entry_set_text(GTK_ENTRY(firstnameEntry),"");
    gtk_entry_set_text(GTK_ENTRY(lastnameEntry),"");
}



void Lyric_button_clicked(GtkWidget *wid,gpointer data) {
  //  char *tokentest = strdup(finalest);

   // printf("%s", tokentest);
    gchar *text = gtk_button_get_label (showLyricBtn);

    open_website_part(lyric1, text);
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
void Lyric1_button_clicked(GtkWidget *wid,gpointer data) {
  //  char *tokentest = strdup(finalest);

 //  printf("%s", tokentest);
    gchar *text = gtk_button_get_label (showLyricBtn1);

    open_website_part(lyric2, text);
}

void Lyric2_button_clicked(GtkWidget *wid,gpointer data) {
    //char *tokentest = strdup(finalest);

   // printf("%s", tokentest);
    gchar *text = gtk_button_get_label (showLyricBtn2);
    open_website_part(lyric3, text);
}

static void activate (GtkApplication* app, gpointer user_data) {
    GtkWidget *window;
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "One of the top hits by artist");
    gtk_window_set_default_size (GTK_WINDOW (window), 600, 500);
    
    GtkWidget *showSearch;
    firstnameLabel = gtk_label_new("First name:");
    firstnameEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(firstnameEntry),"First Name");
    //GIcon *icon; 
    //GFile *path;
    //path = g_file_new_for_path("");
    //icon = g_file_icon_new(path);
    //gtk_entry_set_icon_from_gicon(GTK_ENTRY(firstnameEntry),GTK_ENTRY_ICON_PRIMARY,icon);
    
    lastnameLabel = gtk_label_new("Lastname:");
    lastnameEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(lastnameEntry),"Last Name");
    //gtk_entry_set_visibility(GTK_ENTRY(lastnameEntry),FALSE);
    searchBtn = gtk_button_new_with_label("search");

    showLyricBtn = gtk_button_new_with_label("Show Lyric");
    showLyricBtn1 = gtk_button_new_with_label("Show Lyric");
    showLyricBtn2 = gtk_button_new_with_label("Show Lyric");

    showSearch = gtk_label_new("");
    
    g_signal_connect(searchBtn,"clicked",G_CALLBACK(search_button_clicked),showSearch);

    g_signal_connect(showLyricBtn,"clicked",G_CALLBACK(Lyric_button_clicked),showSearch);
    g_signal_connect(showLyricBtn1,"clicked",G_CALLBACK(Lyric1_button_clicked),showSearch);
    g_signal_connect(showLyricBtn2,"clicked",G_CALLBACK(Lyric2_button_clicked),showSearch);


    
    GtkWidget *box; box = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);
    gtk_box_pack_start(GTK_BOX(box),firstnameLabel,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),firstnameEntry,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),lastnameLabel,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),lastnameEntry,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),searchBtn,FALSE,FALSE,0);


    gtk_box_pack_start(GTK_BOX(box),showSearch,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),showLyricBtn,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),showLyricBtn1,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),showLyricBtn2,FALSE,FALSE,0);

    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_widget_show_all (window);
    gtk_widget_hide(showLyricBtn);
    gtk_widget_hide(showLyricBtn1);
    gtk_widget_hide(showLyricBtn2);

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
    app = gtk_application_new ("xyz.null0verflow", G_APPLICATION_FLAGS_NONE);
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


/*############################################################################
  ############################################################################
  ############################################################################
  ####################           STRUCTURE CODE           ####################
  ####################        LINKED LIST FUNCTIONS       ####################
  ####################           STRUCTURE CODE           ####################
  ############################################################################
  ############################################################################
  ############################################################################
*/





// ALL TRAVERSE
void AllTraverse(struct All** head, struct All* temp)
{
    int count = 0;
    /*
     * If the list is empty i.e. head = NULL
     */
    if (head == NULL)
    {
        printf("List is empty.");
    }
    else
    {
        temp = (*head);
        printf("%p", temp);
        while (temp != NULL)
        {
            if(count <= 2)
            {
                printf("\n\n########################################\n");
                printf("Pointer Address: %p\n", temp);
                printf("Artist Name: %s\n", temp->ArtistName);
                printf("Song Title: %s\n", temp->Song);
                printf("Lyric URL: %s\n", temp->LyricURL);
                printf("########################################\n\n");// Print data of current node
                if(count == 0){
                    song1 = temp->Song;
                    lyric1 = temp->LyricURL;
                }
                if(count == 1){
                    song2 = temp->Song;
                    lyric2 = temp->LyricURL;
                }
                if(count == 2){
                    song3 = temp->Song;
                    lyric3 = temp->LyricURL;
                }
            }
            temp = temp->next;
            count+=1;
        }
    }
}

//Basic node creation for ALL structure
void CreateListNodeAll(struct All** head, struct All** temp, char song[], char artist[], char lyric[])
{
    *temp = malloc(sizeof(struct All));
    strcpy((*temp)->ArtistName, artist);
    strcpy((*temp)->Song, song);
    strcpy((*temp)->LyricURL, lyric);
    (*temp)->next = NULL;
    *head = (*temp);
    *temp = NULL;
}

//Basic insert end node creation for ALL structure
void InsertEndAll(struct All** head, struct All** temp, char song[], char artist[], char lyric[])
{
    printf("Inside insert end all function");
    struct All* end;
    *temp = malloc(sizeof(struct All));
    strcpy((*temp)->ArtistName, artist);
    strcpy((*temp)->Song, song);
    strcpy((*temp)->LyricURL, lyric);
    (*temp)->next = NULL;
    end = *head;
    while (end->next != NULL)
    {
        end = end->next;
    }
    end->next = (*temp);
    (*temp) = NULL;

}

//Function to free memory for songs structure
void deleteAllSongNodes(struct SongStruct** head)
{
    if(*head == NULL)
    {
        printf("List Is Empty...");
    }
    else
    {
        struct SongStruct* temp = *head;
        while(*head == NULL)
        {
            temp = head;
            head = (*head)->next;

            free(temp);
        }
    }
}

//Function to free memory for Artists structure
void deleteAllArtistNodes(struct ArtistStruct** head)
{
    if(*head == NULL)
    {
        printf("List Is Empty...");
    }
    else
    {
        struct ArtistStruct* temp = *head;
        while(*head == NULL)
        {
            temp = head;
            head = (*head)->next;

            free(temp);
        }
    }
}

//Function to free memory for Lyrics structure
void deleteAllLyricNodes(struct LyricStruct** head)
{
    if(*head == NULL)
    {
        printf("List Is Empty...");
    }
    else
    {
        struct LyricStruct* temp = *head;
        while(*head == NULL)
        {
            temp = head;
            head = (*head)->next;

            free(temp);
        }
    }
}

//Function to delete the fake links to keep the list nice and accurate.
void deleteEnd(struct LyricStruct** head){
    struct LyricStruct* temp = *head;
    struct LyricStruct* previous;
    if(*head == NULL){
        printf("Linked List Empty, nothing to delete");
        return;
    }
    
    if(temp->next == NULL){
        *head = NULL;
        return;
    }
    
    while (temp->next != NULL) 
    {
        previous = temp; 
        temp = temp->next; 
    }
    previous->next = NULL;
    free(temp);
}

//Basic node creation for Song structure
void CreateListNodeSong(struct SongStruct** head, struct SongStruct** temp, char song[])
{
    *temp = malloc(sizeof(struct SongStruct));
    strcpy((*temp)->Song, song);
    (*temp)->next = NULL;
    *head = (*temp);
    *temp = NULL;
}

//Basic insert end node creation for Song structure
void InsertEndSong(struct SongStruct** head, struct SongStruct** temp, char song[])
{
    struct SongStruct* end;
    *temp = malloc(sizeof(struct SongStruct));
    strcpy((*temp)->Song, song);
    (*temp)->next = NULL;
    end = *head;
    while (end->next != NULL)
    {
        end = end->next;
    }
    end->next = (*temp);
    (*temp) = NULL;
}


//Basic node creation for Lyric structure
void CreateListNodeLyric(struct LyricStruct** head, struct LyricStruct** temp, char lyric[])
{
    *temp = malloc(sizeof(struct LyricStruct));
    strcpy((*temp)->LyricURL, lyric);
    (*temp)->next = NULL;
    *head = (*temp);
    *temp = NULL;
}

//Basic insert end node creation for Insert structure
void InsertEndLyric(struct LyricStruct** head, struct LyricStruct** temp, char lyric[])
{
    struct LyricStruct* end;
    *temp = malloc(sizeof(struct LyricStruct));
    strcpy((*temp)->LyricURL, lyric);
    (*temp)->next = NULL;
    end = *head;
    while (end->next != NULL)
    {
        end = end->next;
    }
    end->next = (*temp);
    (*temp) = NULL;
}

//Basic node creation for Artist structure
void CreateListNodeArtist(struct ArtistStruct** head, struct ArtistStruct** temp, char artist[])
{
    *temp = malloc(sizeof(struct ArtistStruct));
    strcpy((*temp)->ArtistName, artist);
    (*temp)->next = NULL;
    *head = (*temp);
    *temp = NULL;
}

//Basic insert end node creation for Artist structure
void InsertEndArtist(struct ArtistStruct** head, struct ArtistStruct** temp, char artist[])
{
    struct ArtistStruct* end;
    *temp = malloc(sizeof(struct ArtistStruct));
    strcpy((*temp)->ArtistName, artist);
    (*temp)->next = NULL;
    end = *head;
    while (end->next != NULL)
    {
        end = end->next;
    }
    end->next = (*temp);
    (*temp) = NULL;
}
 
// SONG TRAVERSE
void SongTraverse(struct SongStruct** head, struct SongStruct* temp)
{
    int count = 0;
    if (head == NULL)
    {
        printf("List is empty.");
    }
    else
    {
        temp = head;
        while (temp != NULL)
        {
            if (count == 0)
            {
                temp = temp->next;
            }
            else
            {
                printf("\n\n########################################\n");
                printf("Pointer Address: %p\n", temp);
                printf("Song Title: %s\n", temp->Song);
                printf("########################################\n\n");
            }
            count += 1;

        }
    }
    printf("\n TOTAL SONG : %d", count);
}

//ARTIST TRAVERSE
void ArtistTraverse(struct ArtistStruct** head, struct ArtistStruct* temp)
{
    int count = 0;
    if (head == NULL)
    {
        printf("List is empty.");
    }
    else
    {
        temp = head;
        while (temp != NULL)
        {
            if (count == 0)
            {
                temp = temp->next;
            }
            else
            {
                printf("\n\n########################################\n");
                printf("Pointer Address: %p\n", temp);
                printf("Artist Title: %s\n", temp->ArtistName);
                printf("########################################\n\n");
                temp = temp->next;                 
            }
            count += 1;

        }
    }
    printf("\n TOTAL Artist : %d", count);
}

//Lyric Traverse
void LyricTraverse(struct LyricStruct** head, struct LyricStruct* temp)
{
    /*
     * If the list is empty i.e. head = NULL
     */
    int count = 0;
    if (head == NULL)
    {
        printf("List is empty.");
    }
    else
    {
        temp = head;
        while (temp != NULL)
        {
            if (count == 0)
            {
                temp = temp->next;
            }
            else
            {
                printf("\n\n########################################\n");
                printf("Pointer Address: %p\n", temp);
                printf("Lyiric URL: %s\n", temp->LyricURL);
                printf("########################################\n\n");
                temp = temp->next;                 
            }
            count += 1;

        }
    }
    printf("\n TOTAL Lyric : %d", count);
}



/*############################################################################
  ############################################################################
  ############################################################################
  ####################                 END                ####################
  ############################################################################
  ############################################################################
  ############################################################################
*/

//This is the combineNodes function to combine the 3 different structures into 1
void combineNodes(struct SongStruct** SongHead, struct LyricStruct** LyricHead, struct ArtistStruct** ArtistHead, struct All** AllHead, struct All** temp)
{
    // Defining temp variables for the head of each list...
    struct SongStruct* SongTemp = (*SongHead);
    struct LyricStruct* LyricTemp = (*LyricHead);
    struct ArtistStruct* ArtistTemp = (*ArtistHead);

    //Calling for ListNode for the ALL structure with the varibles of other structures
    CreateListNodeAll(&AllHead, &temp, SongTemp->Song, ArtistTemp->ArtistName, LyricTemp->LyricURL);

    //Itterating through the lists by setting the temporary values to the next value of themselves.
    SongTemp = SongTemp->next;
    LyricTemp = LyricTemp->next;
    ArtistTemp = ArtistTemp->next;

    //Looping through all of the lists until the last linked value.
    while(ArtistTemp->next != NULL)
    {
        //Through itterating adding a node to the end of the list
        InsertEndAll(&AllHead, &temp, SongTemp->Song, ArtistTemp->ArtistName, LyricTemp->LyricURL);

        //Itterating through the lists by setting the temporary values to the next value of themselves.
        SongTemp = SongTemp->next;
        LyricTemp = LyricTemp->next;
        ArtistTemp = ArtistTemp->next;
    }

    //Function traverses through the list to print out the details for debugging.
    AllTraverse(&AllHead, &temp);
}

void GrabSong()
{
    //Defining all the local variables, had issues combining them and making it look pretty so I'm gonna go with functionality over cleanliness...
    struct SongStruct* SongHead = NULL;
    struct SongStruct* SongTemp = NULL;
    struct ArtistStruct* ArtistHead = NULL;
    struct ArtistStruct* ArtistTemp = NULL;
    struct LyricStruct* LyricHead = NULL;
    struct LyricStruct* LyricTemp = NULL;
    bool fakeLink = false;
    //Duplicating the HTTPS request to character pointer
    char *mem = strdup(chunk.memory);

    //The values we are looking to isolate.
    char SongTitle[] = "full_title";
    char ArtistTitle[] = "artist_names";
    char LyricTitle[] = "url";
    char FakeLyric[] = "name";

    //Count for parsing the desired values
    int SongCount = 0;
    int ArtistCount = 0;
    int LyricCount = 0;
    int SongTrack = 0;
    int ArtistTrack = 0;
    int LyricTrack = 0;

    //Breaking value
    char brake[] = "\"";

    //HTTPs request memory split by breaking vlaue
    char* between = strtok(mem, brake);

    //Looping until the HTTPs request response has been parsed through
    while(between != NULL)
    {   
        /*

            Song Parsing

        */

        //If "full_title" is found, this executes.
        if(SongCount == 1)
        {   
            //Song is the parsed value by break
            char* song = strtok(NULL, brake);

            //Prints Song Title For Logs
            printf("\nSONG IS: %s\n", song);

            //Looks to see if this is the first itteration, seeing is songTrack has been added. If not it creates the first list node, if so it returns false.
            if(SongTrack == 0)
            {
                CreateListNodeSong(&SongHead, &SongTemp, song);
            }

            //If songTrack has been hit a list node has been created so it moves to this if statment, otherwise it won't execute.
            if(SongTrack > 0)
            {
                InsertEndSong(&SongHead, &SongTemp, song);
            }

            // Adding values each time this if statement is hit.
            SongTrack+=1;
            SongCount = 0;
        }
        //String comparison to find "full_title", then start song count to count to the song name
        if(strcmp(between, SongTitle) == 0)
        {
            SongCount+=1;
        }
        /*

            Artist Parsing

        */

        //If "artist_names" is found, this executes.
        if(ArtistCount == 1)
        {
            //Artist is the parsed value by break
            char* artist = strtok(NULL, brake);

            //Prints Artist Name For Logs
            printf("\nARTIST IS: %s\n", artist);

            //Looks to see if this is the first itteration, seeing is ArtistTrack has been added. If not it creates the first list node, if so it returns false.
            if(ArtistTrack == 0)
            {
                CreateListNodeSong(&ArtistHead, &ArtistTemp, artist);
            }

            //If ArtistTrack has been hit a list node has been created so it moves to this if statment, otherwise it won't execute.
            if(ArtistTrack > 0)
            {
                InsertEndSong(&ArtistHead, &ArtistTemp, artist);
            }

            // Adding values each time this if statement is hit.
            ArtistTrack+=1;
            ArtistCount = 0;
        }

        //String comparison to find "artist_names", then start artist count to count to the artist name
        if(strcmp(between, ArtistTitle) == 0)
        {
            ArtistCount+=1;
            printf("\nArtist is here, count is %d\n", ArtistCount);
        }
        /*

            Lyric Parsing

        */
        //If "url" is found, this executes.
        if(LyricCount == 1)
        {

            //Lyric URL is the parsed value by break
            char* lyric = strtok(NULL, brake);

            //Prints Song Title For Logs
            printf("\nLyric URL IS: %s\n", lyric);

            //Checks for the boolean of a NON-LYRIC URL
            if(!fakeLink)
            {
                //Looks to see if this is the first itteration, seeing is LyricTrack has been added. If not it creates the first list node, if so it returns false.
               if(LyricTrack == 0)
                {
                    CreateListNodeLyric(&LyricHead, &LyricTemp, lyric);
                }

                //If LyricTrack has been hit a list node has been created so it moves to this if statment, otherwise it won't execute.
                if(LyricTrack > 0)
                {
                    InsertEndLyric(&LyricHead, &LyricTemp, lyric);
                }
                LyricTrack+=1;
            }
            //Sets fakeLink to false so it won't keep hitting falsely
            fakeLink = false;
            // Adding values each time this if statement is hit.
            LyricCount = 0;
        }

        //String comparison to find "URL", then start lyric count to count to the lyric name
        if(strcmp(between, LyricTitle) == 0)
        {
            LyricCount+=1;
            printf("\nArtist is here, count is %d\n", LyricCount);
        }

        // For the love of god trying to get rid of non lyric urls but this is so insanely tedious UGHH
        //Trying for URL that doesn't have IQ after it... :/
        //Alright this took a fat minute but once we fine "name", we know it's not a lyric url so we activate the boolean and turn it to false.
        if(strcmp(between, FakeLyric) == 0)
        {
            fakeLink = true;
        }

        //going through the itterations
        between = strtok(NULL, brake);
    }

    //Calling Traverse functions to see the values real-time
    /*SongTraverse(&SongHead, &SongTemp);
    ArtistTraverse(&ArtistHead, &ArtistTemp);
    LyricTraverse(&LyricHead, &LyricTemp);
    */

    //This is the combineNodes function to combine the 3 different structures into 1
    //My method is inefficient, but I'm not sure how else I could've gotten the lists recorded when they aren't all found ont he same itteration.
    combineNodes(&SongHead, &LyricHead, &ArtistHead, &AllHead, &AllTemp);
}

void httpsGet(char token[], char url[]) {
    printf("passes this bad boy");
    int count = 0;
    CURL* curl = NULL;
    CURLcode res;
    chunk.memory = malloc(1);
    chunk.size = 0;
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
    GrabSong();
  //  printf("%s", chunk.memory);
   // parseJson();
    //free(chunk.memory);
    
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

/*

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
}*/

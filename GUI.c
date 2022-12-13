 #define _GNU_SOURCE
#include <gtk/gtk.h>
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>


struct MemoryStruct {
    char *memory;
    size_t size;
} chunk;

/* Made All char Allocations in these structs 500. Not sure why, but it fixes a memory allocation issue in the CreateListNodeAll function later 
when the user searches only for specific artists. Elvis Presley, Frank Sinatra, Justin Bieber, and Geto Boys were among a few. */
struct SongStruct
{
    struct SongStruct* next;
    char Song[500];

};

struct ArtistStruct
{
    struct ArtistStruct* next;
    char ArtistName[500];

};

struct LyricStruct
{
    struct LyricStruct* next;
    char LyricURL[500];
};

struct All
{
    struct All* next;
    char ArtistName[500];
    char Song[500];
    char LyricURL[500];

} *temp2;


struct thread_params {
    char *string;
};

/* Variable Declarations */
struct All* AllHead = NULL;
struct All* AllTemp = NULL;
struct thread_params* paramsHead = NULL;
char *song1;
char *song2;
char *song3;
char *song4;
char *song5;
char *lyric1;
char *lyric2;
char *lyric3;
char *lyric4;
char *lyric5;
GThread *thread;
GMutex mutex;
gboolean stop_thread = FALSE;
bool song1Bool = false;
bool song2Bool = false;
bool song3Bool = false;
bool song4Bool = false;
bool song5Bool = false;
GtkWidget *window;
GtkWidget *firstnameLabel, *firstnameEntry, *lastnameLabel, *lastnameEntry, *searchBtn, *grid, *showLyricBtn, *showLyricBtn1, *showLyricBtn2, *showLyricBtn3, *showLyricBtn4, *playSongBtn, *playSongBtn1, *playSongBtn2, *playSongBtn3, *playSongBtn4;

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

gpointer open_website_part(gpointer data) 
{
    g_mutex_lock(&mutex);
    if(stop_thread)
    {
        g_mutex_unlock(&mutex);
        g_thread_exit(NULL);
    }
    g_mutex_unlock(&mutex);
    char *filename = "lyricart.py";
            char *cmd;

    if (file_exists(filename)){
            if(song1Bool)
            {
                asprintf(&cmd, "python3 lyricart.py \"%s\"", song1);
                system(cmd);
                bool song1Bool = false;
            }
            if(song2Bool)
            {
                asprintf(&cmd, "python3 lyricart.py \"%s\"", song2);
                system(cmd);
                bool song2Bool = false;
            }
            if(song3Bool)
            {
                asprintf(&cmd, "python3 lyricart.py \"%s\"", song3);
                system(cmd);
                bool song3Bool = false;
            }
            if(song4Bool)
            {
                asprintf(&cmd, "python3 lyricart.py \"%s\"", song4);
                system(cmd);
                bool song4Bool = false;
            }
            if(song5Bool)
            {
                asprintf(&cmd, "python3 lyricart.py \"%s\"", song5);
                system(cmd);
                bool song5Bool = false;
            }
        }
    else 
    {
        if(song1Bool)
        {
            #ifdef  __linux__
            asprintf(&cmd, "xdg-open %s", lyric1);
            system(cmd);
            #elif __APPLE__
            asprintf(&cmd, "OPEN %s", lyric1);
            system(cmd);
            #elif __WIN32__
            asprintf(&cmd, "START %s", lyric1);
            system(cmd);
            #endif
        }
        if(song2Bool)
        {
            #ifdef  __linux__
            asprintf(&cmd, "xdg-open %s", lyric2);
            system(cmd);
            #elif __APPLE__
            asprintf(&cmd, "OPEN %s", lyric2);
            system(cmd);
            #elif __WIN32__
            asprintf(&cmd, "START %s", lyric2);
            system(cmd);
            #endif
        }
        if(song3Bool)
        {
            #ifdef  __linux__
            asprintf(&cmd, "xdg-open %s", lyric3);
            system(cmd);
            #elif __APPLE__
            asprintf(&cmd, "OPEN %s", lyric3);
            system(cmd);
            #elif __WIN32__
            asprintf(&cmd, "START %s", lyric3);
            system(cmd);
            #endif
        }
        if(song4Bool)
        {
            #ifdef  __linux__
            asprintf(&cmd, "xdg-open %s", lyric4);
            system(cmd);
            #elif __APPLE__
            asprintf(&cmd, "OPEN %s", lyric4);
            system(cmd);
            #elif __WIN32__
            asprintf(&cmd, "START %s", lyric4);
            system(cmd);
            #endif
        }
        if(song5Bool)
        {
            #ifdef  __linux__
            asprintf(&cmd, "xdg-open %s", lyric5);
            system(cmd);
            #elif __APPLE__
            asprintf(&cmd, "OPEN %s", lyric5);
            system(cmd);
            #elif __WIN32__
            asprintf(&cmd, "START %s", lyric5);
            system(cmd);
            #endif
        }
    }
    free(cmd);
    g_mutex_lock(&mutex);
    if(stop_thread)
    {
        g_mutex_unlock(&mutex);
        g_thread_exit(NULL);
    }
    g_mutex_unlock(&mutex);
    return NULL;
}


void search_button_clicked(GtkWidget *wid,gpointer data) {
    struct All* temp;
    const gchar *searchData2, *searchData = NULL;
    searchData = gtk_entry_get_text(GTK_ENTRY(firstnameEntry));
    searchData2 = gtk_entry_get_text(GTK_ENTRY(lastnameEntry));
    gtk_widget_show(showLyricBtn4);
    gtk_widget_show(showLyricBtn3);
    gtk_widget_show(showLyricBtn2);
    gtk_widget_show(showLyricBtn1);
    gtk_widget_show(showLyricBtn);
    gtk_widget_show(playSongBtn);
    gtk_widget_show(playSongBtn1);
    gtk_widget_show(playSongBtn2);
    gtk_widget_show(playSongBtn3);
    gtk_widget_show(playSongBtn4);
    main2(searchData, searchData2);
    
    gtk_label_set_text(GTK_LABEL(data), "Click on each song to see the lyric");
    gtk_button_set_label(GTK_BUTTON(showLyricBtn), song1);
    gtk_button_set_label(GTK_BUTTON(showLyricBtn1), song2);
    gtk_button_set_label(GTK_BUTTON(showLyricBtn2), song3);
    gtk_button_set_label(GTK_BUTTON(showLyricBtn3), song4);
    gtk_button_set_label(GTK_BUTTON(showLyricBtn4), song5);
    gtk_button_set_label(GTK_BUTTON(playSongBtn), "Play");
    gtk_button_set_label(GTK_BUTTON(playSongBtn1), "Play");
    gtk_button_set_label(GTK_BUTTON(playSongBtn2), "Play");
    gtk_button_set_label(GTK_BUTTON(playSongBtn3), "Play");
    gtk_button_set_label(GTK_BUTTON(playSongBtn4), "Play");
    gtk_entry_set_text(GTK_ENTRY(firstnameEntry),"");
    gtk_entry_set_text(GTK_ENTRY(lastnameEntry),"");
    gtk_window_resize(GTK_WINDOW(window), 600, 450);
}



void Lyric_button_clicked(GtkWidget *wid,gpointer data) 
{
    song1Bool =true;
    song2Bool =false;
    song3Bool =false;
    song4Bool =false;
    song5Bool =false;
    thread = g_thread_new("my_thread", open_website_part, NULL);
}
void Lyric1_button_clicked(GtkWidget *wid,gpointer data) 
{
    song1Bool =false;
    song2Bool =true;
    song3Bool =false;
    song4Bool =false;
    song5Bool =false;
    thread = g_thread_new("my_thread", open_website_part, NULL);
}

void Lyric2_button_clicked(GtkWidget *wid,gpointer data) 
{
    song1Bool =false;
    song2Bool =false;
    song3Bool =true;
    song4Bool =false;
    song5Bool =false;
    thread = g_thread_new("my_thread", open_website_part, NULL);
}
void Lyric3_button_clicked(GtkWidget *wid,gpointer data) 
{
    song1Bool =false;
    song2Bool =false;
    song3Bool =false;
    song4Bool =true;
    song5Bool =false;
    thread = g_thread_new("my_thread", open_website_part, NULL);
}

void Lyric4_button_clicked(GtkWidget *wid,gpointer data) 
{
    song1Bool =false;
    song2Bool =false;
    song3Bool =false;
    song4Bool =false;
    song5Bool =true;
    thread = g_thread_new("my_thread", open_website_part, NULL);
}
gpointer playSong(gpointer data)
{
    g_mutex_lock(&mutex);
    if(stop_thread)
    {
        g_mutex_unlock(&mutex);
        g_thread_exit(NULL);
    }
    g_mutex_unlock(&mutex);

    char *filename = "pySong.py";
    char *cmd;
    if(song1Bool)
    {
        if (file_exists(filename))
        {
            asprintf(&cmd, "python3 pySong.py \"%s\"", song1);
            system(cmd);
            song1Bool = false;
        }
    }
    if(song2Bool)
    {
        if (file_exists(filename))
        {
            asprintf(&cmd, "python3 pySong.py \"%s\"", song2);
            system(cmd);
            song2Bool = false;
        }
    }
    if(song3Bool)
    {
        if (file_exists(filename))
        {
            asprintf(&cmd, "python3 pySong.py \"%s\"", song3);
            system(cmd);
            song3Bool = false;
        }
    }
    if(song4Bool)
    {
        if (file_exists(filename))
        {
            asprintf(&cmd, "python3 pySong.py \"%s\"", song4);
            system(cmd);
            song4Bool = false;
        }
    }
    if(song5Bool)
    {
        if (file_exists(filename))
        {
            asprintf(&cmd, "python3 pySong.py \"%s\"", song5);
            system(cmd);
            song5Bool = false;
        }
    }
    g_mutex_lock(&mutex);
    if(stop_thread)
    {
        g_mutex_unlock(&mutex);
        g_thread_exit(NULL);
    }
    g_mutex_unlock(&mutex);
    return NULL;
}

void play_button_clicked(GtkWidget *wid,gpointer data) {
    g_mutex_lock(&mutex);
    stop_thread = TRUE;
    g_mutex_unlock(&mutex);
    char *cmd;
    asprintf(&cmd, "pkill -9 -f pySong.py");
    system(cmd);
    stop_thread = FALSE;
    song1Bool =true;
    thread = g_thread_new("my_thread", playSong, NULL);
}

void play1_button_clicked(GtkWidget *wid,gpointer data) {
    g_mutex_lock(&mutex);
    stop_thread = TRUE;
    g_mutex_unlock(&mutex);
    char *cmd;
    asprintf(&cmd, "pkill -9 -f pySong.py");
    system(cmd);
    stop_thread = FALSE;
    song2Bool =true;
    thread = g_thread_new("my_thread", playSong, NULL);
}

void play2_button_clicked(GtkWidget *wid,gpointer data) {
    g_mutex_lock(&mutex);
    stop_thread = TRUE;
    g_mutex_unlock(&mutex);
    char *cmd;
    asprintf(&cmd, "pkill -9 -f pySong.py");
    system(cmd);
    stop_thread = FALSE;
    song3Bool =true;
    thread = g_thread_new("my_thread", playSong, NULL);
}
void play3_button_clicked(GtkWidget *wid,gpointer data) {
    g_mutex_lock(&mutex);
    stop_thread = TRUE;
    g_mutex_unlock(&mutex);
    char *cmd;
    asprintf(&cmd, "pkill -9 -f pySong.py");
    system(cmd);
    stop_thread = FALSE;
    song4Bool =true;
    thread = g_thread_new("my_thread", playSong, NULL);
}
void play4_button_clicked(GtkWidget *wid,gpointer data) {
    g_mutex_lock(&mutex);
    stop_thread = TRUE;
    g_mutex_unlock(&mutex);
    char *cmd;
    asprintf(&cmd, "pkill -9 -f pySong.py");
    system(cmd);
    stop_thread = FALSE;
    song5Bool =true;
    thread = g_thread_new("my_thread", playSong, NULL);
}

void on_window_closed(GtkWidget *widget, gpointer data)
{
    g_mutex_lock(&mutex);
    stop_thread = TRUE;
    g_mutex_unlock(&mutex);
    char *cmd;
    asprintf(&cmd, "pkill -9 -f pySong.py");
    asprintf(&cmd, "pkill -9 -f lyricart.py");
    system(cmd);
}

static void activate (GtkApplication* app, gpointer user_data) {
    GtkWidget *fixed;
    fixed = gtk_fixed_new();

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "One of the top hits by artist");
    gtk_window_set_default_size (GTK_WINDOW(window), 50, 100);

    GtkWidget *showSearch;
    firstnameLabel = gtk_label_new("First Name:");
    firstnameEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(firstnameEntry),"First Name");
    
    lastnameLabel = gtk_label_new("Last Name:");
    lastnameEntry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(lastnameEntry),"Last Name");
    searchBtn = gtk_button_new_with_label("search");

    showLyricBtn = gtk_button_new_with_label("Show Lyric");
    showLyricBtn1 = gtk_button_new_with_label("Show Lyric");
    showLyricBtn2 = gtk_button_new_with_label("Show Lyric");
    showLyricBtn3 = gtk_button_new_with_label("Show Lyric");
    showLyricBtn4 = gtk_button_new_with_label("Show Lyric");
    playSongBtn = gtk_button_new_with_label("Play");
    playSongBtn1 = gtk_button_new_with_label("Play");
    playSongBtn2 = gtk_button_new_with_label("Play");
    playSongBtn3 = gtk_button_new_with_label("Play");
    playSongBtn4 = gtk_button_new_with_label("Play");

    showSearch = gtk_label_new("");
    
    g_signal_connect(searchBtn,"clicked",G_CALLBACK(search_button_clicked),showSearch);
    g_signal_connect(showLyricBtn,"clicked",G_CALLBACK(Lyric_button_clicked),showSearch);
    g_signal_connect(showLyricBtn1,"clicked",G_CALLBACK(Lyric1_button_clicked),showSearch);
    g_signal_connect(showLyricBtn2,"clicked",G_CALLBACK(Lyric2_button_clicked),showSearch);
    g_signal_connect(showLyricBtn3,"clicked",G_CALLBACK(Lyric3_button_clicked),showSearch);
    g_signal_connect(showLyricBtn4,"clicked",G_CALLBACK(Lyric4_button_clicked),showSearch);
    g_signal_connect(playSongBtn,"clicked",G_CALLBACK(play_button_clicked),showSearch);
    g_signal_connect(playSongBtn1,"clicked",G_CALLBACK(play1_button_clicked),showSearch);
    g_signal_connect(playSongBtn2,"clicked",G_CALLBACK(play2_button_clicked),showSearch);
    g_signal_connect(playSongBtn3,"clicked",G_CALLBACK(play3_button_clicked),showSearch);
    g_signal_connect(playSongBtn4,"clicked",G_CALLBACK(play4_button_clicked),showSearch);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_window_closed), NULL);
    
    GtkWidget *box;
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);
    gtk_fixed_put(GTK_FIXED(fixed),firstnameLabel,20,20);
    gtk_fixed_put(GTK_FIXED(fixed),firstnameEntry,100,10);
    gtk_fixed_put(GTK_FIXED(fixed),lastnameLabel,20,60);
    gtk_fixed_put(GTK_FIXED(fixed),lastnameEntry,100,50);
    gtk_fixed_put(GTK_FIXED(fixed),searchBtn,190,100);

    gtk_fixed_put(GTK_FIXED(fixed),showSearch,200,150);

    gtk_fixed_put(GTK_FIXED(fixed),showLyricBtn,10,200);
    gtk_fixed_put(GTK_FIXED(fixed),showLyricBtn1,10,250);
    gtk_fixed_put(GTK_FIXED(fixed),showLyricBtn2,10,300);
    gtk_fixed_put(GTK_FIXED(fixed),showLyricBtn3,10,350);
    gtk_fixed_put(GTK_FIXED(fixed),showLyricBtn4,10,400);
    gtk_fixed_put(GTK_FIXED(fixed),playSongBtn,500,200);
    gtk_fixed_put(GTK_FIXED(fixed),playSongBtn1,500,250);
    gtk_fixed_put(GTK_FIXED(fixed),playSongBtn2,500,300);
    gtk_fixed_put(GTK_FIXED(fixed),playSongBtn3,500,350);
    gtk_fixed_put(GTK_FIXED(fixed),playSongBtn4,500,400);
    gtk_widget_set_size_request(playSongBtn, 80, 30);
    gtk_widget_set_size_request(playSongBtn1, 80, 30);
    gtk_widget_set_size_request(playSongBtn2,80, 30);
    gtk_widget_set_size_request(playSongBtn3, 80, 30);
    gtk_widget_set_size_request(playSongBtn4, 80, 30);

    gtk_container_add(GTK_CONTAINER(window), fixed);

    gtk_widget_show_all (window);
    gtk_widget_hide(showLyricBtn);
    gtk_widget_hide(showLyricBtn1);
    gtk_widget_hide(showLyricBtn2);
    gtk_widget_hide(showLyricBtn3);
    gtk_widget_hide(showLyricBtn4);
    gtk_widget_hide(playSongBtn);
    gtk_widget_hide(playSongBtn1);
    gtk_widget_hide(playSongBtn2);
    gtk_widget_hide(playSongBtn3);
    gtk_widget_hide(playSongBtn4);


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

bool silent = false;
int main(int argc,char *argv[]) {
    if(argc == 1)
    {
        GtkApplication *app;
        int status;        
        app = gtk_application_new ("xyz.null0verflow", G_APPLICATION_DEFAULT_FLAGS);
        g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
        status = g_application_run(G_APPLICATION(app), argc, argv);
        return status;
    }
    if(argc == 2)
    {
        silent = true;
        char args[] = "silent";
        if(!strcmp(argv[1], args))
        {   
            char *name;
            name = (char *)malloc(100 * sizeof(char));
            char *first;
            char *last;
            printf("\nHello and welcome to the C music player!\nPlease input artist name!\n");
            scanf("%[^\n]", name);
            int count = 0;
            char* temp = strtok(name, " ");
            while(temp != NULL)
            {
                if(count == 0)
                {
                    first = temp;
                }
                else
                {
                    last = temp;
                }
                temp = strtok(NULL, " ");
                count+=1;
            }
            if(main2(first, last) == 0)
            {
                bool menu = true;
                int choice1 = '0';
                int choice2 = 0;
                char* songChoice;
                while(menu)
                {
                    printf("Your songs have been gathered!\n");
                    printf("1. Show Lyrics\n");
                    printf("2. Play Song\n");
                    printf("Please insert the function value you'd like to execute: ");
                    scanf(" %d", &choice1);
                    if(choice1 == 1)
                    {
                        bool menu2 = true;
                        while(menu2)
                        {
                            printf("\nHere are your songs:\n1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n", song1, song2, song3, song4, song5);
                            scanf("%d", &choice2);
                            if(choice2 == 1)
                            {   
                                menu2 = false;
                                songChoice = song1;
                                song1Bool = true;
                                open_website_part(NULL);
                                break;
                            }
                            if(choice2 == 2)
                            {
                                menu2 = false;
                                songChoice = song2;
                                song2Bool = true;
                                open_website_part(NULL);
                                break;
                            }
                            if(choice2 == 3)
                            {
                                menu2 = false;
                                songChoice = song3;
                                song3Bool = true;
                                open_website_part(NULL);
                                break;
                            }
                            if(choice2 == 4)
                            {
                                menu2 = false;
                                songChoice = song3;
                                song4Bool = true;
                                open_website_part(NULL);
                                break;
                            }
                            if(choice2 == 5)
                            {
                                menu2 = false;
                                songChoice = song3;
                                song5Bool = true;
                                open_website_part(NULL);
                                break;
                            }
                            else
                            {
                                printf("\nPlease insert a valid integer!\n");
                            }
                        }
                        menu = false;
                        break;
                    }
                    if(choice1 == 2)
                    {
                        bool menu2 = true;
                        while(menu2)
                        {
                            printf("\nHere are your songs:\n1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n", song1, song2, song3, song4, song5);
                            scanf("%d", &choice2);
                            if(choice2 == 1)
                            {   
                                menu2 = false;
                                songChoice = song1;
                                song1Bool = true;
                                playSong(NULL);
                                break;
                            }
                            if(choice2 == 2)
                            {
                                menu2 = false;
                                songChoice = song2;
                                song2Bool = true;
                                playSong(NULL);
                                break;
                            }
                            if(choice2 == 3)
                            {
                                menu2 = false;
                                songChoice = song3;
                                song3Bool = true;
                                playSong(NULL);
                                break;
                            }
                            if(choice2 == 4)
                            {
                                menu2 = false;
                                songChoice = song4;
                                song4Bool = true;
                                playSong(NULL);
                                break;
                            }
                            if(choice2 == 5)
                            {
                                menu2 = false;
                                songChoice = song5;
                                song5Bool = true;
                                playSong(NULL);
                                break;
                            }
                            else
                            {
                                printf("\nPlease insert a valid integer!\n");
                            }
                        }
                        menu = false;
                        break;
                    }
                    else
                    {
                        printf("\nPlease insert a valid integer!\n");
                    }
                }
            }

        }
        else
        {
            printf("Uh oh! Looks like an invalid arguement has been entered!");
        }
    }
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
void AllTraverse(struct All** head, struct All** temp)
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
        *temp = (*head);
        while (*temp != NULL)
        {
            if(!silent)
            {
                if(count <= 4)
                {
                    printf("\n\n########################################\n");
                    printf("Pointer Address: %p\n", *temp);
                    printf("Artist Name: %s\n", (*temp)->ArtistName);
                    printf("Song Title: %s\n", (*temp)->Song);
                    printf("Lyric URL: %s\n", (*temp)->LyricURL);
                    printf("########################################\n\n");// Print data of current node
                    if(count == 0){
                        song1 = (*temp)->Song;
                        lyric1 = (*temp)->LyricURL;
                    }
                    if(count == 1){
                        song2 = (*temp)->Song;
                        lyric2 = (*temp)->LyricURL;
                    }
                    if(count == 2){
                        song3 = (*temp)->Song;
                        lyric3 = (*temp)->LyricURL;
                    }
                    if(count == 3)
                    {
                        song4 = (*temp)->Song;
                        lyric4 = (*temp)->LyricURL;
                    }
                    if(count == 4)
                    {
                        song5 = (*temp)->Song;
                        lyric5 = (*temp)->LyricURL;
                    }
                }
            *temp = (*temp)->next;
            count+=1;
            }
            else
            {
                if(count <= 4)
                {
                    if(count == 0){
                        song1 = (*temp)->Song;
                        lyric1 = (*temp)->LyricURL;
                    }
                    if(count == 1){
                        song2 = (*temp)->Song;
                        lyric2 = (*temp)->LyricURL;
                    }
                    if(count == 2){
                        song3 = (*temp)->Song;
                        lyric3 = (*temp)->LyricURL;
                    }
                    if(count == 3){
                        song4 = (*temp)->Song;
                        lyric4 = (*temp)->LyricURL;
                    }
                    if(count == 4){
                        song5 = (*temp)->Song;
                        lyric5 = (*temp)->LyricURL;
                    }
                }
            *temp = (*temp)->next;
            count+=1;
            }
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
            temp = *head;
            *head = (*head)->next;

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
            temp = *head;
            *head = (*head)->next;

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
            temp = *head;
            *head = (*head)->next;

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
    if (*head == NULL)
    {
        printf("List is empty.");
    }
    else
    {
        temp = *head;
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
    if (*head == NULL)
    {
        printf("List is empty.");
    }
    else
    {
        temp = *head;
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
    if (*head == NULL)
    {
        printf("List is empty.");
    }
    else
    {
        temp = *head;
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
    CreateListNodeAll(AllHead, temp, SongTemp->Song, ArtistTemp->ArtistName, LyricTemp->LyricURL);

    //Itterating through the lists by setting the temporary values to the next value of themselves.
    SongTemp = SongTemp->next;
    LyricTemp = LyricTemp->next;
    ArtistTemp = ArtistTemp->next;

    //Looping through all of the lists until the last linked value.
    while(ArtistTemp->next != NULL)
    {
        //Through itterating adding a node to the end of the list
        InsertEndAll(AllHead, temp, SongTemp->Song, ArtistTemp->ArtistName, LyricTemp->LyricURL);

        //Itterating through the lists by setting the temporary values to the next value of themselves.
        SongTemp = SongTemp->next;
        LyricTemp = LyricTemp->next;
        ArtistTemp = ArtistTemp->next;
    }

    //Function traverses through the list to print out the details for debugging.
    AllTraverse(AllHead, temp);
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

            //Looks to see if this is the first itteration, seeing is ArtistTrack has been added. If not it creates the first list node, if so it returns false.
            if(ArtistTrack == 0)
            {
                CreateListNodeArtist(&ArtistHead, &ArtistTemp, artist);
            }

            //If ArtistTrack has been hit a list node has been created so it moves to this if statment, otherwise it won't execute.
            if(ArtistTrack > 0)
            {
                InsertEndArtist(&ArtistHead, &ArtistTemp, artist);
            }

            // Adding values each time this if statement is hit.
            ArtistTrack+=1;
            ArtistCount = 0;
        }

        //String comparison to find "artist_names", then start artist count to count to the artist name
        if(strcmp(between, ArtistTitle) == 0)
        {
            ArtistCount+=1;
        }
        /*

            Lyric Parsing

        */
        //If "url" is found, this executes.
        if(LyricCount == 1)
        {

            //Lyric URL is the parsed value by break
            char* lyric = strtok(NULL, brake);

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
        }

        // For the love of god trying to get rid of non lyric urls but this is so insanely tedious UGHH
        //Trying for URL that doesn't have IQ after it... :/
        //Alright this took a fat minute but once we find "name", we know it's not a lyric url so we activate the boolean and turn it to false.
        if(strcmp(between, FakeLyric) == 0)
        {
            fakeLink = true;
        }

        //going through the itterations
        between = strtok(NULL, brake);
    }

    //This is the combineNodes function to combine the 3 different structures into 1
    //My method is inefficient, but I'm not sure how else I could've gotten the lists recorded when they aren't all found on the same itteration.
    combineNodes(&SongHead, &LyricHead, &ArtistHead, &AllHead, &AllTemp);
}

void httpsGet(char token[], char url[]) {
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
    
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

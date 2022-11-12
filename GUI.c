#include <gtk/gtk.h>
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

/* Variable Declarations */
int testCode();
char *token2;
GtkWidget *firstnameLabel, *firstnameEntry, *lastnameLabel, *lastnameEntry, *searchBtn, *grid;
struct MemoryStruct chunk;

/* Function Prototypes */
int main2(const gchar *, const gchar *);
void parseJson();
char* httpsGet(char token[], char url[]);

struct MemoryStruct {
	char *memory;
	size_t size;
};

void search_button_clicked(GtkWidget *wid,gpointer data) {
	const gchar *searchData = gtk_entry_get_text(GTK_ENTRY(firstnameEntry));
	const gchar *searchData2 = gtk_entry_get_text(GTK_ENTRY(lastnameEntry));
	
	main2(searchData, searchData2);
	
	gtk_label_set_text(GTK_LABEL(data), token2);
	gtk_entry_set_text(GTK_ENTRY(firstnameEntry),"");
	gtk_entry_set_text(GTK_ENTRY(lastnameEntry),"");
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
	showSearch = gtk_label_new("");
	
	g_signal_connect(searchBtn,"clicked",G_CALLBACK(search_button_clicked),showSearch);
	
	GtkWidget *box; box = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);
	gtk_box_pack_start(GTK_BOX(box),firstnameLabel,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),firstnameEntry,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),lastnameLabel,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),lastnameEntry,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),searchBtn,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),showSearch,FALSE,FALSE,0);
	
	gtk_container_add(GTK_CONTAINER(window),box);
	gtk_widget_show_all (window);
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
 	char url[60];
 	char name[60];
 	char genius[] = "https://api.genius.com/search?q=";
 	strcpy(url, genius);
 	char space[] = "%20";
 	char geniusToken[] = "mXWeiTbMTOxwTP87bXlHJtTKcaam60Njvfb5OsR8XAHflIqFKvGEgGuAkXZ2dtkC";
 	printf("Hello and welcome to the music finder thingy!\nPlease input the name of the artist you would like to view...\n");
 	//scanf("%s %s", firstname, lastname);
 	strcpy(name, firstname);
 	strcat(name, space);
 	strcat(name, lastname);
 	strcat(url, name);
 	httpsGet(geniusToken, url);
 	return 0;
}

char* httpsGet(char token[], char url[]) {
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
	
	printf(chunk.memory);
	parseJson();
	free(chunk.memory);
	
	curl_easy_cleanup(curl);
}

void parseJson() {
	memmove(chunk.memory, chunk.memory+34+55+9, strlen(chunk.memory));
	
	char w[10] = "full";
	int i=0,k=0,c,index;
	
	while(chunk.memory[i]!='\0') {
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
		}
		
		i++;
		k=0;
	}
	
	//printf (index);
	memmove(chunk.memory, chunk.memory+index+13 ,strlen(chunk.memory));
	const char deli[] = "\""; 
	
	token2 = strtok(chunk.memory, deli); 
}

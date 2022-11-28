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
    char ArtistName[50];
    char Song[50];
    char LyricURL[200];

};


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

void GrabSong()
{
    //Defining all the local variables, had issues combining them and making it look pretty so I'm gonna go with functionality over cleanliness...
    struct SongStruct* SongHead = NULL;
    struct SongStruct* SongTemp = NULL;
    struct ArtistStruct* ArtistHead = NULL;
    struct ArtistStruct* ArtistTemp = NULL;
    struct LyricStruct* LyricHead = NULL;
    struct LyricStruct* LyricTemp = NULL;
    struct All* AllHead = NULL;
    struct All* AllTemp = NULL;
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

// ALL TRAVERSE
void AllTraverse(struct All** head, struct All* temp)
{
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
            printf("\n\n########################################\n");
            printf("Pointer Address: %p\n", temp);
            printf("Artist Name: %s\n", temp->ArtistName);
            printf("Song Title: %s\n", temp->Song);
            printf("Lyric URL: %s\n", temp->LyricURL);
            printf("########################################\n\n");// Print data of current node
            temp = temp->next;                 // Move to next node
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

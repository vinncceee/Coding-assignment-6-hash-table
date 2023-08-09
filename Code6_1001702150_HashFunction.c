//Name: Vince Vennedick Banks
//ID: 1001702150
/* Coding Assignment 6 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 30
 
typedef struct playstation_store_games
{
    char *name;
    char ESRB_rating;
    char *genre;
    int year_of_release;
    float current_retail_price;
    struct playstation_store_games *next_ptr;
}
PLAYSTATION_STORE_GAMES;
 
/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char *key)
{
	int HashIndex = 0;
	
	for (int i = 0; i < strlen(key); i++)
	{
		HashIndex += key[i];
	}
	
	return HashIndex %= HASHTABLESIZE; 
}

void AddNode(PLAYSTATION_STORE_GAMES *NewNode, PLAYSTATION_STORE_GAMES *ps4_store_index[])
{
	int HashIndex = CalculateHashIndex(NewNode->name);
	
	/* a linked list does not exist for this cell of the array */
	if (ps4_store_index[HashIndex] == NULL) 
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
		ps4_store_index[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		PLAYSTATION_STORE_GAMES *TempPtr = ps4_store_index[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->next_ptr != NULL) 
		{
			TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(PLAYSTATION_STORE_GAMES *ps4_store_index[])
{
	PLAYSTATION_STORE_GAMES *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = ps4_store_index[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->name);
				NextPtr = TempPtr->next_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}

int DeleteNode(PLAYSTATION_STORE_GAMES *ps4_store_index[])
{
    char LookupName[100] = {};
    int result = 0;

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter the name of the game to delete from the PS4 Store Index: ");
    fgets(LookupName, sizeof(LookupName), stdin);

    if (LookupName[strlen(LookupName) - 1] == '\n')
        LookupName[strlen(LookupName) - 1] = '\0';

    int HashIndex = CalculateHashIndex(LookupName);

    /* Get linked list at key in array */
    PLAYSTATION_STORE_GAMES *TempPtr = ps4_store_index[HashIndex];
    PLAYSTATION_STORE_GAMES *PrevPtr = NULL;

    /* This array index does not have a linked list; therefore, no keys */
    if (TempPtr == NULL) 
    {
        printf("\n\nGame %s does not exist in the PS4 Store Index\n\n", LookupName);
        result = 0;
    }
    else 
    {
        while (TempPtr != NULL) 
        {
            if (strcmp(TempPtr->name, LookupName) == 0)
            {
                /* If the node being deleted is the head node */
                if (TempPtr == ps4_store_index[HashIndex])
                {
                    /* The node the head was pointing at is now the head */
                    ps4_store_index[HashIndex] = TempPtr->next_ptr;
                    printf("\nThe Game %s has been deleted from the PS4 Store Index\n\n", TempPtr->name);
                    free(TempPtr->name);
                    free(TempPtr->genre);
                    free(TempPtr);
                    TempPtr = NULL;
                }
                /* Found node to be deleted - node is not the head */
                else
                {
                    PrevPtr->next_ptr = TempPtr->next_ptr;
                    printf("\nThe Game %s has been deleted from the PS4 Store Index\n\n", TempPtr->name);
                    free(TempPtr->name);
                    free(TempPtr->genre);
                    free(TempPtr);
                    TempPtr = NULL;
                }
                result = 1;
            }
            /* this is not the node that needs to be deleted but save */
            /* its info and move to the next node in the linked list  */
            else
            {
                PrevPtr = TempPtr;
                TempPtr = TempPtr->next_ptr;
            }
        }
        if (result == 0)
        {
            printf("\n\nGame %s does not exist in the PS4 Store Index\n\n", LookupName);
        }
    }
    return result;
}


/* display the contents of the Hash Table */
void DisplayHashTable(PLAYSTATION_STORE_GAMES *ps4_store_index[])
{
	int i;
	PLAYSTATION_STORE_GAMES *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = ps4_store_index[i];

		printf("\nPs4_store_index[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->name);
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByLetter(PLAYSTATION_STORE_GAMES *ps4_store_index[])
{
	int i;
	PLAYSTATION_STORE_GAMES *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = ps4_store_index[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->name);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByName(PLAYSTATION_STORE_GAMES *ps4_store_index[])
{
	PLAYSTATION_STORE_GAMES *TempPtr = NULL;
	char LookupName[100] = {};
	int FoundIt = 0;
	
	printf("\n\nEnter game's name: ");

	while(getchar() != '\n');

	fgets(LookupName, sizeof(LookupName), stdin);
	LookupName[strlen(LookupName)-1] = '\0';

	#if TIMING
	clock_t start, end;
	start = clock();
	#endif

	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = ps4_store_index[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->name, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;
					printf("Game:\t\t%s\n", TempPtr->name);
					printf("ESRB Rating:\t%c\n", TempPtr->ESRB_rating);
					printf("Genre:\t\t%s\n", TempPtr->genre);
					printf("Year of Release:\t%d\n", TempPtr->year_of_release);
					printf("Retail Price:\t%.2f\n", TempPtr->current_retail_price);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nGame %s not found in PlayStation Store Index\n\n", LookupName);
}

void AddNewGame(PLAYSTATION_STORE_GAMES *ps4_store_index[])
{
    int HashIndex = 0;
    PLAYSTATION_STORE_GAMES *NewNode;
    char TempBuffer[100] = {};

    NewNode = malloc(sizeof(PLAYSTATION_STORE_GAMES));
    NewNode->next_ptr = NULL;

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\n\nEnter new game's name ");
    fgets(TempBuffer, sizeof(TempBuffer), stdin); 
    if (TempBuffer[strlen(TempBuffer) - 1] == '\n')
        TempBuffer[strlen(TempBuffer) - 1] = '\0'; 
    NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
    strcpy(NewNode->name, TempBuffer);

    printf("\n\nEnter %s's ESRB Rating (E/M/T/...) ", NewNode->name);
    scanf(" %c", &(NewNode->ESRB_rating));
    NewNode->ESRB_rating = toupper(NewNode->ESRB_rating);
    

    fgets(TempBuffer, sizeof(TempBuffer), stdin);

    printf("\n\nEnter %s's genre ", NewNode->name);
    fgets(TempBuffer, sizeof(TempBuffer), stdin); 
    if (TempBuffer[strlen(TempBuffer) - 1] == '\n')
        TempBuffer[strlen(TempBuffer) - 1] = '\0';
    NewNode->genre = malloc(strlen(TempBuffer)*sizeof(char)+1);
    strcpy(NewNode->genre, TempBuffer);

    printf("\n\nEnter %s's year of release ", NewNode->name);
    scanf("%d", &(NewNode->year_of_release));

    fgets(TempBuffer, sizeof(TempBuffer), stdin);

    printf("\n\nEnter %s's current retail price ", NewNode->name);
    scanf("%f", &(NewNode->current_retail_price));

    AddNode(NewNode, ps4_store_index);  
}

int ReadFileIntoHashTable(int argc, char *argv[], PLAYSTATION_STORE_GAMES *ps4_store_index[])
{
	FILE *FH = NULL;
	char FileLine[256] = {};
	char *token = NULL;
	int counter = 0;
	PLAYSTATION_STORE_GAMES *NewNode;

	if (argc > 1)
	{
		FH = fopen(argv[1], "r");
		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);
		}
		
		while (fgets(FileLine, sizeof(FileLine)-1, FH))
		{
			NewNode = malloc(sizeof(PLAYSTATION_STORE_GAMES));
			if (!NewNode) 
			{
				perror("Memory allocation failed for NewNode");
				exit(0);
			}
			NewNode->next_ptr = NULL;
			
			token = strtok(FileLine, "|");
			NewNode->name = strdup(token);

			token = strtok(NULL, "|");
			NewNode->ESRB_rating = *token;

			token = strtok(NULL, "|");
			NewNode->genre = strdup(token);
		
			token = strtok(NULL, "|");
			NewNode->year_of_release = atoi(token);

			token = strtok(NULL, "|");
			NewNode->current_retail_price = atof(token);

			AddNode(NewNode, ps4_store_index);
			counter++;
		}
		fclose(FH);
	}
	else
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	
	return counter;
}

int main(int argc, char *argv[]) 
{
	int MenuChoice = 0;
	int counter = 0;
	PLAYSTATION_STORE_GAMES *PS4StoreIndex[HASHTABLESIZE] = {};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, PS4StoreIndex);
 
	do
	{
		printf("\n\nPlayStation Store Menu\n\n"
			   "1. Show all games in the store for a given initial letter\n"
			   "2. Look up game by name\n"
			   "3. How many games are in the store?\n"
			   "4. Display the game list\n"
			   "5. Add a new game\n"
			   "6. Delete a game from the store\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
				ShowByLetter(PS4StoreIndex);
				break;
			case SHOWBYNAME:
				ShowByName(PS4StoreIndex);
				break;
			case COUNT:
				printf("Your PlayStation Store contains %d games\n", counter); 
				break;
 			case DISPLAY:
				DisplayHashTable(PS4StoreIndex);
				break;
			case ADD:
				AddNewGame(PS4StoreIndex);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(PS4StoreIndex))
				{
					counter--;
				}
				break;
			case EXIT:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != EXIT);
	
	FreeDynamicMemory(PS4StoreIndex);

	return 0;
}		  

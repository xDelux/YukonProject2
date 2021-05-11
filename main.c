#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <wchar.h>

#include<fcntl.h>
#include<io.h>


#define DECK_SIZE 52
#define FOUNDATION_SIZE 4
#define COLUM_SIZE 7

wchar_t *clubs = L"\u2663";
wchar_t *diamonds = L"\u2666";
wchar_t *hearts = L"\u2665";
wchar_t *spades = L"\u2660";


typedef struct CardNode
{
    char value;
    char type;
    int isHidden;
    struct CardNode *next;
    struct CardNode *prev;
    
} CardNode;

typedef struct Pile
{
    char id[2];
    struct CardNode *head;
    struct CardNode *tail;
    struct Pile *next;
    struct Pile *prev;
    int cardsInPile;
} Pile;

// Print opertaions
void printConsole();
void printSuit(char type);
// Node functions 
//CardNode* makeNode(Card *card);
void createNode();
int removeNode();
void createPile();
void removePile();
void moveTailCard(Pile *fromPile, Pile *toPile);
void moveCardAtIndex(Pile *fromPile, Pile *toPile, int cardIndex);
void moveCardsFromIndex(Pile *fromPile, Pile *toPile, int cardIndex);
void moveHeadCard(Pile *fromPile, Pile *toPile);


void newDeck();
int loadFile(char *filename);
// Command functions
void LD(char input[]);
void SW();
void SI(int split);
void SR();
void SD();
void P();

// Initialization
void initCards();
void initPilesNFoundations();

int game = 0;
char input[10];
char message[256] = "HELLO";
char lastCom[10] = "NONE";

// First pile and foundation
Pile *pileHead = NULL;
Pile *pileTail = NULL;


int main(void)
{
    //setmode(_fileno(stdout), _O_U16TEXT);
    initPilesNFoundations();
    Pile *ref = pileHead->next;
    LD("LD");
    SW();
    printConsole();
    
    
    
    //printConsole();
    /*do
    {       
        printConsole();
        scanf("%s", &input);
        if(strcmp(input, "SW") == 0) {SW();}
        if(strcmp(input, "LD") == 0) {LD(input);}
        //if(strcmp(input, "SR") == 0) {SR();}
        
    } while (strcmp(input, "QQ") != 0); */
}

// Prints the console
void printConsole()
{
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\t\t\n\n");    
    
    // Pointers for the piles, foundations and nodes.
    Pile *F1, *Cx;
    CardNode *temp = NULL;
    F1 = pileHead->next->next->next->next->next->next->next; 
    int done, endOfPile,column, row = 0;
    done = endOfPile = column = 0;
    while(1){
        Cx = pileHead;

        // navigate to column
        for(int i = 0; i < column; i++){Cx = Cx->next;}

        //navigate to row
        if(Cx->head == NULL){ 
            temp = NULL;
            endOfPile++;
        }else{
            temp = Cx->head;
            for(int j = 0; j < row; j++){
                if(temp->next == NULL){
                    endOfPile++;
                    temp = NULL;
                    break;
                }
                temp = temp->next;
            }
        }
       

        //print content of node
        if(temp == NULL){
           printf(".");
        } else {

            if(temp->isHidden == 0){
                printSuit(temp->type);
                printf("%c", temp->value);
            } else{
                printf("[]");
            }

        }

        printf("\t");
       
        column++;
        if(column == 7) {
            if(row == 0 || row == 2 || row == 4 || row == 6){

                if(F1->tail != NULL){
                    printSuit(F1->tail->type);
                    printf("%c", F1->tail->value);
            
                }else{ printf("[]");}
                
                printf("\tF%d", (row/2)+1);

                if(F1->next != NULL) {
                F1 = F1->next;
                }

            }


            if(endOfPile == 7 && row > 6){break;}
            endOfPile = 0; 
            printf("\n");
            row++;
        }
        column = column%7;
        
    }
    
    
    printf("\nLAST Command: %s\n", lastCom);
    printf("Message: %s\n", message);
    printf("INPUT > ");
}

void initPilesNFoundations() {
    
   for(int i = 0; i < 12; i++){
       createPile();
   }
}

void createPile() {
    if(pileHead != NULL){
        struct Pile* temp = malloc(sizeof(struct Pile));
        temp->next = NULL; 
        temp->prev = pileTail; 
        pileTail->next = temp;
        pileTail = temp;

        temp->head=NULL;
        temp->tail= NULL;

        temp->cardsInPile = 0;
    } else { // List is empty
        pileHead = malloc(sizeof(struct Pile));	// Setting up space in the memory for the 1st node.
        pileHead->prev = NULL;
        pileHead->next = NULL;
        
        pileHead->head=NULL;
        pileHead->tail= NULL;

        pileHead->cardsInPile = 0;
        pileTail = pileHead;
    }
}
void removePile() {
    if(pileTail!=NULL){
        struct Pile* temp1;
        if(pileTail->prev != NULL){
            temp1 = pileTail;
            pileTail = pileTail->prev;
            free(temp1);
            pileTail->next = NULL;
        } else {
            //Last node in the list.
            free(pileTail);
            pileHead = NULL;
            pileTail = NULL;
        }
    }
}

void createNode() {
    struct CardNode* temp = malloc(sizeof(struct CardNode));
    if(pileTail->head != NULL){
        temp->next = NULL; 
        temp->prev = pileTail->tail; 
        pileTail->tail->next = temp;
        pileTail->tail = temp;
        pileTail->cardsInPile++;
    } else { // List is empty
        temp->prev = NULL;
        temp->next = NULL;
        
        pileTail->head = temp;
        pileTail->tail = temp;
        pileTail->cardsInPile++;
    
    }
}
int removeNode() {
    if(pileHead->tail!=NULL){
        struct CardNode* temp1;
        if(pileHead->tail->prev != NULL){
            temp1 = pileHead->tail->prev;
            pileHead->tail = pileHead->tail->prev;
            free(temp1);
            pileHead->tail->next = NULL;
            return 1;
        } else {
            //Last node in the list.
            free(pileHead->tail);
            pileHead->head = NULL;
            pileHead->tail = NULL;
            return 0;
        }
    }
    return 0;
}
void moveCardAtIndex(Pile *fromPile, Pile *toPile, int cardIndex) {
    CardNode *temp;
    if(fromPile->head == NULL) {
        strcpy(message, "Error moves cards pile empty");
        return;
    }

    for (int i = 0; i < cardIndex; i++)
    {   
        if(i == 0) {
            temp = fromPile->head;
        } else {
            if(temp->next == NULL) {
            strcpy(message, "Index out of bounds");
            return;
            }
            temp = temp->next;
        }
    }
    
    if(temp->prev == NULL) {
        if(temp->next == NULL) {
            // Last card in from pile
            fromPile->tail = NULL;
            fromPile->head = NULL;
        } 
        else {
            // Card is head
            fromPile->head = temp->next;
            fromPile->head->prev = NULL;

        }
    } else if(temp->next == NULL) {
        // Card is the tail of pile
        fromPile->tail = temp->prev;
        fromPile->tail->next = NULL;
        
    } else {
         // Card is in between 2 cards
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
    fromPile->cardsInPile--;
    
    if(toPile->head == NULL) {
        toPile->head = temp;
        toPile->tail = temp;
        temp->next = NULL;
        temp->prev = NULL;
        toPile->cardsInPile++;
    } else {
        toPile->tail->next = temp;
        temp->prev = toPile->tail;
        temp->next  = NULL;
        toPile->tail = temp;
        toPile->cardsInPile++;
    }

}
void moveTailCard(Pile *fromPile, Pile *toPile) {
    struct CardNode* temp;
    if(fromPile->tail == NULL) {
        return;
    }
    temp = fromPile->tail;
    // Move pointers for the piles
    if(temp->prev == NULL) {
        // Last card in Pile
        fromPile->tail = NULL;
        fromPile->head = NULL;
        fromPile->cardsInPile--;
    } else {
        // Multiple cards left in Pile
        fromPile->tail = fromPile->tail->prev;
        temp->prev->next = NULL;
        temp->prev = NULL;
        fromPile->cardsInPile--;
    }
    

    //Insert card into new pile
    if(toPile->tail == NULL) {
        // Pile is empty
        toPile->tail = temp;
        toPile->head = temp;
        toPile->cardsInPile++;
    } else {
        // If not empty add to the end of tail.
        toPile->tail->next = temp;
        temp->prev = toPile->tail;
        toPile->tail = temp;
        toPile->cardsInPile++;
    }
}
void moveCardsFromIndex(Pile *fromPile, Pile *toPile, int cardIndex) {
    if(fromPile->head == NULL) {
        strcpy(message, "Error moves cards pile empty");
        return;
    }
    struct CardNode* temp1 = fromPile->head; 
    int count = 1;
    // Navigate to chosen card.
    while(1) {
        if(temp1->next != NULL) {
            temp1 = temp1->next;
        }
        if(cardIndex != count && temp1->next == NULL) {
            strcpy(message, "Error in move cards, selected card does not exist.");
            return;
        }
        if(count == cardIndex) {
            break;
        }
        count++;
    }
    
    // Set correct pointers for the fromPile.
    if(temp1->prev == NULL) {
        fromPile->head = NULL;
        fromPile->tail = NULL;
        fromPile->cardsInPile -= count;
    } else {
        fromPile->tail = temp1->prev;
        fromPile->cardsInPile -= count;
    }

    // Set correct pointers for the toPile.
    if(toPile->head == NULL) {
        toPile->head = temp1;
        toPile->cardsInPile += count;
        
    } else {
        toPile->tail->next = temp1;
        temp1->prev = toPile->tail->prev;
        toPile->cardsInPile += count;
    }
        while(temp1->next != NULL) {
            temp1 = temp1->next;
        }
        toPile->tail = temp1;
}
void moveHeadCard(Pile *fromPile, Pile *toPile) {
    struct CardNode* temp;
    if(fromPile->head == NULL) {
        return;
    }
    temp = fromPile->head;
    // Move pointers for the piles
    if(temp->next == NULL) {
        // Last card in Pile
        fromPile->tail = NULL;
        fromPile->head = NULL;
        fromPile->cardsInPile--;

    } else {
        // Multiple cards left in Pile
        fromPile->head = fromPile->head->next;
        temp->next->prev = NULL;
        fromPile->cardsInPile--;
    }
    
    //Insert card into new pile
    if(toPile->tail == NULL) {
        // Pile is empty
        toPile->tail = temp;
        toPile->head = temp;
        toPile->cardsInPile++;
    } else {
        // If not empty add to the end of tail.
        toPile->tail->next = temp;
        temp->prev = toPile->tail;
        toPile->tail = temp;
        temp->next = NULL;
        toPile->cardsInPile++;
    }
}
int loadFile(char *filename) {
    char tempArray[5];

    FILE *fp;
    fp = fopen (filename, "r");
    if(fp==NULL) { 
        return 0;
    }
    while(!feof(fp)){

       fgets(tempArray, 5, fp);
       if(tempArray[strlen(tempArray)-1] == 5) {
           // Housekeeping delete all nodes (wrong format)
           return 1;
       }
       if(tempArray[strlen(tempArray)-1]== '\n'){
            tempArray[strlen(tempArray)-1] = 0;
        }
        createNode();
        pileTail->tail->value = tempArray[1];
        pileTail->tail->type = tempArray[0];
        pileTail->tail->isHidden = 1;
        
    }
    fclose(fp);
    return 2;
}

// Load a deck of cards or create a new one if not specified
void LD(char input[])
{
    // Remember to split the function to validate if input is "LD" or "LD <filename>"
    int status;
        // Lav nyt deck ublandet
        status = loadFile("cards.txt");
        if(status == 0) {
            strcpy(message, "Unable to open file");
            strcpy(lastCom, input);
            return;
        } 
        else if(status == 1) {
            strcpy(message, "Wrong format of file content");
            strcpy(lastCom, input);
            return;
        } 
        else {
            strcpy(message, "OK");
            strcpy(lastCom, input);    
        }

        Pile *tempPile;
        tempPile = pileHead;
        int count = 0;
        while(pileTail->head != NULL) {
            moveHeadCard(pileTail, tempPile);
            count++;
            if(count == 7) {
                tempPile = pileHead;
                count = 0;
            } else {
                tempPile = tempPile->next;
            }
        }

}

void SW() {
    if(pileHead == NULL) {
        strcpy(lastCom, input);
        strcpy(message, "No cards to show");
        return;
    }
    Pile *tempPile = pileHead;
    CardNode *tempNode = NULL;
    int colCount = 0;
    while (colCount < 7)
    {   
        if(tempPile->head != NULL) {
            tempNode = tempPile->head;
            while (tempNode != NULL)
            {   
            tempNode->isHidden = 0;
            tempNode = tempNode->next;
            }
        }
        tempPile = tempPile->next;
        colCount++;
    }
    
}
void SR() {
    Pile *tempPile = pileHead;
    Pile *ref;
    CardNode *tempNode;

    
    time_t t;
    srand((unsigned) time(&t));
    int col, index, cards, r;
    cards = DECK_SIZE;
    col = r = 0;
    while(cards != 0) {
        r = (rand() % 7);
        for (int i = 0; i < r; i++)
        {
            tempPile = tempPile->next;
            col++;
            if(col > 6) {
                tempPile = pileHead;
                col = 0;
            }
        }
        while( tempPile->cardsInPile == 0 || tempPile->head == NULL) {
            tempPile->next;
            col++;
            if(col > 6) {
                tempPile = pileHead;
                col = 0;
            }
        }
        
        if(tempPile->cardsInPile == 1) {
            moveHeadCard(tempPile, pileTail);
        } else {
        index = (rand() % tempPile->cardsInPile);
        moveCardAtIndex(tempPile, pileTail, index);
        }
        ref = pileHead;
        for (int i = 0; i < 7; i++)
        {
        printf("%d ", ref->cardsInPile);
        ref = ref->next;
        }
        printf("\n");        
        cards--; 
    }
    
    
    
}
void SI(int split) {
    // Fuck denne funktion sut diller 
}
 
        
        
        
void printSuit(char type) {
    if(type == 'H') {
        wprintf(L"\x2665");
    }
    if(type == 'D') {
        wprintf(L"\x2666");
    }
    if(type == 'S') {
        wprintf(L"\x2660");
    }
    if(type == 'C') {
        wprintf(L"\x2663");
    }  
 }

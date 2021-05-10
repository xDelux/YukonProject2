#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <memory.h>
#include <time.h>

#define DECK_SIZE 52
#define FOUNDATION_SIZE 4
#define COLUM_SIZE 7

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
} Pile;

/* typedef struct Foundation
{
    char id[2];
    struct CardNode *head;
    struct CardNode *tail;
    struct Foundation *next;
    struct Foundation *prev;
    int cardsInPile;
} Foundation; */

// Print opertaions
void printConsole();

void printCard(Card *card);

// Node functions 
//CardNode* makeNode(Card *card);
void createNode();
void removeNode();
void createPile();
void removePile();
void moveCard(Pile *fromPile, Pile *toPile);
void moveCards(Pile *fromPile, Pile *toPile, int cardIndex);

void appendNodeInDeck(CardNode *node);
void assignNodeInPile(Pile *pile, CardNode *node);


void appendPile(Pile *head, char *name);
void appendFoundation(Foundation *head, char *name);
void newDeck();

// Command functions
FILE *LD();
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

char types[4] = {'H', 'D', 'S', 'C'};
char values[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

Card deck[13][4];

// First pile and foundation
Pile *pileHead;
Pile *pileTail;


int main(void)
{
    initCards();
    initPilesNFoundations();

    do
    {       
        update();
        scanf("%s", &input);
        if(strcmp(input, "SW") == 0) {SW();}
        if(strcmp(input, "LD") == 0) {LD();}
        if(strcmp(input, "SR") == 0) {SR();}
        if(strcmp(input, "T") == 0) {
            time_t t;
            CardNode *ref = startOfDeck;
            srand((unsigned) time(&t));
            for (int i = 0; i < rand() % 53; i++)
            {
                ref = ref->nextInDeck;
            }
            printCard(ref->card);
            printf("->");
            printCard(ref->nextInDeck->card);
            puts("");
            
        }
        
    } while (strcmp(input, "QQ") != 0); 
}

// Prints the console
void update()
{
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\t\t\n\n");
    // Counters
    int line, tails;
    line = tails = 0;
    // Pointers for the piles, foundations and nodes.
    Pile *pile = C1;
    int done = 0;
    int dontPrint = 1;
    Foundation *foundation = F1;
    CardNode *cn = NULL;

    if(game == 0) {
        if(startOfDeck != NULL) {
            cn = startOfDeck;
        }
        while(done == 0) {
            for (int i = 0; i < COLUM_SIZE; i++)
            {
                if(cn != NULL) {
                printCard(cn->card);
                cn = cn->nextInDeck;
                }
                printf("\t");
            }
            if (line == 0 || line == 2 || line == 4 || line == 6)
            {
                printf("[]");
                printf(" %s", foundation->id);
                foundation = foundation->next;
            } 
            printf("\n");
            if(cn == NULL && line >= 8) {done = 1;}
            line++;
        }
    } else {
    
    while (done == 0)
    {   
        for (int i = 0; i < COLUM_SIZE; i++)
        {
            if (pile->head != NULL)
            {
                cn = pile->head;
                if (line != 0)
                {
                    for (int i = 0; i < line; i++)
                    {   
                        // Traverse for every line 
                        if(cn->next == NULL){
                            tails++;
                            dontPrint = 0;
                            break;
                        } else {
                            cn = cn->next;
                        }
                    }   
                }
                if(dontPrint){printCard(cn->card);}
                
                
            } else
            {
                tails++;
            }
            printf("\t");
            if(tails >= 7 && line >= 6) {done = 1;}
            pile = pile->next;
            dontPrint = 1;
        }
        if (line == 0 || line == 2 || line == 4 || line == 6)
            {
                if(foundation->tail != NULL) {
                    cn = foundation->tail;
                    printCard(cn->card);
                }
                else {
                    printf("[]");
                }
                printf(" %s", foundation->id);
                foundation = foundation->next;
            }
        tails == 0;
        line++;
        printf("\n");
    }
    }
    printf("LAST Command: %s\n", lastCom);
    printf("Message: %s\n", message);
    printf("INPUT > ");
}
void printCard(Card* card)
{
    if (card->isHidden == 0)
    {
        printf("%c", card->value);
        printf("%c", card->type);
        
    }
    else
    {
        printf("[]");
    }
}

//Creates all struct Card information
void initCards()
{
    int count = DECK_SIZE;
    int j = 0;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < count/4; i++) {
        // Order goes 0 = hearts, 1 = diamonds, 2 = spades, 3 = clovers
        deck[i][j].value = values[i];
        deck[i][j].type = types[j];
        deck[i][j].isHidden = 0;
        }
        
    }
}
void initPilesNFoundations() {
    
    C1 = (Pile*)malloc(sizeof(struct Pile));
    strcpy(C1->id, "C1");
    C1->prev = NULL; C1->next = NULL; C1->tail = NULL; C1->head = NULL;
    
    F1 = (Foundation*)malloc(sizeof(struct Foundation));
    strcpy(F1->id, "F1"); 
    F1->prev = NULL; F1->next = NULL; F1->tail = NULL; F1-> head = NULL;
    int piles, foundations;
    piles = COLUM_SIZE - 1;
    foundations = FOUNDATION_SIZE - 1;
    
    char pId[2];
    char fId[2];
    for (int j = 0; j < foundations; j++)
    {
        sprintf(fId, "F%d", j+2);
        appendFoundation(F1, fId);
    }

    for (int i = 0; i < piles; i++)
    {   
        sprintf(pId, "C%d", i+2);
        appendPile(C1, pId);
        
    }
}

void createPile() {
    if(pileHead != NULL){
        struct Pile* temp1 = malloc(sizeof(struct Pile));
        temp1->next = NULL; 
        temp1->prev = pileTail; 
        pileTail->next = temp1;
        pileTail = temp1;
    } else { // List is empty
        pileHead = malloc(sizeof(struct Pile));	// Setting up space in the memory for the 1st node.
        pileHead->prev = NULL;
        pileHead->next = NULL;
        
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
    struct CardNode* temp1 = malloc(sizeof(struct CardNode));
    if(pileHead->head != NULL){
        temp1->next = NULL; 
        temp1->prev = pileHead->tail; 
        pileHead->tail->next = temp1;
        pileHead->tail = temp1;
    } else { // List is empty
        temp1->prev = NULL;
        temp1->next = NULL;
        
        pileHead->head = temp1;
        pileHead->tail = temp1;
    
    }
}
int removeNode() {
    if(pileHead->tail!=NULL){
        struct CardNode* temp1;
        if(pileHead->tail->prev != NULL){
            temp1 = pileHead->tail->prev;
            pileHead.tail = pileHead->tail->prev;
            free(temp1);
            pileHead.tail->next = NULL;
            return 1;
        } else {
            //Last node in the list.
            free(pileHead.tail);
            pileHead.head = NULL;
            pileHead.tail = NULL;
            return 0;
        }
    }
    return 0;
}

void moveCard(Pile *fromPile, Pile *toPile) {
    struct CardNode* temp1;
    temp1 = fromPile->tail;
    // Move pointers for the piles
    if(temp1->prev == NULL) {
        // Last card in Pile
        fromPile->tail = NULL;
        fromPile->head = NULL;

    } else {
        // Multiple cards left in Pile
        fromPile->tail = fromPile->tail->prev;
    }
    
    // Now we want to move the pointer of the cards
    if(temp1->prev == NULL) {
        // Last card in pile, do nothing.
    } else {
        temp1->prev->next = NULL;
        temp1->prev = NULL;
    }

    //Insert card into new pile
    if(toPile->tail == NULL) {
        // Pile is empty
        toPile->tail = temp1;
        toPile->head = temp1;
    } else {
        // If not empty add to the end of tail.
        toPile->tail->next = temp1;
        temp1->prev = toPile->tail;
        toPile->tail = temp1;
    }
}
void moveCards(Pile *fromPile, Pile *toPile, int cardIndex) {
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
            strcpy(message, "Error in move cards, selected card does not exist.")
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
    } else {
        fromPile->tail = temp1->prev;
    }

    // Set correct pointers for the toPile.
    if(toPile->head == NULL) {
        toPile->head = temp1;
        
    } else {
        toPile->tail->next = temp1;
        temp1->prev = toPile->prev;
        
    }
        while(temp1->next != NULL) {
            temp1 = temp1->next;
        }
        toPile->tail = temp1;
}

// Load a deck of cards or create a new one if not specified
FILE *LD(char input[])
{
    if (strcmp(input, "LD") == 0)
    {
        // Lav nyt deck ublandet
        newDeck();
        strcpy(message, "OK");
        strcpy(lastCom, "LD");
        return NULL;
    }
    if (access(input, F_OK) == 0)
    {
        strcpy(message, "OK");
        strcpy(lastCom, ("LD %s", input));
        return fopen(input, "r");
    }
    else
    {
        strcpy(message, "FILE 404 NOT FOUND");
        strcpy(lastCom, ("LD %s", input));
        return NULL;
    }
}
void SW() {
    Pile *pile = C1;
    
    CardNode *node = C1->head;
    
    Card *card;
    
    for (int i = DECK_SIZE; i > 0; i--)
    {   
        card = node->card;
        card->isHidden = 0;
        if(node->next == NULL) {
            pile = pile->next;
            node = pile->head;
        } else {
            node = node->next;
        }
        
    }
    
}
void SR() {
    CardNode *card;
    CardNode *ref;
    CardNode *ref2;
    CardNode *startOfShuffled = NULL;
    int cards = DECK_SIZE;
    if(startOfDeck == NULL) {
        strcpy(message, "NO DECK TO SHUFFLE");
        strcpy(lastCom, "SR");
        return;
    } else {
        time_t t;
        srand((unsigned) time(&t));
        card = startOfDeck;
        ref = startOfDeck;
        
        while(cards != 0) {
            for (int i = 0; i < rand() % cards+1; i++)
            {
                card = card->nextInDeck;
            }
            
            card->prevInDeck->nextInDeck = card->nextInDeck;
            card->nextInDeck->prevInDeck = card->prevInDeck;
            
            if(startOfDeck == NULL;) {
                startOfDeck = card;
                card->nextInDeck = NULL;
                card->prevInDeck = NULL;
            } else {
                ref = startOfDeck;
                while(card->nextInDeck != NULL) {
                    
                }
            }
            cards--;
        }
        
    }

}

void newDeck()
{
    Pile *pile = C1;
    Card *card;
    int type, value;
    type = value =  0;
        
    for (int j = 0; j < 4; j++)
    {
       for (int i = 0; i < 13; i++)
       {
            card = &deck[i][j];
            card->isHidden = 1;
            CardNode *node = makeNode(card);
            appendNodeToDeck(node);
            assignNodeInPile(pile, node);
            pile = pile->next;    
       }  
    }
}
    

int cardValue(Card card)
{
    switch (card.value)
    {
    case 'A':
        return 1;
        break;
    case '2':
        return 2;
        break;
    case '3':
        return 3;
        break;
    case '4':
        return 4;
        break;
    case '5':
        return 5;
        break;
    case '6':
        return 6;
        break;
    case '7':
        return 7;
        break;
    case '8':
        return 8;
        break;
    case '9':
        return 9;
        break;
    case 'T':
        return 10;
        break;
    case 'J':
        return 11;
        break;
    case 'Q':
        return 12;
        break;
    case 'K':
        return 13;
        break;
    default:
        break;
    }
}

int isBlack(struct Card c)
{
    return c.type == 'S' || c.type == 'C';
}
int isRed(struct Card c)
{
    return c.type == 'H' || c.type == 'D';
}
int isDifferent(struct Card c1, struct Card c2)
{
    return c1.type != c2.type;
}
int isSequencial(struct Card lower, struct Card higher)
{
    return higher.value == lower.value + 1;
}
int canFoundation(struct Card c)
{
    return c.value == 13;
}
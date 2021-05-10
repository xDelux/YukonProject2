#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <memory.h>
#include <time.h>

#define DECK_SIZE 52
#define FOUNDATION_SIZE 4
#define COLUM_SIZE 7

typedef struct Card
{
    char value;
    char type;
    int isHidden;
} Card;

typedef struct CardNode
{
    struct Card *card;
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

typedef struct Foundation
{
    char id[2];
    struct CardNode *head;
    struct CardNode *tail;
    struct Foundation *next;
    struct Foundation *prev;
    int cardsInPile;
} Foundation;

char input[10];
char message[256] = "HELLO";
char lastCom[10] = "NONE";

char types[4] = {'H', 'D', 'S', 'C'};
char values[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

Card deck[13][4];

// First pile and foundation
Pile *C1;
Foundation *F1;

// 
void update();
void newDeck();
void printCard(Card *card);

//
void appendNodeInPile(Pile *pile, Card *card);
void appendPile(Pile *head, char *name);
void appendFoundation(Foundation *head, char *name);

// Command functions
FILE *load();
void show();

// Initialization
void initCards();
void initPilesNFoundations();

int main(void)
{
    initCards();
    initPilesNFoundations();
    
    
    /* Pile *pile = C1;
    Foundation *found = F1;
    
    for (int i = 0; i < 7; i++)
    {
        printf("%s -> %s\n", pile->id, pile->next->id);
        pile = pile->next;
    }
    for (int i = 0; i < 4; i++)
    {
        printf("%s -> %s\n", found->id, found->next->id);
        found = found->next;
    }
    pile = C1;
    pile = pile->next;
    CardNode *n = pile->head;
    while(1) {
        printCard(n->card);
        if(n->next == NULL) {break;}
        n = n->next;
    } */
    do
    {
        update();
        scanf("%s", &input);
        if(strcmp(input, "LD") == 0) {
            newDeck();
        }
        if(strcmp(input, "SW") == 0) {
            show();
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
    int DONE = 1;
    int dontPrint = 1;
    Foundation *foundation = F1;
    CardNode *cn = NULL;
    while (DONE)
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
            if(tails >= 7 && line >= 6) {DONE = 0;}
            pile = pile->next;
            dontPrint = 1;
        }
        if (line == 0 || line == 2 || line == 4 || line == 6)
            {
                if(foundation->tail != NULL) {
                    cn = foundation->tail;
                    printCard(cn->card);
                }
                printf(" %s", foundation->id);
                foundation = foundation->next;
            }
        tails == 0;
        line++;
        printf("\n");
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

void appendPile(Pile *head, char *name) {

    //Make a new Pile and make th
    struct Pile* newPile = (Pile*)malloc(sizeof(struct Pile));
    struct Pile* last = head;

    strcpy(newPile->id, name);

    newPile->next = NULL;
    
    //If the list empty make the new Pile the head of the list.
    if(head == NULL) {
        newPile->prev = NULL;
        newPile->next = NULL;
        newPile->head = NULL;
        head = newPile;
        return;
    }

    // Traverse
    int i = 0;
    while(last->next != NULL) {
        last = last->next;
        i++;
    }

    //Set the pointers when hit the last node.
    last->next = newPile;
    newPile->prev = last;
    newPile->head = NULL;

    if(i == 5) {
        newPile->next = head;
    }
    
}
void appendFoundation(Foundation *head, char *name) {
    //Make a new Foundation and 
    struct Foundation* newFound = (Foundation*)malloc(sizeof(struct Foundation));
    struct Foundation* last = head;

    strcpy(newFound->id, name);
    newFound->next = NULL;
    newFound->tail = NULL;
    newFound->head = NULL;
    
    //If the list is empty make the new Foundation the head of the list.
    if(head == NULL) {
        newFound->prev = NULL;
        head = newFound;
        return;
    }

    // Traverse through the Foundation
    while(last->next != NULL) {
        last = last->next;
    }

    //Set the pointers when hit the last node.
    last->next = newFound;
    newFound->prev = last;
}
void appendNodeInPile(Pile *pile, Card *card)
{
    CardNode *headNode = pile->head;
    
    if (headNode == NULL)
    {
        CardNode *newNode = (CardNode *)malloc(sizeof(CardNode));
        newNode->card = card;
        pile->head = newNode;
        newNode->next = NULL;
        newNode->prev = NULL;
        return;
    } 
    else {
        // Traverse
        while(headNode->next != NULL) {
            headNode = headNode->next;
        }
        
        CardNode *newNode = (CardNode *)malloc(sizeof(CardNode));
        newNode->card = card;
        
        newNode->next = NULL;
        headNode->next = newNode;
        newNode->prev = newNode;
        
    }
    pile->cardsInPile++;
}

// Load a deck of cards or create a new one if not specified
FILE *load(char input[])
{
    if (strcmp(input, "LD") == 0)
    {
        // Lav nyt deck ublandet
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
void show() {
    int cards = DECK_SIZE;
    Pile *pile = C1;
    CardNode *node = C1->head;
    while(cards > 0) {
        node->card->isHidden = 0;
        if(node->next == NULL) {
            pile = pile->next;
        }
        node = node->next;
        cards--;
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
            appendNodeInPile(pile, card);
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
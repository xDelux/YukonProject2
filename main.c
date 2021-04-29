#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <memory.h>
#include <time.h>

#define DECK_SIZE 52
#define PILE_SIZE 4
#define COLUM_SIZE 7


char input[10];
char message[256] = "HELLO";
char lastCom[10] = "NONE";



typedef struct Card {
    char value;
    char type;
    int isHidden;
} Card;

typedef struct CardNode {
    Card *card;
    struct CardNode *next;
    struct CardNode *prev;
} CardNode;

typedef struct Pile {
    CardNode *head;
    int cardsInPile;
} Pile;

const char *typeToCharPtr();

void update();
FILE *load();
void initCards();
CardNode *createCardNode();


int main(void) {
    do {
    update();
    scanf("%s", &input); 
    // if(strcmp(input, "LD") == 0)
    
    }while (strcmp(input, "QQ") != 0);

}

void update() {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\t\t\n\n");
    printf("\t\t\t\t\t\t\t[]\tF1\n");
    printf("\n");
    printf("\t\t\t\t\t\t\t[]\tF2\n");
    printf("\n");
    printf("\t\t\t\t\t\t\t[]\tF3\n");
    printf("\n");
    printf("\t\t\t\t\t\t\t[]\tF4\n");
    printf("LAST Command: %s\n", lastCom);
    printf("Message: %s\n", message);
    printf("INPUT > ");
}

//Create all card information
void initCards() {
    char id[2];
    int count = DECK_SIZE;
    for (int i = 0; i < count; i++)
    {
        
    }
    
}

//Allocate memory for a node
CardNode *creatCardNode(Card *card) {
    CardNode *newCardNode;
    newCardNode = (CardNode*)malloc(sizeof(CardNode));
    if(newCardNode == NULL) {
        strcpy(message, "MALLOC ERROR");
    }
    newCardNode->card = card;
    newCardNode->next = 0;
    return newCardNode;
}

void push(struct CardNode node, struct CardNode** head) {
    node->next = (*head);
    node->prev = NULL;

    if((*head) != NULL)
        (*head)->prev = node;    
    
    (*head) = node;    
}
// Load a deck of cards or create a new one if not specified
FILE *load(char input[]) {
    if(strcmp(input, "LD") == 0) {
        // Lav nyt deck ublandet
        strcpy(message, "OK");
        strcpy(lastCom, "LD");
        return;
    }
    if( access(input, F_OK ) == 0) {
        strcpy(message, "OK");
        strcpy(lastCom, ("LD %s", input));
        return fopen(input, "r"); 
        }
    else {
        strcpy(message, "FILE 404 NOT FOUND");
        strcpy(lastCom, ("LD %s", input));
        return; 
        }       
}

int cardValue(Card card) {
    switch (card.value)
    {
    case 'A' :
        return 1;
        break;
    case '2' :
        return 2;
        break;
    case '3' :
        return 3;
        break;
    case '4' :
        return 4;
        break;
    case '5' :
        return 5;
        break;
    case '6' :
        return 6;
        break;
    case '7' :
        return 7;
        break;
    case '8' :
        return 8;
        break;
    case '9' :
        return 9;
        break;
    case 'T' :
        return 10;
        break;
    case 'J' :
        return 11;
        break;
    case 'Q' :
        return 12;
        break;
    case 'K' :
        return 1;
        break;
    default:
        break;
    }
}

int isBlack(struct Card c) {
    return c.type == 'S' || c.type == 'C';
}
int isRed(struct Card c) {
    return c.type == 'H' || c.type == 'D';
}
int isDifferent(struct Card c1, struct Card c2) {
    return c1.type != c2.type;
}
int isSequencial(struct Card lower, struct Card higher) {
    return higher.value == lower.value + 1;
}
int canFoundation(struct Card c) {
    return c.value == 13;
}
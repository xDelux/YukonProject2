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
    struct Card *card;
    struct CardNode *next;
    struct CardNode *prev;
} CardNode;

typedef struct Pile {
    char *id;
    struct CardNode *head;
    struct CardNode *tail;
    struct Pile *next;
    struct Pile *prev;
    int cardsInPile;
} Pile;

typedef struct Foundation {
    char *id;
    struct CardNode *head;
    struct CardNode *tail;
    struct Foundation *next;
    struct Foundation *prev;
    int cardsInPile;
} Foundation;

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
    // Counters
    int line, tails, i;
    line = tails = 0;
    // Pointers for the piles, foundations and nodes.
    Pile *pile;
    Foundation *foundation:
    CardNode *cn;
    while(1)
    {
        
        for (i = 0; i < COLUM_SIZE; i++) {
            if(pile != NULL) {
                cn = pile.tail->card;
                if(line != 0) {
                    for (int i = 0; i < line; i++) {
                        if(cn->next != NULL) {
                            cn->next; }
                        } else {
                            tails++; 
                            goto;
                        } 
                    }
                    printCard(&cn);
                } else {
                    tails++;
                }               
            }
            printf("\t")
            pile = pile.next;
        }
        if(line == 2 || line == 4 || line == 6 || line == 8) {
                printCard(foundation.tail->card))
                foundation = foundation.next;
            }
        line++;
        printf("\n");
        if(tails == 7) {
            return;
        }
        tails == 0;
    
    printf("LAST Command: %s\n", lastCom);
    printf("Message: %s\n", message);
    printf("INPUT > ");
}

void printCard(Card *card) {
    if(card->isHidden == 0) {
        printf("%s", card->type);
        printf("%s", card->value);
    } else {
        printf("[]");
    }
}
//Create all card information
void initCards() {
    char id[2];
    int count = DECK_SIZE/4;
        for (int i = 0; i < count; i++) {
            
        }
        for (int i = 0; i < count; i++) {
            
        }
        for (int i = 0; i < count; i++) {
            
        }
        for (int i = 0; i < count; i++) {
           
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

void push(pile *pile, Card *card) {
  CardNode tail = pile->tail;
  if (tail == NULL) {
    pile->head = createCardNode(card);
  } else {
    tail->next = createCardNode(card);
  }
  pile->cardsInPile++;
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
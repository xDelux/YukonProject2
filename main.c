#include<stdio.h>
#include<stdlib.h>
#include "CardFunctions.c"
#include<unistd.h>

#define DECK_SIZE 52
#define PILE_SIZE 4
#define COLUM_SIZE 7


char input[];
char message[];
char lastCom[];

enum {H, D, S, C};
enum {A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K};

typedef struct Card {
    char value;
    char type;
    int isHidden;
};

typedef struct CardNode {
    Card *card;
    struct Card *next;
    struct Card *prev;
};

typedef struct Pile {
    Card *head;
    int cardsInPile;
};

const char *typeToCharPtr();

void printConsole();
File *load();
void initCards();
CardNode *createCardNode();

int main(void) {
    printConsole();
    scanf("%s", &input);

}

void printConsole() {
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\t\t\n\n");
    printf("\t\t\t\t\t\t\t[]\tF1\n");
    printf("\n");
    printf("\t\t\t\t\t\t\t[]\tF2\n");
    printf("\n");
    printf("\t\t\t\t\t\t\t[]\tF3\n");
    printf("\n");
    printf("\t\t\t\t\t\t\t[]\tF4\n");
    printf("LAST Command: %s\n" + lastCom);
    printf("Message: %s\n" + message);
    printf("INPUT > ");
}

void initCards() {
    char id[2]
    for (size_t i = 0; i < count; i++)
    {
        
    }
    
}

CardNode *creatCardNode(Card *card) {
    CardNode *newCardNode;
    newCard = (Card*)malloc(sizeof(Card));
    if(newCard == NULL) {
        message = "MALLOC ERROR";
    }
    newCardNode->card;
    newCardNode->next = 0;
    return newCardNode;
}

File* load(char input[]) {
    if(input == NULL) {
        // Lav nyt deck ublandet
        message = "OK"
        lastCom = "LD"
        return;
    }
    if( access(input, F_OK ) == 0) {
        message = "OK"
        lastCom = "LD %s" + input;
        return fopen(input, "r"); 
        }
    else {
        message = "FILE 404 NOT FOUND";
        lastCom = "LD %s" + input;
        return; 
        }
}
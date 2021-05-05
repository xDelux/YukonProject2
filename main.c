#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <memory.h>
#include <time.h>

#define DECK_SIZE 52
#define PILE_SIZE 4
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
    char *id;
    struct CardNode *head;
    struct CardNode *tail;
    struct Pile *next;
    struct Pile *prev;
    int cardsInPile;
} Pile;

typedef struct Foundation
{
    char *id;
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

Card deck[4][13];
Pile piles[7];
struct Foundation foundations[4];

const char *typeToCharPtr();
void pushNode(Pile *pile, Card *card);
void pushPile(Pile *pile);
void update();
FILE *load();
void initCards();
CardNode *createCardNode(Card *card);
void printCard(Card *card);
void newDeck();

int main(void)
{
    initCards();
    do
    {
        update();
        scanf("%s", &input);
        // if(strcmp(input, "LD") == 0)

    } while (strcmp(input, "QQ") != 0);
}

// Prints the console
void update()
{
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\t\t\t\n\n");
    // Counters
    int line, tails, i;
    line = tails = 0;
    i = 1;
    // Pointers for the piles, foundations and nodes.
    Pile *pile = &piles[0];
    Foundation *foundation = &foundations[0];
    CardNode *cn = NULL;
    Card *c = NULL;
    while (1)
    {   
        printf("Outer loop reached");
        for (i = 0; i < COLUM_SIZE; i++)
        {
            printf("Middle loop reached");
            if (pile != NULL)
            {
                cn = pile->tail;
                if (line != 0)
                {
                    for (int i = 0; i < line; i++)
                    {
                        printf("Inner loop reached");
                        if (cn->next != NULL)
                        {
                            cn->next;
                        }
                        else
                        {
                        tails++;
                        break;
                        }
                    }   
                }
                c = cn->card;
                printCard(c);
            } else
            {
                printf("tails hehe");
                tails++;
            }
        }
        printf("\t");
        pile = pile->next;
        
        if (line == 2 || line == 4 || line == 6 || line == 8)
        {
                if(foundation->tail != NULL) {
                    c = foundation->tail->card;
                    printCard(c);
                }
                printf("F%d", i);
                foundation = foundation->next;
                i++;
        }
        printf("\n");
        if(tails == 7 && line >= 8) {
            printf("break reached");
            break;
        }
        tails == 0;
        line++;
        
    }
    printf("LAST Command: %s\n", lastCom);
    printf("Message: %s\n", message);
    printf("INPUT > ");
}

void printCard(Card *card)
{
    if (card->isHidden == 0)
    {
        printf("%s", card->type);
        printf("%s", card->value);
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
        deck[j][i].type = types[j];
        deck[j][i].value = values[i];
        }
    }
}

void insertAfterPile(Pile *prevPile, char *name) {
    if(prevPile == NULL) {
        return;
    }
    struct Pile newPile = (struct Pile*)malloc(sizeof(struct Pile));
    newPile->id = name;

    newPile->prev = nextPile->prev;
    next->prev = newPile;

    newPile
}

void pushNodeInPile(Pile *pile, Card *card)
{
    CardNode *tail = pile->tail;
    if (tail == NULL)
    {
        pile->head = createCardNode(card);
    }
    else
    {
        tail->next = createCardNode(card);
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

void newDeck()
{
    int type, value;
    type = value = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int i = 0; i < DECK_SIZE / 4; i++)
        {
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

//Allocate memory for a node
CardNode *createCardNode(Card *card)
{
    CardNode *newCardNode;
    newCardNode = (CardNode *)malloc(sizeof(CardNode));
    if (newCardNode == NULL)
    {
        strcpy(message, "MALLOC ERROR");
        return NULL;
    }
    newCardNode->card = card;
    newCardNode->next = 0;
    return newCardNode;
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
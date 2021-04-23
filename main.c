#include<stdio.h>
#include<stdlib.h>

char input[];

struct Card {
    char value;
    char type;
    int hidden;
    struct Card* next;
    struct Card* prev;
};

void printConsole();
void commandLD();

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
    printf("LAST Command: \n");
    printf("Message: \n");
    printf("INPUT > ");
}
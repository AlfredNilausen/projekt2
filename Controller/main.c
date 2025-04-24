#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Model/card.h"
#include "../Model/columns.h"
#include "../Model/deck.h"
int LD(char* filename);
Deck currentdeck;
char* keyboardInput();
void errorcode(int);
int main(void) {
    currentdeck = createDeck();

    int tal = LD("C:\\Users\\alfre\\CLionProjects\\projekt2\\Model\\filename.txt");
    if (tal < 0) {
        errorcode(tal);
    } else {
        printf("The deck has: %d cards", tal);
    }
    tal = LD("C:\\Users\\alfre\\CLionProjects\\projekt2\\Model\\filename2.txt");
    if (tal < 0) {
        errorcode(tal);
    } else {
        printf("\nThe deck has: %d cards", tal);
    }
    tal = LD("C:\\Users\\alfre\\CLionProjects\\projekt2\\Model\\filename3.txt");
    if (tal < 0) {
        errorcode(tal);
    } else {
        printf("\nThe deck has: %d cards", tal);
    }
    tal = LD("C:\\Users\\alfre\\CLionProjects\\projekt2\\Model\\filenam.txt");
    if (tal < 0) {
        errorcode(tal);
    } else {
        printf("\nThe deck has: %d cards", tal);
    }
    /*
    Card* deck = createDeckShuffled();
    Card* columns[7] = {NULL};
    dealToColumns(deck, columns);
    printColumns(columns);
    freeColumns(columns);
    */
    return 0;
}

int LD(char* filename) {
    int cards = 0;
    int letters = 0;
    Deck tempdeck = createDeck();
    FILE* file = fopen(filename, "r");
    if (!file) {
        return -1;
    }
    char data[10];
    while (fgets(data, 10, file) != NULL) {
        char rank = data[0];
        char suit = data[1];
        if ((rank >= '2' && rank <= '9') || rank == 'A' || rank == 'T' || rank == 'J' || rank == 'Q' || rank == 'K') {
            if (suit == 'H' || suit == 'D' || suit == 'C' || suit == 'S') {
                Card *newcard = createCard(rank, suit);
                int check = addCard(newcard, &tempdeck);
                if (check == -1) {
                    return -3;
                }
                cards++;
            } else {
                return -2;
            }
        } else {
            return -2;
        }

        }
    fclose(file);
    currentdeck = tempdeck;
    return cards;

}

char* keyboardInput() {
    char label[10];
    scanf("%s", label);
    char* output;
    output = &label[0];
    return output;
}

void errorcode(int code) {
    if (code == -1) {
        printf("\nFile cannot be found");
    } else if (code == -2) {
        printf("\nDeck contains a fake card");
    } else if (code == -3) {
        printf("\nDeck contains a duplicate card");
    }
}
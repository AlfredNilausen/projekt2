#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Model/card.h"
#include "../Model/columns.h"
#include "../Model/deck.h"
#include "../View/BoardView.h"

#define MAX_INPUT 100

int LD(char* filename);
Deck currentdeck;
char* keyboardInput();
void errorcode(int);
int main(void) {
    currentdeck = createDeck();

    srand(time(NULL)); // random til shuffle

    Card* deck = NULL;
    Card* columns[7] = {NULL};  // 7 kolonner

    char input[MAX_INPUT];
    char lastCommand[MAX_INPUT] = "";
    char message[MAX_INPUT] = "No game started yet.";

    printf("YUKON - TEXT MODE\n");

    while (1) {
        // Vis status
        printf("\nLAST Command: %s\n", lastCommand);
        printf("Message: %s\n", message);
        printf("INPUT > ");

        // Læs input fra bruger
        if (!fgets(input, sizeof(input), stdin)) {
            strcpy(message, "Error reading input");
            continue;
        }

        // Fjern newline
        input[strcspn(input, "\n")] = 0;
        strcpy(lastCommand, input);

        // ---------- Parser kommandoer ----------
        if (strncmp(input, "LD", 2) == 0) {
            strcpy(message, "Loading deck not implemented yet!");

        } else if (strcmp(input, "SW") == 0) {
            if (deck)
                printDeck(deck);
            else
                strcpy(message, "No deck loaded");

        } else if (strcmp(input, "P") == 0) {
            if (!deck) {
                strcpy(message, "No deck loaded to play");
            } else {
                dealToColumns(deck, columns);
                strcpy(message, "Game started!");
            }

        } else if (strcmp(input, "C") == 0) {
            printColumns(columns);
            strcpy(message, "Columns printed");

        } else if (strcmp(input, "Q") == 0) {
            strcpy(message, "Quitting...");
            break;

        } else {
            strcpy(message, "Unknown command");
        }
    }

    // Ryd op
    freeColumns(columns);
    freeDeck(deck);

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
    //TODO call view
    //printLD();
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Model/card.h"
#include "../Model/columns.h"
#include "../Model/deck.h"
#include "../View/BoardView.h"
#include "../Controller/GameController.h"
#include "../Model/Game.h"

#define MAX_INPUT 100


int main(void) {
    setDeck(createDeck());
    createDeck();
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
            int tal = LD(input + 3);
            if (tal == 52) {
                strcpy(message, "Loading deck completed");
            } else {
                errorcode(tal);
                //printf("Loading deck failed\n with %d cards", tal);
                strcpy(message, "Error in loading deck");
            }

        } else if (strcmp(input, "SW") == 0) {
            if (getDeck()->size == 52) {
                //printDeck(getDeck());
                for (int i = 0; i < 7; i++) {
                    printColumn(getColumn(i));
                }
                strcpy(message, "Deck printed succesfully");
            } else {
                strcpy(message, "No deck loaded");
            }

        } else if (strcmp(input, "P") == 0) {
            if (!deck) {
                strcpy(message, "No deck loaded to play");
            } else {
                //dealcardstocolumn(deck, columns);
                strcpy(message, "Game started!");
            }

        } else if (strcmp(input, "C") == 0) {
            //printColumn(columns);
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



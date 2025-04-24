#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "card.h"
#include "columns.h"


#define MAX_INPUT 100

int main() {
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

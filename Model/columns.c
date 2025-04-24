#include "columns.h"
#include "card.h"
#include <stdio.h>
#include <stdlib.h>

void dealToColumns(Card* shuffledDeck, Card* columns[7]) {
    Card* current = shuffledDeck;

    for (int col = 0; col < 7; col++) {
        int faceDown = col;
        int faceUp = (col == 0) ? 1 : 5;
        int total = faceDown + faceUp;

        Card* last = NULL;

        for (int i = 0; i < total; i++) {
            Card* next = current->next;
            current->next = NULL;

            current->visible = (i >= faceDown) ? 1 : 0;

            if (columns[col] == NULL) {
                columns[col] = current;
                last = current;
            } else {
                last->next = current;
                last = current;
            }

            current = next;
        }
    }
}


void printColumns(Card* columns[7]) {
    for (int i = 0; i < 7; i++) {
        printf("Column %d:\n", i + 1);
        Card* current = columns[i];
        while (current != NULL) {
            if (current->visible)
                printf("  %c of %c \n", current->rank, current->suit);
            else
                printf("  XX (Invisble)\n");
            current = current->next;
        }
    }
}

void freeColumns(Card* columns[7]) {
    for (int i = 0; i < 7; i++) {
        Card* current = columns[i];
        while (current != NULL) {
            Card* next = current->next;
            free(current);
            current = next;
        }
        columns[i] = NULL;
    }
}

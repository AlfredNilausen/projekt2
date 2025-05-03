//
// Created by alfre on 01-05-2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Model/card.h"
#include "../Model/columns.h"
#include "../Model/deck.h"
#include "../View/BoardView.h"
#include "GameController.h"
#include "../Model/Game.h"


int LD(const char* filename) {

    char fullpath[512];  // Ensure this is big enough
    snprintf(fullpath, sizeof(fullpath), "../Model/%s",  filename);
    int cards = 0;
    int letters = 0;
    Deck tempdeck = createDeck();
    FILE* file = fopen(fullpath, "r");
    if (!file) {
        return -1;
    }
    char data[10];
    while (fgets(data, 10, file) != NULL) {
        char rank = data[0];
        char suit = data[1];
        if ((rank >= '2' && rank <= '9') || rank == 'A' || rank == 'T' || rank == 'J' || rank == 'Q' || rank == 'K') {
            if (suit == 'H' || suit == 'D' || suit == 'C' || suit == 'S') {
                Card *newcard = createCard(rank, suit,-1);
                int check = addCardBottom(newcard, &tempdeck);
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
    if (cards == 52) {
        setDeck(tempdeck);
        dealcardstocolumn(&tempdeck, -1);
        printBoard();
        return cards;
    } else {
        return -4;
    }
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
    } else if (code == -4) {
        printf("\nDeck doesnt contain enough cards");
    }

}


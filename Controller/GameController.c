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
    if (strlen(filename) == 0) {
        filename = "filename.txt"; //default unshuffled deck
    }
    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "../Model/%s",  filename); //getting the path to the deck
    int cards = 0; //counter to make sure we have 52 cards
    Deck tempdeck = createDeck();
    FILE* file = fopen(fullpath, "r");
    if (!file) {
        return -1; //errorcode for not opening the file
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
int saveDeckToFile(Deck* deck, const char* filename) {
    if (strlen(filename) == 0) {
        filename = "cards.txt";
    }
    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "../Model/%s",  filename);
    FILE* file = fopen(fullpath, "w");
    if (!file) {
        printf("Error: Could not open file '%s' for writing.\n", filename);
        return -1;
    }
    Card* current = deck->top;
    while (current != NULL) {
        fprintf(file, "%c%c\n", current->rank, current->suit);
        current = current->next;
    }

    fclose(file);
    return 0;
}


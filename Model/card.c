#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char suits[] = {'h', 'c', 'd', 's'};
const char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'D', 'K'};

Card* createCard(char rank, char suit, int visible) {
    Card* newCard = malloc(sizeof(Card));
    if (!newCard) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newCard->rank = rank;
    newCard->suit = suit;
    newCard->visible = visible;
    newCard->next = NULL;
    newCard->previous = NULL;
    return newCard;
}

Card* createDeckShuffled() {
    Card* allCards[52];
    int index = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            allCards[index] = createCard(ranks[j], suits[i], 1);
            index++;
        }
    }

    for (int i = 0; i < 51; i++) {
        int j = rand() % (1 + i);
        Card* temp = allCards[i];
        allCards[i] = allCards[j];
        allCards[j] = temp;
    }

    for (int i = 0; i < 51; i++) {
        allCards[i]->next = allCards[i + 1];
    }

    allCards[51]->next = NULL;

    return allCards[0];
}



void freeDeck(Card* firstCard) {
    Card* current = firstCard;
    while (current != NULL) {
        Card* nextCard = current->next;
        free(current);
        current = nextCard;
    }
}



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



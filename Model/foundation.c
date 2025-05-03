//
// Created by alfre on 01-05-2025.
//

#include "foundation.h"
#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "deck.h"


#include <stdio.h>
#include <stdlib.h>

Foundation* createFoundation(Foundation* foundation) {
    Foundation* newFoundation = malloc(sizeof(Foundation));
    if (!newFoundation) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newFoundation->bottom = NULL;
    newFoundation->top = NULL;
    newFoundation->size = 0;
    newFoundation->suit = ' ';
    return newFoundation;
}

void addCardFoundation(Card* card, Foundation* foundation) {
    Card *newCard = createCard(card->rank, card->suit, 1);
    if (foundation->size == 0) {
        foundation->top = newCard;
        foundation->bottom = newCard;
        foundation->size = 1;
        foundation->suit = card->suit;
        newCard->next = NULL;
        newCard->previous = NULL;
    } else {
        newCard->next = foundation->top;
        foundation->top->previous = newCard;
        foundation->top = newCard;
        newCard->previous = NULL;
        foundation->suit = card->suit;
        foundation->size++;
    }
}

Card* getTopCardFoundation(Foundation* foundation) {
    return foundation->top;
}
int getSize(Foundation* foundation) {
    return foundation->size;
}

Card* removeCardFoundation(Foundation* foundation) {

}
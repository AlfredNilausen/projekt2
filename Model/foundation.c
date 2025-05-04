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

    card->next = NULL;
    card->previous = NULL;
    card->visible =1;

    if (foundation->size == 0) {
        foundation->top = foundation->bottom = card;


    } else {
        card->next = foundation->top;
        foundation->top->previous = card;
        foundation->top = card;
    }

        foundation->suit = card->suit;
        foundation->size++;
    }


Card* getTopCardFoundation(Foundation* foundation) {
    return foundation->top;
}
int getSize(Foundation* foundation) {
    return foundation->size;
}

Card* removeCardFoundation(Foundation* foundation) {

    if (foundation->size == 0 || foundation->top == NULL) {
        return NULL;
    }
    Card* removed = foundation->top;
    foundation->top = removed->next;

    if (foundation->top) {
        foundation->top->previous = NULL;
    } else {
        foundation->bottom = NULL;
    }
    removed->next = NULL;
    removed->previous = NULL;
    foundation->size--;

    return removed;
}
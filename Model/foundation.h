//
// Created by alfre on 01-05-2025.
//

#ifndef FOUNDATION_H
#define FOUNDATION_H

#include "../Model/deck.h"
#include "../Model/card.h"

typedef struct Foundation {
    Card* top;
    Card* bottom;
    int size;
    char suit;
} Foundation;

Foundation* createFoundation();
void freeFoundations();
Card* getTopCardFoundation(Foundation* foundation);
int getSize(Foundation* foundation);
void addCardFoundation(Card* card, Foundation* foundation);
Card* removeCardFoundation(Foundation* foundation);


#endif //FOUNDATION_H

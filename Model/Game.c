//
// Created by alfre on 01-05-2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "foundation.h"
#include "../Model/card.h"
#include "../Model/columns.h"
#include "../Model/deck.h"
#include "../View/BoardView.h"
#include "../Controller/GameController.h"

Deck currentDeck;
Column columns[7];
Foundation foundations[4];

Column* getColumn(int i) {
    return &columns[i];
}
Foundation* getFoundation(int i) {
    return &foundations[i];
}

Foundation * createFoundation(void);

void createFoundations() {
    for (int i = 0; i < 4; i++) {
        foundations[i] = *createFoundation();
    }
}
void createColumns() {
    for (int i = 0; i < 7; i++) {
        columns[i] = *createColumn();
    }
}
void setColumn(int i, Column column) {
    columns[i] = column;
}
void setFoundation(int i, Foundation foundation) {
    foundations[i] = foundation;
}
Deck *getDeck() {
    return &currentDeck;
}
void setDeck(Deck d) {
    currentDeck = d;
}

int biggestColumn() {
    int biggest = 0;
    for (int i = 0; i < 7; i++) {
        if (columns[i].size > biggest) {
            biggest = columns[i].size;
        }
    }
    return biggest;
}

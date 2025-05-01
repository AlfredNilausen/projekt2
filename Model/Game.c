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
#include "../Controller/GameController.h"

Deck currentDeck;
Column columns[7];

Column* getColumn(int i) {
    return &columns[i];
}
void createColumns() {
    for (int i = 0; i < 7; i++) {
        columns[i] = *createColumn();
    }
}
void setColumn(int i, Column column) {
    columns[i] = column;
}
Deck *getDeck() {
    return &currentDeck;
}
void setDeck(Deck d) {
    currentDeck = d;
}


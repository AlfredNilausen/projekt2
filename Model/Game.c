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

Deck getDeck() {
    return currentDeck;
}
void setDeck(Deck d) {
    currentDeck = d;
}


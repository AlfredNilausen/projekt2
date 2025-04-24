#ifndef DECK_H
#define DECK_H

#include "../Model/card.h"
#include "../Model/columns.h"

typedef struct Deck {
  Card* top;
  Card* bottom;
  int size;
} Deck;


void addCard(Card* card, Deck* deck);
Deck createDeck();

#endif
#ifndef DECK_H
#define DECK_H

#include "../Model/card.h"
#include "../Model/columns.h"

typedef struct Deck {
  Card* top;
  Card* bottom;
  int size;
} Deck;


int addCard(Card* card, Deck* deck);

Card* getTopCard(Deck* deck);
Deck createDeck();
void printDeck(Deck* deck);

#endif
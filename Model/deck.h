#ifndef DECK_H
#define DECK_H

#include "../Model/card.h"
#include "../Model/columns.h"

typedef struct Deck {
  Card* top;
  Card* bottom;
  int size;
} Deck;


int addCardTop(Card* card, Deck* deck);
int addCardBottom(Card* card, Deck* deck);

Deck splitDeck(Deck *deck, int size);
Deck randomShuffle(Deck *deck);
Card* removeCardFromDeck(Deck* deck);
Card* getTopCard(Deck* deck);
Deck createDeck();
void printDeck(Deck* deck);
void freeDeck();

#endif
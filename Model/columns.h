#ifndef COLUMNS_H
#define COLUMNS_H

#include "../Model/deck.h"
#include "../Model/card.h"
typedef struct Deck Deck;
typedef struct Column {
    Card* top;
    Card* bottom;
    int size;
} Column;

Column* createColumn();
Card* getCardCol(int index, Column* column);
int dealcardstocolumn(Deck* deck);
int playdealcard(Deck* deck);
void addCardColumn(Card* card, Column* column, int visible);
Card* removeCardColumn(Column* column);
//void dealToColumns(Card* shuffledDeck, Card* columns[7]);
void printColumn(Column* column);
void freeColumns(Card* columns[7]);

#endif // COLUMNS_H


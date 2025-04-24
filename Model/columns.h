#ifndef COLUMNS_H
#define COLUMNS_H

#include "../Model/card.h"

void dealToColumns(Card* shuffledDeck, Card* columns[7]);
void printColumns(Card* columns[7]);
void freeColumns(Card* columns[7]);

#endif // COLUMNS_H


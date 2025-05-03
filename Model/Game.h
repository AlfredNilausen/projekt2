//
// Created by alfre on 01-05-2025.
//

#ifndef GAME_H
#define GAME_H
#include "deck.h"

Column* getColumn(int i);
void setColumn(int i, Column* column);
void createColumns();
Deck *getDeck();
int isColumnthere();
int biggestColumn();
void setDeck(Deck);
#endif //GAME_H

//
// Created by Magnus Fehrmann on 10/04/2025.
//

#ifndef CARD_H
#define CARD_H

// Struct definition using typedef
typedef struct Card {
    char rank;
    char suit;
    int visible;
    struct Card* previous;
    struct Card* next;
} Card;
// Function declarations
Card* createCard(char rank, char suit);
Card* createDeckShuffled();
void printDeck(Card* firstCard);
void freeDeck(Card* firstCard);

#endif // CARD_H

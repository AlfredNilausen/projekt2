
#include "../Model/columns.h"
#include "../Model/card.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Model/deck.h"

int addCard(Card* card, Deck* deck) {

  Card* current = deck->top;
  while (current != NULL) {
    if (current->rank == card->rank && current->suit == card->suit) {
      return -1;
    }
    current = current->next;
  }

  card->next = NULL;
  card->previous = NULL;

  if (deck->size == 0) {
    deck->top = card;
    deck->bottom = card;
    card->previous = NULL;
    card->next = NULL;
  } else {
    deck->bottom->next = card;
    card->previous = deck->bottom;
    deck->bottom = card;
    card->next = NULL;

  }
  deck->size++;
  return 1;
}

Deck createDeck() {
  Deck* deck = (Deck*) malloc(sizeof(Deck));
  deck-> size = 0;
  deck->top = NULL;
  deck->bottom = NULL;

  return *deck;
}
Card* getTopCard(Deck* deck) {
  return deck->top;
}

void printDeck(Deck* deck) {
  Card* current = getTopCard(deck);
  printf("\n");
  while (current != NULL) {
    printf("%c of %c\n", current->rank, current->suit);
    current = current->next;
  }
}

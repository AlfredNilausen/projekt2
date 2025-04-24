
#include "../Model/columns.h"
#include "../Model/card.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Model/deck.h"

void addCard(Card* card, Deck* deck) {

  Card* current = deck->top;
  while (current != NULL) {
    if (current == card) {
      return;
    }
    current = current->next;
  }

  card->next = NULL;
  card->previous = NULL;

  if (deck->size == 0) {
    deck->top = card;
    deck->bottom = card;
  } else {
    deck->bottom->next = card;
    card->previous = deck->bottom;
    deck->bottom = card;
  }
  deck->size++;
}

Deck createDeck() {
  Deck* deck = (Deck*) malloc(sizeof(Deck));
  deck->top = NULL;
  deck->bottom = NULL;
  return *deck;
}

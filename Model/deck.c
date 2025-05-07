
#include "../Model/columns.h"
#include "../Model/card.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Model/deck.h"

#include "Game.h"

int addCardTop(Card* card, Deck* deck) {

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
    deck->top->previous = card;
    card->next = deck->top;
    deck->top = card;
    card->previous = NULL;

  }
  deck->size++;
  return 1;
}

int addCard (Card* card, Deck* deck) {
  Card* current = deck->top;
  while (current != NULL) {
    if (current->rank == card->rank && current->suit == card->suit) {
      return -1;
    }
    current = current->next;
  }

  if (deck->size == 52) {
    return -1;
  } else if (deck->size == 0) {
    deck->top = card;
    deck->bottom = card;
    card->previous = NULL;
    card->next = NULL;
  } else {

  }

  deck->size++;
  return 1;
}

int addCardBottom(Card* card, Deck* deck) {

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

Card* removeCardFromDeck(Deck* deck) {
  if (deck == NULL || deck->top == NULL) {
    return NULL; // Empty deck
  }

  Card* removedCard = deck->top;

  // Update deck top to next card
  deck->top = removedCard->next;

  if (deck->top != NULL) {
    deck->top->previous = NULL;
  } else {
    deck->bottom = NULL; // Deck is now empty
  }

  removedCard->next = NULL;
  removedCard->previous = NULL;
  deck->size--;

  return removedCard;
}



Deck splitDeck(Deck *deck, int size) {
  if (size == 0) {
     size = rand() % (51) + 1;
  }

  Deck newDeck = createDeck();
  Deck resultDeck = createDeck();
  int total = 0;
  for (int i = 0; i < size; i++) {
    addCardBottom(removeCardFromDeck(deck), &newDeck);
  }
  
  while (deck->size > 0 && newDeck.size > 0) {
    if (deck->size > 0) {
      addCardTop(removeCardFromDeck(deck), &resultDeck);
      total++;
    }
    if (newDeck.size > 0) {
      addCardTop(removeCardFromDeck(&newDeck), &resultDeck);
      total++;
    }
  }
  Deck* leftDeck;
  if (deck->size == 0) {
    leftDeck = &newDeck;
  } else {
    leftDeck = deck;
  }
  while (resultDeck.size != 52) {
    addCardBottom(removeCardFromDeck(leftDeck), &resultDeck);
  }
  return resultDeck;
}

Deck randomShuffle(Deck* deck) {
  Deck tempDeck = createDeck();


  while (deck->size > 0) {
    addCardTop(removeCardFromDeck(deck), &tempDeck);
  }


  for (int i = 0; i < 52; i++) {
    Card* card = removeCardFromDeck(&tempDeck);
    if (deck->size == 0) {
      addCardTop(card, deck);
      continue;
    }

    int position = rand() % (deck->size + 1);  //


    if (position == 0) {
      addCardTop(card, deck);
    }

    else if (position == deck->size) {
      addCardBottom(card, deck);
    }

    else {
      Card* current = deck->top;
      for (int j = 0; j < position - 1; j++) {
        current = current->next;
      }

      card->next = current->next;
      card->previous = current;
      current->next->previous = card;
      current->next = card;
      deck->size++;
    }
  }

  return *deck;
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
void freeDeck() {
    Deck* current = getDeck();

    if (current) {
      Card* currentCard = current->top;
      while (currentCard != NULL) {
        Card* next = currentCard->next;
        free(currentCard);
        currentCard = next;
      }
      current->top = NULL;
      current->bottom = NULL;
      current->size = 0;
    }
    }


#include "columns.h"
#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "deck.h"


void printColumn(Column* column) {
    Card* current = column->top;
    while (current != NULL) {
        if (current->visible) {
            printf("  %c of %c \n", current->rank, current->suit);
        }else {
            printf("  XX (Invisble)\n");
        }
        current = current->next;
    }

}

void freeColumns() {
    for (int i = 0; i < 7; i++) {
        Column* current = getColumn(i);
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
}

Column* createColumn() {
    Column* newColumn = malloc(sizeof(Column));
    if (!newColumn) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newColumn->bottom = NULL;
    newColumn->top = NULL;
    newColumn->size = 0;
    return newColumn;
}

void addCardColumn(Card* card, Column* column, int visible) {
    Card *newCard = createCard(card->rank, card->suit, visible);
    if (column->size == 0) {
        column->top = newCard;
        column->bottom = newCard;
        column->size = 1;
        newCard->next = NULL;
        newCard->previous = NULL;
    } else {
        newCard->previous = column->bottom;
        column->bottom->next = newCard;
        column->bottom = newCard;
        newCard->next = NULL;
        column->size++;

    }
}
Card* removeCardColumn(Column* column) {
    if (column->size == 1) {
        Card removedtopofcolumn = *column->top;
        column->top = NULL;
        column->bottom = NULL;
        column->size = 0;
        return &removedtopofcolumn;
    } else {
        Card removedtopofcolumn = *column->top;
        column->top = removedtopofcolumn.previous;
        column->size--;
        column->top->next = NULL;
        return &removedtopofcolumn;
    }
}

int dealcardstocolumn(Deck* deck, int visible) {
    freeColumns();
    createColumns();
    Card* current = getTopCard(deck);
    int total = 0;
    int count = 0;
    while (current != NULL) {
        int adding = total % 7;
        Card* newCard = createCard(current->rank, current->suit, visible);
        addCardColumn(newCard, getColumn(adding), visible);
        current = current->next;
        total++;
        count++;
    }
    return total;
}
Card* getCardCol(int index, Column* column) {
    Card *current = column->top;
    for (int i = 0; i < index; i++) {
        current = current->next;
        if (current == NULL) {
            return current;
        }
    }
    return current;
}

int playdealcard(Deck* deck) {
    createColumns();
    Card* current = getTopCard(deck);
    int total = 0;
    int count = 0;
    int visible = 1;
    addCardColumn(current, getColumn(0), 1);
    current = current->next;
    for (int j = 0; j < 6; j++) {
        for (int i = 1; i < 7; i++) {
            if (j < i) {
                visible = -1;
            }
            addCardColumn(current, getColumn(i), visible);
            visible = 1;
            current = current->next;
        }
    }
    for (int j = 0; j < 5; j++) {
        for (int i = j+2; i < 7; i++) {
            addCardColumn(current, getColumn(i), 1);
            current = current->next;
        }
    }



    return total;
}
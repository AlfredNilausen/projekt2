#include "columns.h"
#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "deck.h"
/*
void dealToColumns(Card* shuffledDeck, Card* columns[7]) {
    Card* current = shuffledDeck;

    for (int col = 0; col < 7; col++) {
        int faceDown = col;
        int faceUp = (col == 0) ? 1 : 5;
        int total = faceDown + faceUp;

        Card* last = NULL;

        for (int i = 0; i < total; i++) {
            Card* next = current->next;
            current->next = NULL;

            current->visible = (i >= faceDown) ? 1 : 0;

            if (columns[col] == NULL) {
                columns[col] = current;
                last = current;
            } else {
                last->next = current;
                last = current;
            }

            current = next;
        }
    }
}
*/

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

void freeColumns(Card* columns[7]) {
    for (int i = 0; i < 7; i++) {
        Card* current = columns[i];
        while (current != NULL) {
            Card* next = current->next;
            free(current);
            current = next;
        }
        columns[i] = NULL;
    }
}

Column createColumn() {
    Column* newColumn = malloc(sizeof(Column));
    if (!newColumn) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newColumn->bottom = NULL;
    newColumn->top = NULL;
    newColumn->size = 0;
    return *newColumn;
}

int addCardColumn(Card* card, Column* column) {
    if (column->size == 0) {
        column->top = card;
        column->bottom = card;
        column->size = 1;
        card->next = NULL;
        card->previous = NULL;
        return 1;
    } else {
        card->next = column->top;
        column->top->previous = card;
        column->top = card;
        card->previous = NULL;
        column->size++;
        return 1;
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

int dealcardstocolumn(Deck* deck) {
    printf("Top card: %c of %c\n", deck->top->rank, deck->top->suit);
    if (deck->top->next)
        printf("Next card: %c of %c\n", deck->top->next->rank, deck->top->next->suit);
    else
        printf("Next card is NULL\n");
    printf("Dealing cards to columns...\n");
    Card* current = deck->top;
    int total = 0;
    int count = 0;
    while (current != NULL) {
        int adding = total % 7;
        if (getColumn(adding) == NULL) {
            printf("Column %d is NULL!\n", adding);
        }
        printf("Dealing %c of %c to column %d\n", current->rank, current->suit, adding);
        addCardColumn(current, getColumn(adding));
        total++;
        current = current->next;
        count++;
    }
    printf("Printed %d cards\n", count);
    printf("Total cards dealt: %d\n", total);
    return total;
}

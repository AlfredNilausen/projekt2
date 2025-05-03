// MoveLogic.c
#include "MoveLogic.h"
#include "../Model/card.h"
#include "../Model/columns.h"
#include "../Model/Game.h"
#include <string.h>
#include <ctype.h>

int rankToValue(char rank) {
    if (rank == 'A') return 1;
    if (rank == 'T') return 10;
    if (rank == 'J') return 11;
    if (rank == 'Q') return 12;
    if (rank == 'K') return 13;
    if (rank >= '2' && rank <= '9') return rank - '0';
    return -1;
}



int handleMoveCommand(const char* command) {
    char from[10], to[10];
    const char* arrow = strstr(command, "->");
    if (!arrow) return 0;

    size_t len = arrow - command;
    strncpy(from, command, len);
    from[len] = '\0';
    strcpy(to, arrow + 2);

    if (toupper(from[0]) != 'C' || toupper(to[0]) != 'C') return 0;

    int fromColIndex = from[1] - '1';
    int toColIndex = to[1] - '1';
    Column* fromCol = getColumn(fromColIndex);
    Column* toCol = getColumn(toColIndex);
    if (!fromCol || !toCol) return 0;

    Card* movingCard = NULL;

    if (strchr(from, ':')) {
        char rank = from[3];
        char suit = from[4];
        Card* current = fromCol->top;
        while (current != NULL) {
            if (current->rank == rank && current->suit == suit && current->visible) {
                movingCard = current;
                break;
            }
            current = current->next;
        }
    } else {
        movingCard = fromCol->bottom;
        if (!movingCard || !movingCard->visible) return 0;
    }

    if (!movingCard) return 0;

    int moveCount = 0;
    Card* temp = movingCard;
    while (temp != NULL) {
        moveCount++;
        temp = temp->next;
    }

    Card* dest = toCol->bottom;
    int sr = rankToValue(movingCard->rank);
    int dr = dest ? rankToValue(dest->rank) : -1;
    int valid = (!dest) || ((sr == dr - 1));

    if (!valid) return 0;


    if (movingCard == fromCol->top) {
        fromCol->top = NULL;
        fromCol->bottom = NULL;
        fromCol->size = 0;
    } else {
        if (movingCard->previous) {
            movingCard->previous->next = NULL;
            fromCol->bottom = movingCard->previous;
            fromCol->size -= moveCount;
        }
    }
    if (fromCol->bottom && fromCol->bottom->visible < 0) {
        fromCol->bottom->visible = 1;
    }


    if (toCol->size == 0) {
        toCol->top = movingCard;
        toCol->bottom = movingCard;
        movingCard->previous = NULL;
    } else {
        toCol->bottom->next = movingCard;
        movingCard->previous = toCol->bottom;

    }

    while (movingCard->next) movingCard = movingCard->next;
    toCol->bottom = movingCard;
    toCol->size += moveCount;

    return 1;
}

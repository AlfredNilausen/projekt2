// MoveLogic.c
#include "MoveLogic.h"
#include "../Model/card.h"
#include "../Model/columns.h"
#include "../Model/Game.h"
#include "../Model/foundation.h"
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

    strncpy(from, command, arrow - command);
    from[arrow - command] = '\0';
    strcpy(to, arrow + 2);
    if (strlen(from) < 2 || strlen(to) < 2 || !isdigit(from[1]) || !isdigit(to[1])) {
        return 0;
    }


    char fromType = toupper(from[0]);
    char toType = toupper(to[0]);

    if (fromType == 'C' && toType == 'F') {
        int fromColIndex = from[1] - '1';
        int toFIndex = to[1] - '1';
        if (fromColIndex < 0 || toFIndex < 0 || fromColIndex > 6 || toFIndex > 3) {
            return 0;
        }
        Column* fromCol = getColumn(fromColIndex);
        Foundation* toF = getFoundation(toFIndex);
        if (!fromCol || !toF) return 0;

        Card* card = fromCol->bottom;
        if (!card) return -1;
        if (!card->visible) return -6;

        int sr = rankToValue(card->rank);
        Card* topF = getTopCardFoundation(toF);
        int fr = topF ? rankToValue(topF->rank) : 0;

        if ((toF->size == 0 && sr == 1) || (topF && sr == fr + 1 && card->suit == toF->suit)) {
            card = removeCardColumn(fromCol); // safely detach
            addCardFoundation(card, toF);
            if (fromCol->bottom && fromCol->bottom->visible < 0)
                fromCol->bottom->visible = 1;
            return 1;
        }

        return -7;
    }

    if (fromType == 'F' && toType == 'C') {
        int fromFIndex = from[1] - '1';
        int toColIndex = to[1] - '1';
        if (fromFIndex < 0 || toColIndex < 0 || fromFIndex > 3 || toColIndex > 6) {
            return 0;
        }
        Foundation* fromF = getFoundation(fromFIndex);
        Column* toCol = getColumn(toColIndex);
        if (!fromF || !toCol) return 0;

        Card* card = getTopCardFoundation(fromF);
        if (!card) return -8;

        Card* dest = toCol->bottom;
        int sr = rankToValue(card->rank);
        int dr = dest ? rankToValue(dest->rank) : -1;

        if (!dest || sr == dr - 1) {
            removeCardFoundation(fromF);
            attachCardColumn(card, toCol);
            return 1;
        }
        return -2;
    }

    if (fromType == 'C' && toType == 'C') {
        int fromColIndex = from[1] - '1';
        int toColIndex = to[1] - '1';
        if (fromColIndex < 0 || toColIndex < 0 || fromColIndex > 6 || toColIndex > 6) {
            return 0;
        }
        Column* fromCol = getColumn(fromColIndex);
        Column* toCol = getColumn(toColIndex);
        if (!fromCol || !toCol) return 0;

        Card* movingCard = NULL;

        if (strchr(from, ':')) {
            char rank = from[3];
            char suit = from[4];
            Card* current = fromCol->top;
            while (current) {
                if (current->rank == rank && current->suit == suit) {
                    if (current->visible > 0) {
                        movingCard = current;
                        break;
                    } else {
                        return -6;
                    }
                }
                current = current->next;
            }
        } else {
            movingCard = fromCol->bottom;
            if (!movingCard) return -1;
            if (!movingCard->visible) return -6;
        }

        if (!movingCard) return -4;

        int moveCount = 0;
        Card* temp = movingCard;
        while (temp) {
            moveCount++;
            temp = temp->next;
        }

        Card* dest = toCol->bottom;
        int sr = rankToValue(movingCard->rank);
        int dr = dest ? rankToValue(dest->rank) : -1;

        if (!dest || sr == dr - 1) {
            if (movingCard == fromCol->top) {
                fromCol->top = NULL;
                fromCol->bottom = NULL;
                fromCol->size = 0;
            } else {
                movingCard->previous->next = NULL;
                fromCol->bottom = movingCard->previous;
                fromCol->size -= moveCount;
            }
            if (fromCol->bottom && fromCol->bottom->visible < 0)
                fromCol->bottom->visible = 1;

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
    }

    return -5;
}

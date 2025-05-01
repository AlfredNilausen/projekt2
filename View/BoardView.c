//
// Created by alfre on 24-04-2025.
//

#include "BoardView.h"

#include <stdio.h>

#include "../Model/Game.h"

void printLD(Deck* deck) {
    printf("Please enter a keyboard input:\n");
}
void printSW(Deck* deck) {
    printf("Please enter a SW input:\n");
}
void printBoard() {
    int biggest = biggestColumn();
    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    for (int j = 0; j < biggest; j++) {
        for (int i = 0; i < 7; i++) {
            Column *printColumn = getColumn(i);
            Card *printCard = getCardCol(j, printColumn);
            if (printCard != NULL) {
                if (printCard->visible > 0) {
                    printf("%c%c\t",printCard->rank, printCard->suit);
                } else {
                    printf("[]\t");
                }
            } else {
                printf("  \t");
            }
        }
        printf("\n");
    }

    if (isColumnthere() == 0) {
        printf("\t\t\t\t\t\t\t\t\\[]\tF1n\n\n");
    }
}
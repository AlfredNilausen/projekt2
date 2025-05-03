//
// Created by alfre on 24-04-2025.
//

#include "BoardView.h"

#include <stdio.h>

#include "../Model/foundation.h"
#include "../Model/Game.h"

void printLD(Deck* deck) {
    printf("Please enter a keyboard input:\n");
}
void printSW(Deck* deck) {
    printf("Please enter a SW input:\n");
}
void printBoard() {
    int start = 7;
    int biggest = biggestColumn();
    int total = 0;
    if (biggest > start) {
        total = biggest;
    } else {
        total = start;
    }
    printf("\nC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
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
        if (j % 2 == 0 && j < start) {
            Card* foundationCard = getTopCardFoundation(getFoundation(j / 2));
            printf("\t");
            if (foundationCard != NULL) {
                printf("%c%c\t",foundationCard->rank, foundationCard->suit);
            } else {
                printf("[]\t");
            }
            printf("F%d", (j / 2) + 1);
        }
        printf("\n");
    }
    if (isColumnthere() == 0) {
        printf("\t\t\t\t\t\t\t\t\\[]\tF1n\n\n");
    }
    //printf("size of c1: %d \n size of c2: %d \n size of c3 %d \n size of c4: %d \n size of c5: %d \n size of c6: %d \n size of c7: %d \n ", getColumn(0)->size, getColumn(1)->size, getColumn(2)->size, getColumn(3)->size, getColumn(4)->size, getColumn(5)->size, getColumn(6)->size);
}
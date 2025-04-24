#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Model/card.h"
#include "../Model/columns.h"


int main(void) {
    Card* deck = createDeckShuffled();
    Card* columns[7] = {NULL};
    dealToColumns(deck, columns);
    printColumns(columns);
    freeColumns(columns);
    return 0;
}
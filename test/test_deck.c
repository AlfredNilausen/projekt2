#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Model/card.h"
#include "../Model/deck.h"

int main() {
    srand(time(NULL));


    Card* deck = createDeckShuffled();


    printf("Deck after shuffle:\n");
    printDeck(deck);


    saveDeckToFile(deck, "my_test_deck.txt");


    freeDeck(deck);

    return 0;
}

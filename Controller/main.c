#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Model/card.h"
#include "../Model/columns.h"
#include "../Model/deck.h"
#include "../View/BoardView.h"
#include "../Controller/GameController.h"
#include "../Model/Game.h"
#include "MoveLogic.h"


#define MAX_INPUT 100

int main(void) {
    srand(time(NULL));
    setDeck(createDeck());
    createColumns();

    char input[MAX_INPUT];
    char lastCommand[MAX_INPUT] = "";
    char message[MAX_INPUT] = "No game started yet.";

    int playing = 0;

    printf("YUKON - TEXT MODE\n");

    while (1) {
        // STARTUP PHASE PROMPT
        printf("\nLAST Command: %s\n", lastCommand);
        printf("Message: %s\n", message);
        printf("INPUT > ");

        if (!fgets(input, sizeof(input), stdin)) {
            strcpy(message, "Error reading input");
            continue;
        }

        input[strcspn(input, "\n")] = 0;
        strcpy(lastCommand, input);

        // QQ: Quit entire program
        if (strcmp(input, "QQ") == 0) {
            printf("\nExiting Yukon. Thanks for playing!\n");
            break;
        }

        // LD <filename>
        if (strncmp(input, "LD", 2) == 0) {
            int tal = LD(input + 3);
            if (tal == 52) {
                strcpy(message, "OK");
            } else {
                char* error = errorcode(tal);
                strcpy(message, error);
            }


           //SL: Splitdeck and assemble again
        } else if (strncmp(input, "SL", 2) == 0) {
            int SLnumber = atoi(input + 3);
                if (getDeck()->size == 52) {
                    if (strlen(input) != 2) {
                        if (SLnumber < 52 && SLnumber > 0) {
                            setDeck(splitDeck(getDeck(), SLnumber));
                            strcpy(message, "OK");
                        } else
                            strcpy(message, "Error: input not between 1 and 52");
                    } else {
                        setDeck(splitDeck(getDeck(), SLnumber));
                        strcpy(message, "OK");
                    }
                } else {
                    strcpy(message, "Error no deck loaded");
                }

            // SD: Saves the deck to a file
        } else if (strncmp(input, "SD", 2) == 0) {
            if (getDeck()->size == 52) {
                int check = saveDeckToFile(getDeck(), input + 3);
                if (check == 0) {
                    strcpy(message, "OK");
                } else {
                    strcpy(message, "Error: Something went wrong saving deck");
                }
            } else {
                strcpy(message, "Error: No deck loaded");
            }


            // RD: Randomly takes one card
        } else if (strncmp(input, "SR", 2) == 0) {
            if (getDeck()->size == 52) {
                setDeck(randomShuffle(getDeck()));
                strcpy(message, "OK");
            } else {
                strcpy(message, "Error: No deck loaded");
            }

            // SW: Show deck/columns
        } else if (strcmp(input, "SW") == 0) {
            //printDeck(getDeck());
            if (getDeck() && getDeck()->size == 52) {
                dealcardstocolumn(getDeck(), 1);
                printf("\n");
                printBoard();
                strcpy(message, "OK");
            } else {
                strcpy(message, "Error: No deck loaded");
            }

        // P: Start game
        } else if (strcmp(input, "P") == 0) {
            if (getDeck() && getDeck()->size == 52) {
                printf("\n");
                playdealcard(getDeck());
                printBoard();
                playing = 1;
                printf("\nGame started!");


                // -------- PLAY PHASE --------
                while (playing) {
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;


                    // QQ: Quit entire program
                    if (strcmp(input, "QQ") == 0) {
                        printf("\nExiting Yukon. Thanks for playing!\n");
                        freeDeck(getDeck());
                        return 0;
                    }

                    // Q: Quit game, return to STARTUP
                    else if (strcmp(input, "Q") == 0) {
                        strcpy(message, "Game quit. Returning to STARTUP.");
                        createColumns();  // reset columns for new game
                        break;
                    }

                    // SW: Show columns
                    else if (strcmp(input, "SW") == 0) {
                        for (int i = 0; i < 7; i++) {
                            printf("Column %d:\n", i + 1);
                            printColumn(getColumn(i));
                        }
                    }
                    else if (strchr(input, '-') != NULL) {
                        int success = handleMoveCommand(input);
                        if (success) {
                            printf("Move is valid\n");
                            printBoard();
                        }
                        else {
                            printf("Invalid move\n");
                        }
                    }


                    else {
                        printf("Unknown in-game command: %s\n", input);
                    }
                }

            } else {
                strcpy(message, "No deck loaded to play");
            }

        // Unknown command in STARTUP
        } else {
            strcpy(message, "Unknown command");
        }
    }

    // Final cleanup
    freeDeck(getDeck());
    return 0;
}

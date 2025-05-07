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
            if (strcmp(input, "QQ") == 0 && strlen(input) == 2) {
                freeColumns();
                freeDeck(getDeck());
                freeFoundations();
                printf("\nExiting Yukon. Thanks for playing!\n");
                break;
            }

            // LD <filename>
            else if (strncmp(input, "LD", 2) == 0) {
                if (playing == 0) {
                    int tal = LD(input + 3);
                    if (tal == 52) {
                        strcpy(message, "OK");
                    } else {
                        char* error = errorcode(tal);
                        strcpy(message, error);
                    }
                } else {
                    strcpy(message, "Command not available in the PLAY phase.");
                }



                //SL: Splitdeck and assemble again
            } else if (strncmp(input, "SL", 2) == 0) {
                if (playing == 0) {
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
                } else {
                    strcpy(message, "Command not available in the PLAY phase.");
                }


                // SD: Saves the deck to a file
            } else if (strncmp(input, "SD", 2) == 0) {
                if (playing == 0) {
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
                } else {
                    strcpy(message, "Command not available in the PLAY phase.");
                }


                // SR: Randomly takes one card
            }
            else if (strncmp(input, "SR", 2) == 0 && strlen(input) == 2) {
                if (playing == 0) {
                    if (getDeck()->size == 52) {
                        setDeck(randomShuffle(getDeck()));
                        strcpy(message, "OK");
                    } else {
                        strcpy(message, "Error: No deck loaded");
                    }
                } else {
                    strcpy(message, "Command not available in the PLAY phase.");
                }


                // SW: Show deck/columns
            } else if (strcmp(input, "SW") == 0 && strlen(input) == 2) {
                if (playing == 0) {
                    //printDeck(getDeck());
                    if (getDeck() && getDeck()->size == 52) {
                        dealcardstocolumn(getDeck(), 1);
                        printf("\n");
                        printBoard();
                        strcpy(message, "OK");
                    } else {
                        strcpy(message, "Error: No deck loaded");
                    }
                } else {
                    strcpy(message, "Command not available in the PLAY phase.");
                }


                // P: Start game
            } else if (strcmp(input, "P") == 0 && strlen(input) == 1) {
                if (playing == 0) {
                    if (getDeck() && getDeck()->size == 52) {
                        printf("\n");
                        playdealcard(getDeck());
                        printBoard();
                        playing = 1;
                        //printf("\nGame started!");
                    } else {
                        strcpy(message, "No deck loaded to play");
                    }
                } else {
                    strcpy(message, "Command not available in the PLAY phase.");
                }
            }


            // -------- PLAY PHASE --------
            // Q: Quit game, return to STARTUP
            else if (strcmp(input, "Q") == 0 && strlen(input) == 1) {
                if (playing == 1) {
                    strcpy(message, "Game quit. Returning to STARTUP.");
                    createColumns();  // reset columns for new game
                    playing = 0;
                } else {
                    strcpy(message, "Command not available in the STARTUP phase.");
                }
            }
            /*
            // SW: Show columns
            else if (strcmp(input, "SW") == 0 && playing == 1 && strlen(input) == 2) {
                    for (int i = 0; i < 7; i++) {
                        printf("Column %d:\n", i + 1);
                        printColumn(getColumn(i));
                    }
            }
            */
            else if (strchr(input, '-') != NULL) {
                if (playing == 1) {
                    int success = handleMoveCommand(input);
                    if (success > 0) {
                        printf("Move is valid\n");
                        printBoard();
                        strcpy(message, "OK");
                    } else {
                        strcpy(message, errorMove(success));
                    }
                } else {
                    strcpy(message, "Command not available in the STARTUP phase.");
                }

            } else {
                char unknown[MAX_INPUT] = "Unknown in-game command: \"";
                strcat(unknown, input);
                strcat(unknown, "\"");
                strcpy(message, unknown);
            }
    }
}

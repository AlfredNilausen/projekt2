//
// Created by Magnus Fehrmann on 05/05/2025.
//

#include "raylib.h"
#include <stdbool.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "gui.h"
#include "../Model/Game.h"
#include "../Model/columns.h"
#include "../Model/foundation.h"
#include "../Model/card.h"
#include "../Controller/GameController.h"
#include "../Controller/MoveLogic.h"
#include "../View/BoardView.h"
#include "../Model/deck.h"
#include <unistd.h>


#define CARD_WIDTH 60
#define CARD_HEIGHT 90
#define CARD_SPACING 20
#define START_X 50
#define START_Y 150
#define FOUNDATION_Y 30

static char message[128] = "No game started yet.";
static int gameStarted = 0;

void InitGUI(void) {
    InitWindow(1000, 800, "Yukon Solitaire");
    SetTargetFPS(60);

    createColumns();  // initialize columns first

    int result = LD("../filename.txt");

    if (result != 52) {
        TraceLog(LOG_ERROR, TextFormat("LD failed: %s", errorcode(result)));
        return; // abort init to prevent segfault
    }

    char cwd[512];
    getcwd(cwd, sizeof(cwd));
    TraceLog(LOG_INFO, TextFormat("Working directory: %s", cwd));
    printf("Working directory: %s\n", cwd);

}




void UpdateGUI(void) {

    BeginDrawing();
    ClearBackground(DARKGREEN);

    Deck* d = getDeck();
    if (!d) {
        DrawText("ERROR: Deck is NULL", 20, 20, 20, RED);
        EndDrawing();
        return;
    }

    DrawText(TextFormat("Deck size: %d", d->size), 20, 20, 20, WHITE);


    DrawText("Yukon - GUI Mode", 20, 20, 30, WHITE);
    DrawText(TextFormat("Message: %s", message), 20, 60, 20, WHITE);

    Rectangle btnLD = { 20, 100, 100, 30 };
    Rectangle btnSL = { 140, 100, 100, 30 };
    Rectangle btnSR = { 260, 100, 100, 30 };
    Rectangle btnSW = { 380, 100, 100, 30 };
    Rectangle btnP  = { 500, 100, 100, 30 };
    Rectangle btnQ  = { 620, 100, 100, 30 };

    if (GuiButton(btnLD, "LD")) {
        int status = LD("../filename.txt");
        strcpy(message, status == 52 ? "Deck loaded from filename.txt" : errorcode(status));
    }

    if (GuiButton(btnSL, "SL 26")) {
        if (d->size == 52) {
            setDeck(splitDeck(getDeck(), 26));
            strcpy(message, "Deck split at 26");
        } else {
            strcpy(message, "Error: Load deck first");
        }
    }

    if (GuiButton(btnSR, "Shuffle")) {
        if (d->size == 52) {
            setDeck(randomShuffle(getDeck()));
            strcpy(message, "Deck shuffled");
        } else {
            strcpy(message, "Error: Load deck first");
        }
    }

    if (GuiButton(btnSW, "SW")) {
        if (d->size == 52) {
            dealcardstocolumn(getDeck(), 1);
            strcpy(message, "Deck shown in columns");
        } else {
            strcpy(message, "Error: Load deck first");
        }
    }

    if (GuiButton(btnP, "Play")) {
        if (d->size == 52) {
            playdealcard(getDeck());
            strcpy(message, "Game started");
            gameStarted = 1;
        } else {
            strcpy(message, "Error: Load deck first");
        }
    }

    if (GuiButton(btnQ, "Quit")) {
        CloseWindow();
    }

    if (gameStarted) {
        // Draw current game board (cards)
        for (int i = 0; i < 7; i++) {
            Column* col = getColumn(i);
            Card* current = col ? col->top : NULL;
            int yOffset = 0;
            while (current) {
                Rectangle cardRect = { 100 + i * 120, 160 + yOffset, 60, 90 };
                DrawRectangleRec(cardRect, current->visible ? RAYWHITE : GRAY);
                DrawRectangleLinesEx(cardRect, 2, BLACK);
                if (current->visible) {
                    DrawText(TextFormat("%c%c", current->rank, current->suit), cardRect.x + 5, cardRect.y + 5, 20, BLACK);
                }
                current = current->next;
                yOffset += 30;
            }
        }
    }

    EndDrawing();
}

void CloseGUI(void) {
    freeDeck(getDeck());
    CloseWindow();
}

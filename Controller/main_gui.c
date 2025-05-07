//
// Created by Magnus Fehrmann on 05/05/2025.
//

#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "../View/gui.h"

int main(void) {
    InitGUI();
    while (!WindowShouldClose()) {
        UpdateGUI();
    }
    CloseGUI();
    return 0;
}

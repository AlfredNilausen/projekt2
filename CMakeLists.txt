# Minimum CMake version and project name
cmake_minimum_required(VERSION 3.15)
project(projekt2 C)

set(CMAKE_C_STANDARD 11)

# Raylib include and lib paths (adjust if needed)
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

# Source files
add_executable(gui_mode
        Controller/main_gui.c
        Controller/GameController.c
        Controller/MoveLogic.c
        Model/Game.c
        Model/card.c
        Model/deck.c
        Model/foundation.c
        Model/columns.c
        View/gui.c
        View/BoardView.c
)

# Link Raylib and system libraries
target_link_libraries(gui_mode
        raylib
        m
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
)

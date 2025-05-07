cmake_minimum_required(VERSION 3.30)
project(projekt2 C)

set(CMAKE_C_STANDARD 11)

add_executable(projekt2 Controller/main.c Model/card.c Model/columns.c Model/deck.c View/BoardView.c
        Controller/GameController.c
        Model/Game.c
        Model/Game.h
        Model/foundation.c
        Model/foundation.h
        Controller/MoveLogic.c
        Controller/MoveLogic.h)

add_executable(Test Model/card.c Model/columns.c Model/deck.c)
//
// Created by alfre on 01-05-2025.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#define MAX_INPUT 100

int LD(const char* filename);
char* errorcode(int);
char* errorMove(int code);
int saveDeckToFile(Deck* deck, const char* filename);

#endif //GAMECONTROLLER_H




#pragma once
#include <stdlib.h>

typedef struct GameElement{
    // Position and size from the bottom left
    float pos_x;
    float pos_y;
    float height;
    float width;

    void* spriteSheet;
} GameElement;

GameElement* newElement();
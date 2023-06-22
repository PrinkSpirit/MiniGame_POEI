#pragma once
#include <stdlib.h>

/** GameElememt
 * Basis for other elements that will be displayed ingame
 * This should only be used inside another element
*/
typedef struct GameElement{
    // Position and size from the bottom left
    float pos_x;
    float pos_y;
    float height;
    float width;

    void* spriteSheet;
} GameElement;

GameElement* newElement();
#pragma once
#include <stdlib.h>
#include <SDL2/SDL.h>

/** GameElememt
 * Basis for other elements that will be displayed ingame
 * This should only be used inside another element
*/
typedef struct GameElement{
    // Position and size from the bottom left
    float pos_x;
    float pos_y;
    
    SDL_Rect* size;
    SDL_Rect* sprite;
    SDL_Texture* spriteSheet;
} GameElement;

GameElement* newElement();
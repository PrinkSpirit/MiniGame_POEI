#include "GameElement.h"


GameElement* newElement() {
    GameElement* ge = malloc(sizeof(GameElement));

    ge->pos_x = 0.0f;
    ge->pos_y = 0.0f;

    ge->size = malloc(sizeof(SDL_Rect));
    ge->size->h = 16;
    ge->size->w = 16;
    ge->size->x = 0;
    ge->size->y = 0;


    ge->sprite = malloc(sizeof(SDL_Rect));
    ge->spriteSheet = NULL;


    return ge;
}
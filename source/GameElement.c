#include "GameElement.h"


GameElement* newElement() {
    GameElement* ge = malloc(sizeof(GameElement));

    ge->pos_x = 0.0f;
    ge->pos_y = 0.0f;

    ge->height = 16.0f;
    ge->width = 16.0f;

    ge->spriteSheet = NULL;

    return ge;
}
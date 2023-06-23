#pragma once

#include <SDL2/SDL.h>
#include "Pawn.h"
#include "Controller.h"


/** Player
 * Define an element controlled by external inputs
*/
typedef struct Player
{
    // Attributes
    Pawn* pawn;

    bool isRunning;
    bool isJumping;

    bool canJump;

    SDL_Rect* placeholderSprite;

}Player;

Player* newPlayer();


void PL_setPosition(Player*, float, float);
Actor* PL_getActor(Player*);
void PlayerUpdate(Player* this, Input* input);
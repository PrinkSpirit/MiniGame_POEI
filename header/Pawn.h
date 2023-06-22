#pragma once

#include "Actor.h"
#include <stdbool.h>

/** Pawn
 * Define an actor that can move on it's own.
 * Eg. NPC, Enemy, etc.
*/
typedef struct Pawn{
    Actor* actor;

    unsigned int health;


}Pawn;

Pawn* newPawn();
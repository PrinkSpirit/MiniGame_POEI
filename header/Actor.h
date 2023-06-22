#pragma once
#include "GameElement.h"

/** Actor
 * Define an element with which we can interact but they are not moving on they own
 * They can be still be moved by other means like being pushed or fall folowing gravity
 * 
 * Eg. Key, Heart, Door, Spike
 * 
*/
typedef struct Actor{
    GameElement* element;

    //OnOverlap(struct Actor*)
} Actor;

Actor* newActor();
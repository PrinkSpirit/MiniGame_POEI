#pragma once
#include <stdbool.h>
#include "GameElement.h"
#include "Consts.h"

/** Actor
 * Define an element with which we can interact but they are not moving on their own
 * They can be still be moved by other means like being pushed or fall folowing gravity
 * 
 * Eg. Key, Heart, Door, Spike
 * 
*/
typedef struct Actor{
    GameElement* element;

    // Vertical and horizontal acceleration.
    float v_a;
    float h_a;

    // Allows some items to simply float in midair
    bool usesGravity;
    // Tell the update position function if position need to be updated
    bool needsUpdate;

    //OnOverlap(struct Actor*)
    void (*update)(struct Actor*);
} Actor;

Actor* newActor();
void ActorUpdate(Actor* this);
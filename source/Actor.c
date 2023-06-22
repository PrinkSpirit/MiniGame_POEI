#include "Actor.h"


Actor* newActor(){
    Actor* act = malloc(sizeof(Actor));

    act->element = newElement();

    act->h_a = 0.0f;
    act->v_a = 0.0f;

    act->needsUpdate = false;

    return act;
}
#include "Actor.h"


Actor* newActor(){
    Actor* act = malloc(sizeof(Actor));

    act->element = newElement();

    return act;
}
#include "Actor.h"


Actor* newActor(){
    Actor* act = malloc(sizeof(Actor));

    act->element = newElement();

    act->h_a = 0.0f;
    act->v_a = 0.0f;

    act->needsUpdate = false;
    act->usesGravity = true;

    act->update = ActorUpdate;
    
    return act;
}

void ActorUpdate(Actor* this){
    // Gravity
    if(this->usesGravity)
        this->v_a += GRAVITY;

    this->element->pos_x += this->h_a / MV_ATTENUATION;
    this->element->pos_y += this->v_a / MV_ATTENUATION;

    // Boundary check
    if(this->element->pos_x <=0)
        this->element->pos_x = 0;
    if(this->element->pos_y <=0)
        this->element->pos_y = 0;
    
    if(this->element->pos_x >= WIDTH)
        this->element->pos_x = WIDTH - this->element->sprite->w;
    if(this->element->pos_y >= HEIGHT)
        this->element->pos_y = HEIGHT - this->element->sprite->h;

    // Sprite position Update
    this->element->sprite->x = (int) this->element->pos_x;
    this->element->sprite->y = (int) this->element->pos_y;
}
#include "Player.h"


Player *newPlayer()
{
    Player* p = malloc(sizeof(Player));
    
    p->pawn = newPawn();
    p->canJump = true;
    
    return p;
}



void PL_setPosition(Player* this, float x, float y) {
    this->pawn->actor->element->pos_x = x;
    this->pawn->actor->element->pos_y = y;

    this->pawn->actor->element->sprite->x = (int)x;
    this->pawn->actor->element->sprite->y = (int)y;

}

Actor* PL_getActor(Player* this) {
    return this->pawn->actor;
}

void PlayerUpdate(Player* this, Input* input){
    Actor* actor = this->pawn->actor;
    // Handle inputs
    
    // Left / Right
    if(input->left && !input->right)
        actor->h_a = -SPEED;
    else if(!input->left && input->right)
        actor->h_a = SPEED;
    else
        actor->h_a = 0;

    // Jump
    // Initiating jump
    if(input->jump && this->canJump){
        this->canJump = false;
        this->isJumping = true;
        
        actor->v_a = JUMP;
    }


    if(actor->element->pos_y >= HEIGHT - actor->element->sprite->h) {
        if (!input->jump)
            this->canJump = true;
    }

    

    actor->update(actor);
}
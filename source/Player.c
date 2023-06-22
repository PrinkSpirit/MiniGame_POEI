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

    this->placeholderSprite->x = (int)x;
    this->placeholderSprite->y = (int)y;

}

Actor* PL_getActor(Player* this) {
    return this->pawn->actor;
}
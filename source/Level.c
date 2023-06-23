#include "Level.h"


Level* newLevel(){
    Level* lvl = malloc(sizeof(Level));

    lvl->actorList = malloc(sizeof(Actor*));
    lvl->blockList = malloc(sizeof(StaticBlock*));
    lvl->elementList = malloc(sizeof(GameElement*));

    lvl->nbActor = 0;
    lvl->nbBlock = 0;
    lvl->nbElement = 0;

    return lvl;
}

void AddActor(Level* this, Actor* act){
    this->actorList[this->nbActor++] = act;
}

void AddBlock(Level* this, StaticBlock* blk){
    this->blockList[this->nbBlock++] = blk;
}

void AddElement(Level* this, GameElement* el){
    this->elementList[this->nbElement++] = el;
}

void AddPlayer(Level* this, Player* player){
    this->player = player;
}
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
    this->actorList=(Actor**)realloc(this->actorList,sizeof(this->actorList)+sizeof(Actor));
    this->actorList[this->nbActor++] = act;
}

void AddBlock(Level* this, StaticBlock* blk){
    this->blockList=(StaticBlock**)realloc(this->blockList,sizeof(this->blockList)+sizeof(StaticBlock));
    this->blockList[this->nbBlock++] = blk;
}

void AddElement(Level* this, GameElement* el){
    this->elementList=(GameElement**)realloc(this->elementList,sizeof(this->elementList)+sizeof(GameElement));
    this->elementList[this->nbElement++] = el;
}

void AddPlayer(Level* this, Player* player){
    this->player = player;
}
void freeLevel(Level* this){
    if(this != NULL){
        int last_index;
        int i=0;
        if(this->actorList != NULL){
            last_index=sizeof(this->actorList)-1;
            for(i=0;i<=last_index;i++){
                freeActor(this->actorList[i]);
            }
        }
        if(this->blockList != NULL){
            last_index=sizeof(this->blockList)-1;
            for(i=0;i<=last_index;i++){
                freeBlock(this->blockList[i]);
            }
        }
        if(this->elementList){
            last_index=sizeof(this->elementList)-1;
            for(i=0;i<=last_index;i++){
                freeGameElement(this->elementList[i]);
            }
        }
    }
    
}
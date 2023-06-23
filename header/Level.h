#pragma once
#include <SDL2/SDL.h>
#include "Actor.h"
#include "StaticBlock.h"
#include "Player.h"


typedef struct Level{

    Actor** actorList;
    unsigned int nbActor;

    StaticBlock** blockList;
    unsigned int nbBlock;
    
    GameElement** elementList;
    unsigned int nbElement;

    Player* player;

}Level;


Level* newLevel();
void AddActor(Level* this, Actor* act);
void AddBlock(Level* this, StaticBlock* act);
void AddElement(Level* this, GameElement* act);
void AddPlayer(Level* this, Player* player);
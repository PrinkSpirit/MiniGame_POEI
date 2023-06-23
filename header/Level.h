#pragma once
#include <SDL2/SDL.h>

#include "SDL_Rendering.h"
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

void createBlock(SDL* sdl, Level* lvl, int x, int y, SDL_Texture* spriteSheet, bool collision);

void checkForCollision(Level*);
bool isColliding(GameElement* A, GameElement*B);
void handleCollision(Actor* A, GameElement*B);

void renderLevel(SDL* sdl, Level* lvl);
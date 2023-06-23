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
    
    this->actorList=(Actor**)realloc(this->actorList,sizeof(Actor)*(this->nbActor+1));
    this->actorList[this->nbActor] = act;
    this->nbActor++;
}

void AddBlock(Level* this, StaticBlock* blk){
    
    this->blockList=(StaticBlock**)realloc(this->blockList,sizeof(StaticBlock)*(this->nbBlock+1));
    this->blockList[this->nbBlock] = blk;
    this->nbBlock++;
}

void AddElement(Level* this, GameElement* el){
    
    this->elementList=(GameElement**)realloc(this->elementList,sizeof(GameElement)*(this->nbElement+1));
    this->elementList[this->nbElement] = el;
    this->nbElement++;
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


void createBlock(SDL* sdl, Level* lvl, int x, int y, SDL_Texture* spriteSheet, bool collision){
    
    StaticBlock* block = newStaticBlock(collision);
    block->element->pos_x = x * 16 * SIZE_MULT;
    block->element->pos_y = HEIGHT-y * 16 * SIZE_MULT;
    block->element->spriteSheet = spriteSheet;
    setSprite(sdl, block->element);

    AddBlock(lvl, block);
}

bool isColliding(GameElement* A, GameElement*B){
    return (bool) SDL_HasIntersection(A->sprite, B->sprite);
}

/**
 * Handle collision between action and static elements
*/
void handleCollision(Actor* A, GameElement*B){
    float Ah = A->element->sprite->w;
    float Aw = A->element->sprite->h;
    
    float Bx = B->pos_x;
    float By = B->pos_y;
    float Bh = B->sprite->w;
    float Bw = B->sprite->h;

    if(A->v_a > 0) { // Is falling
        A->element->pos_y = By-Bh - Ah;
        A->v_a = 0;
    }

    if(A->v_a < 0) { // Is rising
        A->element->pos_y = By;
        A->v_a = 0;
    }
    A->element->sprite->x = (int) A->element->pos_x;
    A->element->sprite->y = (int) A->element->pos_y;
    
    if(isColliding(A->element,B)){
        if(A->h_a > 0) { // Is going right
            A->element->pos_x = Bx - Aw; // New position is B minus A's Sprite width
            A->h_a = 0; // Momentum is cut
        }

        if(A->h_a < 0) { // Is going left
            A->element->pos_x = Bx + Bw; // New position is B plus B's Sprite width
            A->h_a = 0; // Momentum is cut
        }

        A->element->sprite->x = (int) A->element->pos_x;
        A->element->sprite->y = (int) A->element->pos_y;
    }
}

void checkForCollision(Level* lvl) {
    
    // Player with blocks
    for(int i=0; i<lvl->nbBlock;i++){
        if(isColliding(lvl->player->pawn->actor->element, lvl->blockList[i]->element)){
            handleCollision(lvl->player->pawn->actor, lvl->blockList[i]->element);

        }
        
    }
}


void renderLevel(SDL* sdl, Level* lvl){

    // Background color
    SDL_SetRenderDrawColor(sdl->renderer, 255, 0, 0, 255);

    for(int i=0; i<lvl->nbBlock;i++){
        SDL_RenderCopy(sdl->renderer, lvl->blockList[i]->element->spriteSheet, lvl->blockList[i]->element->size, lvl->blockList[i]->element->sprite);
    }

    // Rendering Actors
    for(int i=0; i<lvl->nbActor;i++){
        SDL_RenderCopy(sdl->renderer, lvl->actorList[i]->element->spriteSheet, lvl->actorList[i]->element->size, lvl->actorList[i]->element->sprite);
    }

    SDL_RenderCopy(sdl->renderer, lvl->player->pawn->actor->element->spriteSheet, lvl->player->pawn->actor->element->size, lvl->player->pawn->actor->element->sprite);
    
    // Rendering random GameElements
    for(int i=0; i<lvl->nbElement; i++){
        SDL_RenderCopy(sdl->renderer, lvl->elementList[i]->spriteSheet, lvl->elementList[i]->size, lvl->elementList[i]->sprite);
    }


    SDL_RenderPresent(sdl->renderer);
}
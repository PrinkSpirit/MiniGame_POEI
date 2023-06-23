#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "Controller.h"
#include "SDL_Rendering.h"
#include "Player.h"
#include "StaticBlock.h"
#include "Level.h"

void checkForCollision(Level*);

bool isColliding(GameElement* A, GameElement*B);
void handleCollision(Actor* A, GameElement*B);

int main(int argc, char* argv[])
{
    SDL* sdl = Init_SDL();


    
    /* Main loop */
    bool running = true;
    SDL_Event event;
    
    Input* input = initController();

    Level* level = newLevel(); 
    
    /* TMP: INIT PLAYER */
    Player* player = newPlayer();
    player->placeholderSprite = malloc(sizeof(SDL_Rect));
    player->placeholderSprite->h = SIZE;
    player->placeholderSprite->w = SIZE;
    PL_setPosition(player, (WIDTH-SIZE)/2, (HEIGHT-SIZE)/2);

    Actor* pActor = PL_getActor(player);
    pActor->element->size->h = 32;
    pActor->element->size->w = 32;

    setTexture(sdl,pActor->element,"./sprites/Link.bmp");
    setSprite(sdl,pActor->element);

    AddPlayer(level, player);



    /* TMP: Init Blocks */
    SDL_Texture* blockSprite = loadTexture(sdl, "./sprites/brick.bmp");

    StaticBlock* B1 = newStaticBlock(true);
    B1->element->pos_x = 0;
    B1->element->pos_y = HEIGHT;
    B1->element->spriteSheet = blockSprite;
    B1->element->size->h = 16;
    B1->element->size->w = 16;
    setSprite(sdl, B1->element);


    StaticBlock* B2 = newStaticBlock(true);
    B2->element->pos_x = 16*SIZE_MULT;
    B2->element->pos_y = HEIGHT;
    B2->element->spriteSheet = blockSprite;
    setSprite(sdl, B2->element);
    
    StaticBlock* B3 = newStaticBlock(true);
    B3->element->pos_x = WIDTH-256;
    B3->element->pos_y = HEIGHT;
    B3->element->spriteSheet = blockSprite;
    setSprite(sdl, B3->element);
    
    AddBlock(level, B1);
    AddBlock(level, B2);
    AddBlock(level, B3);
   
    while (running)
    {
        /**
         *       Processing events 
         ************************************/
        running = input_handler(&event, input);
        
        
        
        /**
         *        Updating Actors
         ************************************/
        PlayerUpdate(player, input);
        checkForCollision(level);

        /*for(int i=0; i<blockNb; i++){
            actorList[i]->update(actorList[i]);
        }*/


        /** 
         *           RENDERING
         ************************************/

        /* Clear screen */
        clearScreen(sdl);
        
        renderLevel(sdl, level);    

        /* Draw to window and loop */
        draw(sdl);
      
    }
  
    /* Release resources */
    release_SDL(sdl);
    SDL_Quit();

    return 0;
}

bool isColliding(GameElement* A, GameElement*B){
    return (bool) SDL_HasIntersection(A->sprite, B->sprite);
    float Ax = A->pos_x;
    float Ay = A->pos_y;
    float Ah = A->size->w;
    float Aw = A->size->h;
    
    float Bx = B->pos_x;
    float By = B->pos_y;
    float Bh = B->size->w;
    float Bw = B->size->h;
    

    if(Ax < Bx + Bw && Ax + Aw > Bx && Ay < By + Bh && Ay + Ah > By){
        fprintf(stderr, "x:%f, y:%f - Bx:%f, By:%f", Ax, Ay, Bx, By);
        return true;
    }

    //if((Bx<Ax && Ax<Bx+Bw) &&)

    return false;
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
    
    if(A->h_a > 0) { // Is going right
        A->element->pos_x = Bx - Aw; // New position is B minus A's Sprite width
        A->h_a = 0; // Momentum is cut
    }

    if(A->h_a < 0) { // Is going left
        A->element->pos_x = Bx + Bw; // New position is B plus B's Sprite width
        A->h_a = 0; // Momentum is cut
    }

    if(A->v_a > 0) { // Is falling
        A->element->pos_y = By-Bh - Ah;
        A->v_a = 0;
    }

    if(A->v_a < 0) { // Is rising
        A->element->pos_y = By;
        A->v_a = 0;
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



#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "Controller.h"
#include "SDL_Rendering.h"
#include "Player.h"
#include "StaticBlock.h"


int main(int argc, char* argv[])
{
    SDL* sdl = Init_SDL();


    
    /* Main loop */
    bool running = true;
    SDL_Event event;
    
    Input* input = initController();
    
    Actor** actorList = malloc(sizeof(Actor));
    unsigned int nbActor = 0;

    GameElement** elementList = malloc(sizeof(GameElement));
    unsigned int nbElement = 0;
    
    
    
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

    /* TMP: Init Blocks */
    SDL_Texture* blockSprite = loadTexture(sdl, "./sprites/brick.bmp");

    StaticBlock* B1 = newStaticBlock(true);
    B1->element->pos_x = 0;
    B1->element->pos_y = HEIGHT;
    B1->element->spriteSheet = blockSprite;
    setSprite(sdl, B1->element);


    StaticBlock* B2 = newStaticBlock(true);
    B2->element->pos_x = 16*SIZE_MULT;
    B2->element->pos_y = HEIGHT;
    B2->element->spriteSheet = blockSprite;
    setSprite(sdl, B2->element);


    /* Adding elements to the render list */
    elementList[nbElement++] = B1->element;
    elementList[nbElement++] = B2->element;
    elementList[nbElement++] = pActor->element;
    
   
    while (running)
    {
        /**
         *       Processing events 
         ************************************/
        running = input_handler(&event, input);
        
        
        
        /**
         *        Updating Actors
         ************************************/

        /*for(int i=0; i<blockNb; i++){
            actorList[i]->update(actorList[i]);
        }*/

        PlayerUpdate(player, input);

        /** 
         *           RENDERING
         ************************************/

        /* Clear screen */
        clearScreen(sdl);

        /* Draw the rectangle */
        SDL_SetRenderDrawColor(sdl->renderer, 255, 0, 0, 255);
        //SDL_RenderFillRect(sdl->renderer, player->placeholderSprite);
        for(int i=0; i<nbElement; i++){
            SDL_RenderCopy(sdl->renderer, elementList[i]->spriteSheet, elementList[i]->size, elementList[i]->sprite);
        }
        //SDL_RenderCopy(sdl->renderer, pActor->element->spriteSheet, pActor->element->size, pActor->element->sprite);
        SDL_RenderPresent(sdl->renderer);

        /* Draw to window and loop */
        draw(sdl);
      
    }
  
    /* Release resources */
    release_SDL(sdl);
    SDL_Quit();

    return 0;
}

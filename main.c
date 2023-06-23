#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "Controller.h"
#include "SDL_Rendering.h"
#include "Player.h"
#include "StaticBlock.h"
#include "Level.h"

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
    setSprite(sdl, B1->element);


    StaticBlock* B2 = newStaticBlock(true);
    B2->element->pos_x = 16*SIZE_MULT;
    B2->element->pos_y = HEIGHT;
    B2->element->spriteSheet = blockSprite;
    setSprite(sdl, B2->element);
    
    
    AddBlock(level, B1);
    AddBlock(level, B2);
   
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

        /*for(int i=0; i<blockNb; i++){
            actorList[i]->update(actorList[i]);
        }*/


        /** 
         *           RENDERING
         ************************************/

        /* Clear screen */
        clearScreen(sdl);

        /* Draw the rectangle */
        SDL_SetRenderDrawColor(sdl->renderer, 255, 0, 0, 255);
        //SDL_RenderFillRect(sdl->renderer, player->placeholderSprite);

        // Rendering blocks
        
        renderLevel(sdl, level);

        //SDL_RenderCopy(sdl->renderer, pActor->element->spriteSheet, pActor->element->size, pActor->element->sprite);
        

        /* Draw to window and loop */
        draw(sdl);
      
    }
  
    /* Release resources */
    release_SDL(sdl);
    SDL_Quit();

    return 0;
}

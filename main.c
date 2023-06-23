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
    PL_setPosition(player, 8*32, (HEIGHT-4*32));

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
    B1->element->pos_y = HEIGHT-256;
    B1->element->spriteSheet = blockSprite;
    setSprite(sdl, B1->element);

    createBlock(sdl, level, 3, 4, blockSprite, true);
    createBlock(sdl, level, 4, 4, blockSprite, true);
    createBlock(sdl, level, 8, 8, blockSprite, true);
    createBlock(sdl, level, 1, 8, blockSprite, true);
    createBlock(sdl, level, 0, 8, blockSprite, true);
   

    for(int i=0; i<WIDTH/32; i++) {
        createBlock(sdl, level, i, 0, blockSprite, true);
    }
    
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
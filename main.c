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
  
  Player* player = newPlayer();
  player->placeholderSprite = malloc(sizeof(SDL_Rect));
  player->placeholderSprite->h = SIZE;
  player->placeholderSprite->w = SIZE;
  PL_setPosition(player, (WIDTH-SIZE)/2, (HEIGHT-SIZE)/2);

  Actor* pActor = PL_getActor(player);
   
  while (running)
  {
    /**
     *       Processing events 
     ************************************/
    running = input_handler(&event, input);
    
    
    
    /**
     *        Updating Actors
     ************************************/
    pActor->h_a = (input->right - input->left)*SPEED;
    pActor->v_a += GRAVITY;

    if (input->jump && player->canJump)
    {
      player->canJump = false;
      pActor->v_a = JUMP;
    }

    pActor->element->pos_x += pActor->h_a / 60;
    pActor->element->pos_y += pActor->v_a / 60;

    if (pActor->element->pos_x <= 0)
      pActor->element->pos_x = 0;
    if (pActor->element->pos_x >= WIDTH - player->placeholderSprite->w)
      pActor->element->pos_x = WIDTH - player->placeholderSprite->w;
    if (pActor->element->pos_y <= 0)
      pActor->element->pos_y = 0;

    if (pActor->element->pos_y >= HEIGHT - player->placeholderSprite->h)
    {
      pActor->v_a = 0;
      pActor->element->pos_y = HEIGHT - player->placeholderSprite->h;
      if (!input->jump)
        player->canJump = true;
    }
    player->placeholderSprite->x = (int) pActor->element->pos_x;
    player->placeholderSprite->y = (int) pActor->element->pos_y;

  /** 
   *           RENDERING
   ************************************/

    /* Clear screen */
    clearScreen(sdl);

    /* Draw the rectangle */
    SDL_SetRenderDrawColor(sdl->renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(sdl->renderer, player->placeholderSprite);

    /* Draw to window and loop */
    draw(sdl);
    
  }
  
  /* Release resources */
  release_SDL(sdl);
  SDL_Quit();

  return 0;
}

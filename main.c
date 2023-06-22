#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "Controller.h"
#include "SDL_Init.h"

#define WIDTH 640
#define HEIGHT 480
#define SIZE 200
#define SPEED 600
#define GRAVITY 60
#define FPS 60
#define JUMP -1200

int main(int argc, char* argv[])
{
  SDL* sdl = Init_SDL();


  
  /* Main loop */
  bool running = true, can_jump = true;
  float x_pos = (WIDTH-SIZE)/2, y_pos = (HEIGHT-SIZE)/2, x_vel = 0, y_vel = 0;
  SDL_Rect rect = {(int) x_pos, (int) y_pos, SIZE, SIZE};
  SDL_Event event;
  
  Input* input = initController();
  
  
  while (running)
  {
    /**
     *       Processing events 
     ************************************/
    running = input_handler(&event, input);
    
    
    
    /**
     *        Updating Actors
     ************************************/
    x_vel = (input->right - input->left)*SPEED;
    y_vel += GRAVITY;
    if (input->jump && can_jump)
    {
      can_jump = false;
      y_vel = JUMP;
    }
    x_pos += x_vel / 60;
    y_pos += y_vel / 60;
    if (x_pos <= 0)
      x_pos = 0;
    if (x_pos >= WIDTH - rect.w)
      x_pos = WIDTH - rect.w;
    if (y_pos <= 0)
      y_pos = 0;
    if (y_pos >= HEIGHT - rect.h)
    {
      y_vel = 0;
      y_pos = HEIGHT - rect.h;
      if (!input->jump)
        can_jump = true;
    }
    rect.x = (int) x_pos;
    rect.y = (int) y_pos;

  /** 
   *           RENDERING
   ************************************/

    /* Clear screen */
    SDL_SetRenderDrawColor(sdl->renderer, 92, 148, 252, 255);
    SDL_RenderClear(sdl->renderer);

    /* Draw the rectangle */
    SDL_SetRenderDrawColor(sdl->renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(sdl->renderer, &rect);

    /* Draw to window and loop */
    SDL_RenderPresent(sdl->renderer);
    SDL_Delay(1000/FPS);
  }
  
  /* Release resources */
  release_SDL(sdl);
  SDL_Quit();

  return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "Controller.h"

#define WIDTH 640
#define HEIGHT 480
#define SIZE 200
#define SPEED 600
#define GRAVITY 60
#define FPS 60
#define JUMP -1200

int main(int argc, char* argv[])
{
  /* Initializes the timer, audio, video, joystick,
  haptic, gamecontroller and events subsystems */
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("Error initializing SDL: %s\n", SDL_GetError());
    return 0;
  }
  /* Create a window */
  SDL_Window* wind = SDL_CreateWindow("Hello Platformer!",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      WIDTH, HEIGHT, 0);
  if (!wind)
  {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return 0;
  }
  /* Create a renderer */
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer* rend = SDL_CreateRenderer(wind, -1, render_flags);
  if (!rend)
  {
    printf("Error creating renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(wind);
    SDL_Quit();
    return 0;
  }

  
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
    SDL_SetRenderDrawColor(rend, 92, 148, 252, 255);
    SDL_RenderClear(rend);

    /* Draw the rectangle */
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    SDL_RenderFillRect(rend, &rect);

    /* Draw to window and loop */
    SDL_RenderPresent(rend);
    SDL_Delay(1000/FPS);
  }
  /* Release resources */
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(wind);
  SDL_Quit();
  return 0;
}

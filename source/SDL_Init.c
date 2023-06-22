#include "SDL_Init.h"

SDL *Init_SDL()
{

    SDL* sdl = malloc(sizeof(SDL));

    /* Initializes the timer, audio, video, joystick,
    haptic, gamecontroller and events subsystems */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
    
    /* Create a window */
    sdl->window = SDL_CreateWindow("Hello Platformer!",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WIDTH, HEIGHT, 0);
    if (!sdl->window)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }
    /* Create a renderer */
    sdl->render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    sdl->renderer = SDL_CreateRenderer(sdl->window, -1, sdl->render_flags);
    if (!sdl->renderer)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(sdl->window);
        SDL_Quit();
        return 0;
    }

    return sdl;
}

void release_SDL(SDL *sdl)
{
    SDL_DestroyRenderer(sdl->renderer);
    SDL_DestroyWindow(sdl->window);
}

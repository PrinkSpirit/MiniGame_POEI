#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480

typedef struct SDL{
    SDL_Window* window;
    Uint32 render_flags;
    SDL_Renderer* renderer;
}SDL;


SDL* Init_SDL();
void release_SDL(SDL* sdl);
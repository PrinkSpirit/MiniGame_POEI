#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include "Consts.h"
#include "GameElement.h"


/**
 * Handle most SDL features for rendering content
*/
typedef struct SDL{
    SDL_Window* window;
    Uint32 render_flags;
    SDL_Renderer* renderer;
}SDL;


SDL* Init_SDL();
void release_SDL(SDL* sdl);
void clearScreen(SDL* sdl);
void draw(SDL* sdl);

void setTexture(SDL* sdl, GameElement* el, char* path);
SDL_Texture* loadTexture(SDL* sdl, char* path);
void setSprite(SDL* sdl, GameElement* el);

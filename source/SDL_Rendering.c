#include "SDL_Rendering.h"

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

void clearScreen(SDL *sdl)
{
    SDL_SetRenderDrawColor(sdl->renderer, 92, 148, 252, 255);
    SDL_RenderClear(sdl->renderer);
}

void draw(SDL* sdl) {
    SDL_RenderPresent(sdl->renderer);
    SDL_Delay(1000/FPS);
}

void setTexture(SDL* sdl, GameElement* el, char* path){
    SDL_Surface* file = SDL_LoadBMP(path);
    
    if(file==NULL)
        fprintf(stderr, SDL_GetError());

    el->spriteSheet = SDL_CreateTextureFromSurface(sdl->renderer, file);
}

SDL_Texture* loadTexture(SDL* sdl, char* path){
    SDL_Surface* file = SDL_LoadBMP(path);
    
    if(file==NULL)
        fprintf(stderr, SDL_GetError());

    return SDL_CreateTextureFromSurface(sdl->renderer, file);
}

void setSprite(SDL* sdl, GameElement* el){
    Uint32 format;
    int access = 0;
    int width = 0;
    int height = 0;
    int errorCheck;

    errorCheck = SDL_QueryTexture(el->spriteSheet, &format, &access, &width, &height);

    if(errorCheck !=0)
        fprintf(stderr, SDL_GetError());

    if(el->sprite == NULL)
        el->sprite = malloc(sizeof(SDL_Rect));
    
    // SIZE_MULT give bigger sprites
    el->sprite->h = el->size->h * SIZE_MULT;
    el->sprite->w = el->size->w * SIZE_MULT;
    el->sprite->x = el->pos_x;
    el->sprite->y = el->pos_y - el->sprite->h; //Inverted since pixel space start from the top

}
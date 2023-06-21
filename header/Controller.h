#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>

/** Input
 *   - Input handle transition from key to action
 *   - On key down bool is set to true
 *   - On key up bool is set to false
 */
typedef struct Input{
    // Directions
    bool up;
    bool down;
    bool left;
    bool right;
    bool jump;
    bool attack;
} Input;


/** input_handler
 *   - Handle key presses
 */
void input_handler(SDL_Event* event, Input * input);


/** Key check functions
 *   - Use them to give espected keys for each actions
 */
bool up_key(SDL_Scancode code);
bool down_key(SDL_Scancode code);
bool left_key(SDL_Scancode code);
bool right_key(SDL_Scancode code);
bool jump_key(SDL_Scancode code);
bool attack_key(SDL_Scancode code);
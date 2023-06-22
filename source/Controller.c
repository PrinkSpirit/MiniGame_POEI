#include "Controller.h"

Input* initController(){
    Input* input = malloc(sizeof(Input));

    // Since actions are not active at the beginning
    // we set all bool to false
    input->up = false;
    input->down = false;
    input->left = false;
    input->right = false;

    input->attack = false;
    input->jump = false;
    
    return input;
}

bool input_handler(SDL_Event* event, Input* input){
    while (SDL_PollEvent(event))
    {
        SDL_Scancode code = event->key.keysym.scancode;
        switch (event->type)
        {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                if(up_key(code))
                    input->up = true;
                if(down_key(code))
                    input->down = true;
                if(left_key(code))
                    input->left = true;
                if(right_key(code))
                    input->right = true;
                if(attack_key(code))
                    input->attack = true;
                if(jump_key(code))
                    input->jump = true;
                break;
            case SDL_KEYUP:
                if(up_key(code))
                    input->up = false;
                if(down_key(code))
                    input->down = false;
                if(left_key(code))
                    input->left = false;
                if(right_key(code))
                    input->right = false;
                if(attack_key(code))
                    input->attack = false;
                if(jump_key(code))
                    input->jump = false;
                break;
            default:
                break;
        }
    }

    return true;
}

bool up_key(SDL_Scancode code){
    bool up = false;
    up |= code == SDL_SCANCODE_UP;
    return up;
}

bool down_key(SDL_Scancode code)
{
    bool down = false;
    down |= code == SDL_SCANCODE_DOWN;
    return down;
}

bool left_key(SDL_Scancode code)
{
    bool left = false;
    left |= code == SDL_SCANCODE_LEFT;
    return left;
}

bool right_key(SDL_Scancode code)
{
    bool right = false;
    right |= code == SDL_SCANCODE_RIGHT;
    return right;
}

bool jump_key(SDL_Scancode code)
{
    bool jump = false;
    jump |= code == SDL_SCANCODE_SPACE;
    return jump;
}

bool attack_key(SDL_Scancode code)
{
    bool attack = false;
    attack |= code == SDL_SCANCODE_Z;
    return attack;
}

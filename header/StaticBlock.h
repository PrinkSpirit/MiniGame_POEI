#pragma once

#include "GameElement.h"
#include <stdbool.h>

/** StaticBlock
 * Define elements that will never move and have no interaction other than collision.
 * Some will have collision, others won't.
 * 
 * Eg. Ground, Wall, Cloud, Tree, ect.
*/
typedef struct StaticBlock{
    GameElement* element;

    // Define if actors can colide with it
    bool hasColision;

}StaticBlock;

StaticBlock* newStaticBlock(bool);
void freeBlock(StaticBlock* block);
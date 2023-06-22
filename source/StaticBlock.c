#include "StaticBlock.h"



StaticBlock* newStaticBlock(bool colision){
    StaticBlock* block = malloc(sizeof(StaticBlock));

    block->element = newElement();

    block->hasColision = colision;

    return block;
}
#include "StaticBlock.h"



StaticBlock* newStaticBlock(bool colision){
    StaticBlock* block = malloc(sizeof(StaticBlock));

    block->hasColision = colision;

    return block;
}
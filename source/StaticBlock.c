#include "StaticBlock.h"


StaticBlock* newStaticBlock(){
    StaticBlock* block = malloc(sizeof(StaticBlock));

    block->hasColision = false;

    return block;
}

StaticBlock* newStaticBlock(bool colision){
    StaticBlock* block = malloc(sizeof(StaticBlock));

    block->hasColision = colision;

    return block;
}
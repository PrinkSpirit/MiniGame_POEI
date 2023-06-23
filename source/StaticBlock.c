#include "StaticBlock.h"



StaticBlock* newStaticBlock(bool colision){
    StaticBlock* block = malloc(sizeof(StaticBlock));

    block->element = newElement();

    block->hasColision = colision;

    return block;
}

void freeBlock(StaticBlock* block){
    if(block !=NULL){
        if(block->element !=NULL){
            free(block->element);
        }
        free(block);
    }
    
}
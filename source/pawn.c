#include "Pawn.h"

Pawn *newPawn()
{
    Pawn* pawn = malloc(sizeof(Pawn));

    pawn->actor = newActor();

    pawn->health = 0;

    return pawn;
}
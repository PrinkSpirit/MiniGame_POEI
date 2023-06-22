#pragma once
#include <SDL2/SDL_events.h>
#include "Actor.h"
#include "GameElement.h"
typedef struct StartPosition StartPosition;
typedef struct ActorPosition ActorPosition;
typedef struct GoalPosition GoalPosition;
int actorPositionEvent;
int goalPositionEvent;
StartPosition startPosition();
void registerActorPositionEvent();
void registerGoalPositionEvent();
ActorPosition actorPosition(SDL_Event* event);
GoalPosition goalPosition(SDL_Event* event);
int CustomEventTrigger(void *userdata, SDL_Event *event);
void enableWatchTrigger();
int pushActorEvent(Actor* actor);
int pushGoalEvent(GameElement* element);
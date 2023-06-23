#pragma once
#include <SDL2/SDL_events.h>
#include "Actor.h"
#include "GameElement.h"
#include "Level.h"
/**
 * Events.h
 * 
 * This module use SDL Custom Event API
 * 
 * You should call first registerActorPositionEvent() and registerGoalPostionEvent()
 * Then enable WatchTrigger
 * Eventualy to begin the game startPosition
 * 
 * 
 * the only method main should call are:
 * 
 * pushActorEvent()
 * pushGoalEvent()
 * 
 * */
typedef struct StartPosition StartPosition;
typedef struct ActorPosition ActorPosition;
typedef struct GoalPosition GoalPosition;
bool isStarted;
float start_x;
float start_y;
float actors_x;
float actors_y;
int actorPositionEvent;
int goalPositionEvent;
StartPosition startPosition(Actor* player);
void registerActorPositionEvent();
void registerGoalPositionEvent();
void actorPositionTrigger(SDL_Event* event);
void goalPositionTrigger(SDL_Event* event);
int CustomEventTrigger(void *userdata, SDL_Event *event);
void enableWatchTrigger();
int pushActorEvent(Actor* actor);
int pushGoalEvent(GameElement* element,Level* level);
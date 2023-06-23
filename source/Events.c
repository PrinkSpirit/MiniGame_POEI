#include "Events.h"
/***
 * Please see Events.h
 * 
 * 
 * 
*/
/**useless struct kept for not messing the code**/
struct StartPosition {
    SDL_Event event;
    int position_x;
    int position_y;
};


struct ActorPostion {
    SDL_Event customActorEvent;
    Actor* actor;
};




struct GoalPosition {
    SDL_Event customGoalEvent;
    GameElement * element;
};

typedef struct StartPosition StartPosition;
typedef struct ActorPosition ActorPosition;
typedef struct GoalPosition GoalPosition;


/**game is started **/
bool isStarted=false;

/**
 * Start position for player 
*/
float start_x=5.5;
float start_y=5.5*1.6;

/**
 * Start position for actor
 * 
*/
float actors_x=5.5;
float actors_y=5.5*1.6;

/**
*event custom type int for SDL Event type field  
*/
int actorPositionEvent;
int goalPositionEvent;

StartPosition startPosition(Actor* player){
    /**
     * Methods to block and wait at the begining of a game to be call from the main thread 
     * We should wait that the windows is displayed to start the game
     * 
     * any event should be sufficient but we expect the display of a window or a mouse click
     * or a key press
     * 
     * @param Actor -> player
     * 
    */
    
    StartPosition startEvent;
    SDL_Event ev;
    SDL_WaitEvent(&ev);
    /**Setting default values for player and actor start position**/
    int width[1];
    int height[1]; 
    SDL_Window * window=(SDL_Window*)SDL_GetWindowFromID(ev.window.windowID);
    SDL_GetWindowSize(window, width,height);
    start_y=(float)90*height[0]/100;
    start_x=(float)2*width[0]/100;
    actors_x=(float)90*height[0]/100;
    actors_y=(float)95*width[0]/100;
    if(ev.type == SDL_WINDOW_INPUT_FOCUS){
        switch (ev.window.event) {
            case SDL_WINDOWEVENT_SHOWN:
                SDL_Log("Startpostion  -> Window %d shown", ev.window.windowID);
                startEvent.event=ev;
                startEvent.position_x=start_x;
                startEvent.position_y=start_y;
            break;
            default:
                SDL_Log("Start position -> unexepected window event %d ",ev.window.windowID);
                startEvent.event=ev;
                startEvent.position_x=start_x;
                startEvent.position_y=start_y;

        }

    }
    if(ev.type == SDL_KEYDOWN){
        SDL_Log("Startpostion -> key press in windows %d ",ev.key.windowID);
        startEvent.event=ev;
        startEvent.position_x=start_x;
        startEvent.position_y=start_y;
    }

     if(ev.type == SDL_MOUSEBUTTONDOWN){
        SDL_Log("Startpostion -> mouse click in windows %d ",ev.key.windowID);
        startEvent.event=ev;
        startEvent.position_x=start_x;
        startEvent.position_y=start_y;
    }
    isStarted=true;
    player->h_a=start_x;
    player->v_a=start_y;
    return startEvent;
}

/**
 * We should registered ours cutom events here
*/

void registerActorPositionEvent(){
    /**
     * register the custom type to ActorpositionEvent
     * user.data1 should be a pointer to an Actor structure.
    */
    Uint32 myEventType = SDL_RegisterEvents(1);
    Sint32 my_event_code=13;
    if (myEventType != ((Uint32)-1)) {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
        event.type = myEventType;
        event.user.code = my_event_code;
        event.user.data1 = NULL;
        event.user.data2 = NULL;
        SDL_PushEvent(&event);
    }

}
void registerGoalPositionEvent(){
    /**
     * user.data1 should be used to passe an object corresponding to a pointer to the game element
     * 
     * 
    */
    Uint32 myEventType = SDL_RegisterEvents(1);
    Sint32 my_event_code=814;
    if (myEventType != ((Uint32)-1)) {
        SDL_Event event;
        SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
        event.type = myEventType;
        event.user.code = my_event_code;
        event.user.data1 = NULL;
        event.user.data2 = NULL;
        SDL_PushEvent(&event);
    }
}

/**
 * we should define the corresponding  methods here
 * and the trigger stack
 * 
*/
void actorPositionTrigger(SDL_Event* event){
    /**
     * Methods to update postion of an actors
     * we hope having a pointer on Actor struc in user.data1 event
     * 
    */
    Actor* act=(Actor*)event->user.data1;
    
    int width[1];
    int height[1]; 
    SDL_Window * window=(SDL_Window*)SDL_GetWindowFromID(event->window.windowID);
    SDL_GetWindowSize(window, width,height);
    if(act->needsUpdate){
        if(act->h_a == 0){
            act->h_a=actors_x;
        }
        if(act->v_a){
            act->v_a=actors_y;
        }
        float delta=act->h_a+act->element->pos_x;
        if(delta>0 && delta<width[0]){
            act->element->pos_x=delta;
        }
        delta=act->v_a+act->element->pos_y;
        if(delta>0 && delta<height[0]){
            act->element->pos_y=delta;
        }
        
        
    }
}
void goalPositionTrigger(SDL_Event* event){
    /**
     * Methods to manage achievement 
     * (TODO ? should be based on goals implementation)
     * 
    */
    
    int width[1];
    int height[1]; 
    SDL_Window * window=(SDL_Window*)SDL_GetWindowFromID(event->window.windowID);
    SDL_GetWindowSize(window, width,height);
    GameElement* element=(GameElement*)event->user.data1;
    Level* level=(Level*)event->user.data2;
    AddElement(level,element);


    /*
    if(element->pos_x<*width && element->pos_x >0 && element->pos_y<*height && element->pos_y>0){
        goalPos.customGoalEvent=*event;    
        goalPos.element=element;
    }
    */

}




int CustomEventTrigger(void *userdata, SDL_Event *event){
    if(event->type==actorPositionEvent){
        SDL_Log("receiving custom event actorPositionEvent ");
        actorPositionTrigger(event);
    }
    if(event->type==goalPositionEvent){
        SDL_Log("receiving custom event goalPositionEvent ");
        goalPositionTrigger(event);
    }
    
    return 0;

}


void enableWatchTrigger(){
    SDL_AddEventWatch(CustomEventTrigger, NULL);
    
}


/***
* Helpers
* to send custom event
*/

int pushActorEvent(Actor* actor){
    SDL_Event user_event;
    user_event.type = SDL_USEREVENT;
    user_event.user.code = actorPositionEvent ;
    user_event.user.data1 = actor;
    user_event.user.data2 = NULL;
    int res=SDL_PushEvent(&user_event);
    return res;

}

int pushGoalEvent(GameElement* element,Level* level){
    SDL_Event user_event;
    user_event.type = SDL_USEREVENT;
    user_event.user.code = goalPositionEvent ;
    user_event.user.data1 = element;
    user_event.user.data2 = level;
    int res=SDL_PushEvent(&user_event);
    return res;

}
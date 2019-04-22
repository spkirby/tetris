#include "EventHandler.h"
#include "Game.h"
#include "SDL.h"

EventHandler::EventHandler(Game* parentObj)
{
    parent = parentObj;
}

void EventHandler::handleEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                break;
        }

        // keyboard messages
        // notify parent object
    }
}

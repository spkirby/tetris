#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Game.h"

class EventHandler
{
public:
    EventHandler(Game *parentObj);
    void handleEvents();

protected:
    Game *parent;
};

#endif // EVENTHANDLER_H

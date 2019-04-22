#ifndef GAME_H
#define GAME_H

#include "Graphics.h"
#include "Shape.h"
#include "Sound.h"
#include "SDL.h"

class Game
{
protected:
    enum State
    {
        STATE_NOT_STARTED = 0,
        STATE_TITLE       = 1,
        STATE_IN_GAME     = 2,
        STATE_GAME_OVER   = 3,
        STATE_QUITTING    = 4
    };

public:
    Game(Graphics& graphics, Sound& sound);
    virtual ~Game();
    void start();
    void play();
    void redraw();

protected:
    class GameEventHandler
    {
    public:
        GameEventHandler(Game *parentObj)
        {
            parent = parentObj;
        }

        bool isAnyKeyDown(const Uint8* keystate)
        {
            for (int i = 0; i <= SDL_NUM_SCANCODES; i++)
            {
                if (keystate[i] != 0)
                    return true;
            }

            return false;
        }

        void handleEvents()
        {
            SDL_Event event;
            parent->keyPressed = false;

            while(parent->state != STATE_QUITTING && SDL_PollEvent(&event))
            {
                // Handle SDL Events
                switch(event.type)
                {
                    case SDL_QUIT:
                        parent->state = STATE_QUITTING;
                        break;

                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {                        
                            case SDLK_ESCAPE:
                                parent->state = STATE_TITLE;
                                break;
                        
                            case SDLK_F4:
                                if(event.key.keysym.mod & KMOD_ALT)
                                    parent->state = STATE_QUITTING;
                                break;
                        
                            case SDLK_LALT:
                            case SDLK_RALT:
                                break;
                        
                            default:
                                parent->keyPressed = true;
                        }
                        break;
                }
            }
        }

    protected:
        Game *parent;
    };

    static const int FRAMES_PER_SECOND  = 25;
    static const int INITIAL_FALL_DELAY = 20;
    static const int MOVEMENT_RECHARGE_TIME = 2;

    Graphics& graphics;
    Sound& sound;

    bool keyPressed;
    State state;
    int level;
    int score;
    int fallDelay;
    int framesUntilFall;
    int framesUntilMove;
    int linesThisLevel, totalLines;
    Uint32 frameStart, timePerFrame;

    GameEventHandler *eventHandler;
    PlayField field;

    Shape *currentShape, *nextShape;
    const Uint8 *keystate;
    bool canRotate;

    void startFrame();
    void endFrame();
    void reset();
    bool isKeyDown(SDL_Keycode keycode);
};

#endif // GAME_H

#pragma once
#include "Graphics.h"
#include "PlayField.h"
#include "Shape.h"
#include "Sound.h"
#include "StatusPanel.h"
#include "SDL.h"

class Game
{
public:
    Game(Graphics& graphics, Sound& sound);
    virtual ~Game();
    void start();
    void play();
    void render();

protected:
    static const int FRAMES_PER_SECOND  = 25;
    static const int TIME_PER_FRAME = 1000 / FRAMES_PER_SECOND;
    static const int INITIAL_FALL_DELAY = 20;
    static const int MOVEMENT_RECHARGE_TIME = 2;

    enum State
    {
        STATE_NOT_STARTED = 0,
        STATE_TITLE = 1,
        STATE_IN_GAME = 2,
        STATE_GAME_OVER = 3,
        STATE_QUITTING = 4
    };

    enum Direction
    {
        DIRECTION_LEFT = -1,
        DIRECTION_RIGHT = 1
    };

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

    PlayField field;
    StatusPanel statusPanel;

    Shape *currentShape, *nextShape;
    const Uint8 *keystate;

    bool isAnyKeyDown();
    void handleEvents();
    bool canMoveShape(int xOffset, int yOffset);
    bool canRotate(Direction direction);
    void startFrame();
    void endFrame();
    void reset();
    bool isKeyDown(SDL_Keycode keycode);
};

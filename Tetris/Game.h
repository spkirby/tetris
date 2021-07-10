#pragma once
#include "GameState.h"
#include "Graphics.h"
#include "PlayField.h"
#include "Shape.h"
#include "Sound.h"
#include "StatusPanel.h"
#include "SDL.h"
#include "Enums.h"
#include "Keyboard.h"

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

    Graphics& graphics;
    Sound& sound;

    bool keyPressed;
    GameState state;
    int level;
    int score;
    int fallDelay;
    int framesUntilFall;
    int framesUntilMove;
    int linesThisLevel, totalLines;
    Uint32 frameStart, timePerFrame;

    Keyboard keyboard;
    PlayField field;
    StatusPanel statusPanel;

    Shape *currentShape, *nextShape;
    const Uint8 *keystate;

    bool isAnyKeyDown();
    void handleEvents();
    bool tryMoveShape(Direction direction);
    bool canMoveShape(Direction direction);
    bool tryRotate(Direction direction);
    bool canRotate(Direction direction);
    void startFrame();
    void endFrame();
    void reset();
    bool isKeyDown(SDL_Keycode keycode);
};

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
    Keyboard keyboard;
    PlayField field;
    StatusPanel statusPanel;
    GameState state;
    Shape* nextShape;
    bool keyPressed;
    bool rotateLocked;
    int level;
    int score;
    int fallDelay;
    int framesUntilFall;
    int framesUntilMove;
    int linesThisLevel, totalLines;
    Uint32 frameStart, timePerFrame;

    void checkForMove();
    void endFrame();
    void handleEvents();
    void moveShape();
    void reset();
    void startFrame();
    void update();
};

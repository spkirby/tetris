#pragma once
#include "Enums.h"
#include "GameState.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "PlayField.h"
#include "SDL.h"
#include "Shape.h"
#include "Sound.h"
#include "StatusPanel.h"

class Game
{
public:
    Game(Graphics& graphics, Sound& sound);
    void start();
    void play();
    void render();

protected:
    static const int FRAMES_PER_SECOND  = 25;
    static const int TIME_PER_FRAME = 1000 / FRAMES_PER_SECOND;
    static const int INITIAL_FALL_DELAY = 20;
    static const int MOVE_COOLDOWN_TIME = 2;
    static const Point FIELD_POSITION;
    static const Point LOGO_POSITION;
    static const Point NEXT_SHAPE_POSITION;
    static const Point STATUS_PANEL_POSITION;

    int fallCooldown;
    int fallDelay;
    PlayField field;
    Graphics& graphics;
    Keyboard keyboard;
    int level;
    int linesUntilNextLevel;
    int moveCooldown;
    Shape nextShape;
    bool rotateLocked;
    int score;
    Sound& sound;
    GameState state;
    StatusPanel statusPanel;
    int totalLines;

    void checkForCompletedLines();
    void checkForPlayerMove();
    Shape createRandomShape();
    void endFrame(Uint32 frameStart);
    ShapeType getRandomShapeType();
    void handleEvent(SDL_Event &event);
    void pollEvents();
    void reset();
    void showTitleScreen();
    Uint32 startFrame();
    void update();
    void waitForEvent();
};

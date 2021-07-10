#include "Enums.h"
#include "Game.h"
#include "Graphics.h"
#include "Point.h"
#include "Sound.h"
#include "Shape.h"
#include "SDL.h"

Game::Game(Graphics& graphics, Sound& sound) :
    graphics(graphics),
    sound(sound)
{
    keystate = SDL_GetKeyboardState(nullptr);
    state = STATE_NOT_STARTED;
    currentShape = nextShape = nullptr;
    fallDelay = INITIAL_FALL_DELAY;
    statusPanel.position = Point(100, 50);
}

Game::~Game()
{
    if(currentShape) delete currentShape;
    if(nextShape) delete nextShape;
}

void Game::start()
{
    state = STATE_TITLE;
    reset();
    render();

    while(state != STATE_QUITTING)
    {
        handleEvents();

        if(keyPressed)
        {
            sound.play(SOUND_START);
            reset();
            play();

            if(state != STATE_QUITTING)
            {
                state = STATE_TITLE;
                render();

                do // Wait until no keys are pressed
                {
                    handleEvents();
                }
                while(isAnyKeyDown());
            }
        }
    }

    state = STATE_NOT_STARTED;
}

void Game::reset()
{
    framesUntilFall = fallDelay;
    framesUntilMove = MOVEMENT_RECHARGE_TIME;
    linesThisLevel = 0;

    level = 1;
    score = 0;
    totalLines = 0;

    if(currentShape)
        delete currentShape;
    currentShape = Shape::createRandom();

    if(nextShape)
        delete nextShape;
    nextShape = Shape::createRandom();

    field.reset();
    graphics.clear(0, 0, 0);
}

void Game::play()
{
    state = STATE_IN_GAME;
    bool rotateLocked = false;

    while(state == STATE_IN_GAME)
    {
        startFrame();
        graphics.clear(0, 0, 0);

        handleEvents();

        if(currentShape)
        {
            if(framesUntilMove == 0)
            {
                bool hasMoved = false;

                if(isKeyDown(SDLK_a) && !rotateLocked)
                {
                    if (canRotate(DIRECTION_LEFT))
                    {
                        currentShape->rotateLeft();
                        sound.play(SOUND_ROTATE);
                        rotateLocked = true;
                    }
                }
                else if((isKeyDown(SDLK_s) || isKeyDown(SDLK_UP)) && !rotateLocked)
                {
                    if (canRotate(DIRECTION_RIGHT))
                    {
                        currentShape->rotateRight();
                        sound.play(SOUND_ROTATE);
                        rotateLocked = true;
                    }
                }
                else if (isKeyDown(SDLK_LEFT) && canMoveShape(-1, 0))
                {
                    currentShape->moveLeft();
                    hasMoved = true;
                }
                else if (isKeyDown(SDLK_RIGHT) && canMoveShape(1, 0))
                {
                    currentShape->moveRight();
                    hasMoved = true;
                }
                else if (isKeyDown(SDLK_DOWN))
                {
                    framesUntilFall = 0;
                }

                if (!isKeyDown(SDLK_a) && !isKeyDown(SDLK_s) && !isKeyDown(SDLK_UP))
                {
                    rotateLocked = false;
                }

                if (hasMoved)
                {
                    framesUntilMove = MOVEMENT_RECHARGE_TIME;
                }
            }
            else
            {
                framesUntilMove--;
            }


            if(framesUntilFall-- == 0)
            {
                if (canMoveShape(0, 1))
                {
                    currentShape->moveDown();
                }
                else  // Shape has landed
                {
                    if (field.isShapeInsideField(*currentShape))
                    {
                        field.absorbShape(*currentShape);

                        int completeLines = field.checkForLines(currentShape);

                        if(completeLines > 0)
                            sound.play(SOUND_LINE);
                        else
                            sound.play(SOUND_THUD);

                        switch(completeLines)
                        {
                            case 1: score += 40   * level; break;
                            case 2: score += 100  * level; break;
                            case 3: score += 300  * level; break;
                            case 4: score += 1200 * level; break;
                            default: break;
                        }

                        totalLines += completeLines;
                        linesThisLevel += completeLines;

                        if(linesThisLevel >= 10)
                        {
                            level++;
                            linesThisLevel -= 10;

                            if(fallDelay > 0)
                                fallDelay -= 2;
                        }

                        framesUntilMove = 0;
                    }
                    else // Shape is outside the well - game over!
                    {
                        state = STATE_GAME_OVER;
                        sound.play(SOUND_GAME_OVER);
                    }

                    delete currentShape;
                    currentShape = nullptr;
                }

                framesUntilFall = fallDelay;
            }
        }

        if(currentShape == nullptr && !field.isAnimating())
        {
            currentShape = nextShape;
            nextShape = Shape::createRandom();
        }

        if(field.update())
            sound.play(SOUND_THUD);

        render();
        endFrame();
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    keyPressed = false;

    while (state != STATE_QUITTING && SDL_PollEvent(&event))
    {
        // Handle SDL Events
        switch (event.type)
        {
            case SDL_QUIT:
                state = STATE_QUITTING;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        state = STATE_TITLE;
                        break;

                    case SDLK_F4:
                        if (event.key.keysym.mod & KMOD_ALT)
                            state = STATE_QUITTING;
                        break;

                    case SDLK_LALT:
                    case SDLK_RALT:
                        break;

                    default:
                        keyPressed = true;
                }
                break;
        }
    }
}

bool Game::canMoveShape(int xOffset, int yOffset)
{
    Point pos = currentShape->getGridPos();
    return field.checkValidMove(pos.x + xOffset, pos.y + yOffset, *currentShape);
}

bool Game::canRotate(Direction direction)
{
    Shape shapeCopy(*currentShape);

    if (direction == DIRECTION_LEFT)
        shapeCopy.rotateLeft();
    else
        shapeCopy.rotateRight();

    Point pos = shapeCopy.getGridPos();
    bool isValid = field.checkValidMove(pos.x, pos.y, shapeCopy);

    return isValid;
}

void Game::startFrame()
{
    frameStart = SDL_GetTicks();
}

void Game::endFrame()
{
    Uint32 timeLeft = TIME_PER_FRAME - (SDL_GetTicks() - frameStart);

    if(timeLeft > 0 && timeLeft < TIME_PER_FRAME)
        SDL_Delay(timeLeft);
}

void Game::render()
{
    if(state == STATE_IN_GAME)
    {
        field.draw(graphics);

        if(currentShape)
            currentShape->draw(graphics, field.getScreenPos());

        if(nextShape)
            nextShape->draw(graphics, 100, 100);
    }
    else if(state == STATE_TITLE)
    {
        field.drawOutline(graphics);
        graphics.draw(IMAGE_LOGO, 582, 242);
    }

    statusPanel.level = level;
    statusPanel.score = score;
    statusPanel.lines = linesThisLevel;
    statusPanel.render(graphics);

    graphics.update();
}

bool Game::isKeyDown(SDL_Keycode keycode)
{
    return keystate[SDL_GetScancodeFromKey(keycode)] != 0;
}

bool Game::isAnyKeyDown()
{
    for (int i = 0; i <= SDL_NUM_SCANCODES; i++)
    {
        if (keystate[i] != 0)
            return true;
    }

    return false;
}

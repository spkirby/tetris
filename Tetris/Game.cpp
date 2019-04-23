#include "Game.h"
#include "Graphics.h"
#include "Sound.h"
#include "Shape.h"
#include "SDL.h"

Game::Game(Graphics& graphics, Sound& sound) :
    graphics(graphics),
    sound(sound)
{
    eventHandler = new GameEventHandler(this);
    keystate = SDL_GetKeyboardState(NULL);

    state = STATE_NOT_STARTED;
    currentShape = nextShape = NULL;
    timePerFrame = 1000 / FRAMES_PER_SECOND;
    fallDelay = INITIAL_FALL_DELAY;
}

Game::~Game()
{
    if(currentShape) delete currentShape;
    if(nextShape) delete nextShape;
    delete eventHandler;
}

void Game::start()
{
    state = STATE_TITLE;
    reset();
    redraw();

    while(state != STATE_QUITTING)
    {
        eventHandler->handleEvents();

        if(keyPressed)
        {
            sound.play(SOUND_START);
            reset();
            play();

            if(state != STATE_QUITTING)
            {
                state = STATE_TITLE;
                redraw();

                do // Wait until no keys are pressed
                {
                    eventHandler->handleEvents();
                }
                while(eventHandler->isAnyKeyDown(keystate));
            }
        }
    }

    state = STATE_NOT_STARTED;
}

void Game::reset()
{
    framesUntilFall = fallDelay;
    framesUntilMove = MOVEMENT_RECHARGE_TIME;
    linesThisLevel  = totalLines = 0;
    level = 1;
    score = 0;

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

        eventHandler->handleEvents();

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
                    currentShape = NULL;
                }

                framesUntilFall = fallDelay;
            }
        }

        if(currentShape == NULL  &&  field.isAnimating() == false)
        {
            currentShape = nextShape;
            nextShape = Shape::createRandom();
        }

        if(field.update())
            sound.play(SOUND_THUD);

        redraw();
        endFrame();
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
    Uint32 timeLeft = timePerFrame - (SDL_GetTicks() - frameStart);

    if(timeLeft > 0 && timeLeft < timePerFrame)
        SDL_Delay(timeLeft);
}

void Game::redraw()
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

    graphics.draw(IMAGE_STATUS_NEXT, 100, 50);

    graphics.draw(IMAGE_STATUS_LINES, 100, 250);
    graphics.drawNumber(totalLines, 100, 300);

    graphics.draw(IMAGE_STATUS_LEVEL, 100, 400);
    graphics.drawNumber(level, 100, 450);

    graphics.draw(IMAGE_STATUS_SCORE, 100, 550);
    graphics.drawNumber(score, 100, 600);

    graphics.redraw();
}

bool Game::isKeyDown(SDL_Keycode keycode)
{
    return keystate[SDL_GetScancodeFromKey(keycode)] != 0;
}
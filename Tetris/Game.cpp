#include "Enums.h"
#include "Game.h"
#include "GameState.h"
#include "Graphics.h"
#include "Point.h"
#include "Sound.h"
#include "Shape.h"
#include "SDL.h"

Game::Game(Graphics& graphics, Sound& sound) :
    graphics(graphics),
    sound(sound)
{
    state = GameState::NotStarted;
    nextShape = nullptr;
    fallDelay = INITIAL_FALL_DELAY;
    statusPanel.position = Point(100, 50);
}

Game::~Game()
{
    if (nextShape)
    {
        delete nextShape;
    }
}

void Game::start()
{
    state = GameState::Title;
    reset();
    render();

    while (state != GameState::Quitting)
    {
        handleEvents();

        if (keyPressed)
        {
            sound.play(SOUND_START);
            reset();
            play();

            if (state != GameState::Quitting)
            {
                state = GameState::Title;
                render();

                do // Wait until no keys are pressed
                {
                    handleEvents();
                }
                while (keyboard.isAnyKeyDown());
            }
        }
    }

    state = GameState::NotStarted;
}

void Game::reset()
{
    framesUntilFall = fallDelay;
    framesUntilMove = MOVEMENT_RECHARGE_TIME;
    linesThisLevel = 0;

    level = 1;
    score = 0;
    totalLines = 0;

    if (nextShape)
    {
        delete nextShape;
    }

    field.reset();
    field.setShape(Shape::createRandom());

    nextShape = Shape::createRandom();
    nextShape->position = Point(100, 100);

    graphics.clear(0, 0, 0);
}

void Game::play()
{
    state = GameState::InGame;

    while (state == GameState::InGame)
    {
        startFrame();
        handleEvents();
        update();
        render();
        endFrame();
    }
}

void Game::update()
{
    rotateLocked = false;

    if (field.hasShape())
    {
        if (framesUntilMove-- == 0)
        {
            checkForMove();
        }

        if (framesUntilFall-- == 0)
        {
            moveShape();
            framesUntilFall = fallDelay;
        }
    }

    if (!field.hasShape() && !field.isAnimating())
    {
        field.setShape(nextShape);

        nextShape = Shape::createRandom();
        nextShape->position = Point(100, 100);
    }

    if (field.update())
    {
        sound.play(SOUND_THUD);
    }
}

void Game::checkForMove()
{
    bool hasMoved = false;

    if (keyboard.isKeyDown(SDLK_a) && !rotateLocked)
    {
        if (field.tryRotateShape(Direction::Left))
        {
            sound.play(SOUND_ROTATE);
            rotateLocked = true;
        }
    }
    else if ((keyboard.isKeyDown(SDLK_s) || keyboard.isKeyDown(SDLK_UP)) && !rotateLocked)
    {
        if (field.tryRotateShape(Direction::Right))
        {
            sound.play(SOUND_ROTATE);
            rotateLocked = true;
        }
    }
    else if (keyboard.isKeyDown(SDLK_LEFT) && field.tryMoveShape(Direction::Left))
    {
        hasMoved = true;
    }
    else if (keyboard.isKeyDown(SDLK_RIGHT) && field.tryMoveShape(Direction::Right))
    {
        hasMoved = true;
    }
    else if (keyboard.isKeyDown(SDLK_DOWN))
    {
        framesUntilFall = 0;
    }

    if (!keyboard.isKeyDown(SDLK_a) && !keyboard.isKeyDown(SDLK_s) && !keyboard.isKeyDown(SDLK_UP))
    {
        rotateLocked = false;
    }

    if (hasMoved)
    {
        framesUntilMove = MOVEMENT_RECHARGE_TIME;
    }
}

void Game::moveShape()
{
    if (!field.tryMoveShape(Direction::Down)) // Shape has landed
    {
        int completedLines = 0;
        sound.play(SOUND_THUD);

        if (field.tryAbsorbShape(completedLines))
        {
            if (completedLines > 0)
            {
                sound.play(SOUND_LINE);
            }

            switch (completedLines)
            {
            case 1: score += 40 * level; break;
            case 2: score += 100 * level; break;
            case 3: score += 300 * level; break;
            case 4: score += 1200 * level; break;
            default: break;
            }

            totalLines += completedLines;
            linesThisLevel += completedLines;

            if (linesThisLevel >= 10)
            {
                level++;
                linesThisLevel -= 10;

                if (fallDelay > 0)
                {
                    fallDelay -= 2;
                }
            }

            framesUntilMove = 0;
        }
        else // Shape is outside the well - game over!
        {
            state = GameState::GameOver;
            sound.play(SOUND_GAME_OVER);
        }
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    keyPressed = false;
    
    // TODO: Stop this pegging 100% CPU!!
    while (state != GameState::Quitting && SDL_PollEvent(&event))
    {
        // Handle SDL Events
        switch (event.type)
        {
            case SDL_QUIT:
                state = GameState::Quitting;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        state = GameState::Title;
                        break;

                    case SDLK_F4:
                        if (event.key.keysym.mod & KMOD_ALT)
                            state = GameState::Quitting;
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

void Game::startFrame()
{
    frameStart = SDL_GetTicks();
}

void Game::endFrame()
{
    Uint32 timeLeft = TIME_PER_FRAME - (SDL_GetTicks() - frameStart);

    if (timeLeft > 0 && timeLeft < TIME_PER_FRAME)
    {
        SDL_Delay(timeLeft);
    }
}

void Game::render()
{
    graphics.clear(0, 0, 0);

    if (state == GameState::InGame)
    {
        field.render(graphics);

        if (nextShape)
        {
            nextShape->render(graphics);
        }
    }
    else if (state == GameState::Title)
    {
        field.drawOutline(graphics);
        graphics.renderImage(ImageId::Logo, Point(582, 242));
    }

    statusPanel.setLevel(level);
    statusPanel.setScore(score);
    statusPanel.setLines(linesThisLevel);
    statusPanel.render(graphics);

    graphics.update();
}

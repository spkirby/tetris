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
    sound(sound),
    nextShape(nullptr)
{
    state = GameState::NotStarted;
    field.position = Point(550, 50);
    statusPanel.position = Point(100, 50);
    
    reset();
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
    reset();

    do
    {
        state = GameState::Title;
        showTitleScreen();

        if (state != GameState::Quitting)
        {
            state = GameState::InGame;

            sound.play(SOUND_START);
            reset();
            play();
        }
    }
    while (state != GameState::Quitting);
}

void Game::reset()
{
    fallDelay = INITIAL_FALL_DELAY;
    fallCooldown = fallDelay;
    moveCooldown = MOVE_COOLDOWN_TIME;
    rotateLocked = false;

    level = 1;
    score = 0;
    totalLines = 0;
    linesUntilNextLevel = 10;

    if (nextShape)
    {
        delete nextShape;
    }

    field.reset();
    field.setShape(Shape::createRandom());

    nextShape = Shape::createRandom();
    nextShape->position = Point(100, 100);
}

void Game::showTitleScreen()
{
    render();

    while (state != GameState::Quitting && keyboard.isAnyKeyDown())
    {
        waitForEvent();
    }

    while (state != GameState::Quitting && !keyboard.isAnyKeyDown())
    {
        waitForEvent();
    }

    if (state != GameState::Quitting)
    {
        state = GameState::InGame;
    }
}

void Game::play()
{
    while (state == GameState::InGame)
    {
        Uint32 frameStart = startFrame();
        pollEvents();
        update();
        render();
        endFrame(frameStart);
    }
}

void Game::update()
{
    if (field.hasShape())
    {
        if (moveCooldown == 0)
        {
            checkForPlayerMove();
        }
        else
        {
            moveCooldown--;
        }

        if (fallCooldown-- == 0)
        {
            if (!field.tryMoveShape(Direction::Down))
            {
                checkForCompletedLines();
            }
            
            fallCooldown = fallDelay;
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

void Game::checkForPlayerMove()
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
    else if (keyboard.isKeyDown(SDLK_LEFT))
    {
        hasMoved = field.tryMoveShape(Direction::Left);
    }
    else if (keyboard.isKeyDown(SDLK_RIGHT))
    {
        hasMoved = field.tryMoveShape(Direction::Right);
    }
    else if (keyboard.isKeyDown(SDLK_DOWN))
    {
        fallCooldown = 0;
    }

    if (!keyboard.isKeyDown(SDLK_a) && !keyboard.isKeyDown(SDLK_s) && !keyboard.isKeyDown(SDLK_UP))
    {
        rotateLocked = false;
    }

    if (hasMoved)
    {
        moveCooldown = MOVE_COOLDOWN_TIME;
    }
}

void Game::checkForCompletedLines()
{
    sound.play(SOUND_THUD);

    if (field.tryAbsorbShape())
    {
        int completedLines = field.getCompletedLineCount();

        if (completedLines > 0)
        {
            sound.play(SOUND_LINE);

            switch (completedLines)
            {
            case 1:
                score += 40 * level;
                break;
            case 2:
                score += 100 * level;
                break;
            case 3:
                score += 300 * level;
                break;
            default:
                score += 1200 * level;
                break;
            }

            totalLines += completedLines;
            linesUntilNextLevel -= completedLines;

            if (linesUntilNextLevel <= 0)
            {
                level++;
                linesUntilNextLevel += 10;
                fallDelay = std::max(1, fallDelay - 2);
            }
        }

        moveCooldown = 0;
    }
    else // Shape is outside the well - game over!
    {
        state = GameState::GameOver;
        sound.play(SOUND_GAME_OVER);
    }
}

void Game::pollEvents()
{
    SDL_Event event;

    while (state != GameState::Quitting && SDL_PollEvent(&event))
    {
        handleEvent(event);
    }
}

void Game::waitForEvent()
{
    SDL_Event event;
    SDL_WaitEvent(&event);
    handleEvent(event);
}

void Game::handleEvent(SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_QUIT:
            state = GameState::Quitting;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    if (state == GameState::Title)
                    {
                        state = GameState::Quitting;
                    }
                    else
                    {
                        state = GameState::Title;
                    }
                    break;

                case SDLK_F4:
                    if (event.key.keysym.mod & KMOD_ALT)
                    {
                        state = GameState::Quitting;
                    }
                    break;

                case SDLK_LALT:
                case SDLK_RALT:
                    break;
            }
            break;
    }
}

Uint32 Game::startFrame()
{
    return SDL_GetTicks();
}

void Game::endFrame(Uint32 frameStart)
{
    Uint32 timeRemaining = TIME_PER_FRAME - (SDL_GetTicks() - frameStart);

    if (timeRemaining > 0 && timeRemaining < TIME_PER_FRAME)
    {
        SDL_Delay(timeRemaining);
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
    statusPanel.setLines(totalLines);
    statusPanel.render(graphics);

    graphics.update();
}

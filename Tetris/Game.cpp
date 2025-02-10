#include "Enums.h"
#include "Game.h"
#include "GameState.h"
#include "Graphics.h"
#include "Point.h"
#include "Sound.h"
#include "Shape.h"
#include "SDL.h"

const Point Game::FIELD_POSITION = Point(550, 50);
const Point Game::LOGO_POSITION = Point(582, 242);
const Point Game::NEXT_SHAPE_POSITION = Point(100, 100);
const Point Game::STATUS_PANEL_POSITION = Point(100, 50);

Game::Game(Graphics& graphics, Sound& sound) :
    graphics(graphics),
    sound(sound),
    nextShape(Shape(ShapeType::ShapeI))
{
    state = GameState::NotStarted;
    field.position = FIELD_POSITION;
    statusPanel.position = STATUS_PANEL_POSITION;
    
    reset();
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

            sound.play(SoundId::StartGame);
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

    field.reset();
    field.setShapeType(getRandomShapeType());

    nextShape = createRandomShape();
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
        field.setShapeType(nextShape.getType());
        nextShape = createRandomShape();
    }

    if (field.update())
    {
        sound.play(SoundId::Thud);
    }
}

void Game::checkForPlayerMove()
{
    bool hasMoved = false;

    if (keyboard.isKeyDown(SDLK_a) && !rotateLocked)
    {
        if (field.tryRotateShape(Direction::Left))
        {
            sound.play(SoundId::Rotate);
            rotateLocked = true;
        }
    }
    else if ((keyboard.isKeyDown(SDLK_s) || keyboard.isKeyDown(SDLK_UP)) && !rotateLocked)
    {
        if (field.tryRotateShape(Direction::Right))
        {
            sound.play(SoundId::Rotate);
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
    sound.play(SoundId::Thud);

    if (field.tryAbsorbShape())
    {
        int completedLines = field.getCompletedLineCount();

        if (completedLines > 0)
        {
            sound.play(SoundId::LineComplete);

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
        sound.play(SoundId::GameOver);
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
        nextShape.render(graphics);
    }
    else if (state == GameState::Title)
    {
        field.drawOutline(graphics);
        graphics.renderImage(ImageId::Logo, LOGO_POSITION);
    }

    statusPanel.setLevel(level);
    statusPanel.setScore(score);
    statusPanel.setLines(totalLines);
    statusPanel.render(graphics);

    graphics.update();
}

ShapeType Game::getRandomShapeType()
{
    return (ShapeType)(rand() % (int)ShapeType::Count);
}

Shape Game::createRandomShape()
{
    return Shape(getRandomShapeType(), NEXT_SHAPE_POSITION);
}

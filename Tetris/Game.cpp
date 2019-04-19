#include <cstdlib>
#include "Game.h"
#include "Graphics.h"
#include "Sound.h"
#include "Shape.h"
#include "SDL.h"

Game::Game()
{
	eventHandler = new GameEventHandler(this);
	keystate = SDL_GetKeyboardState(NULL);

	state = STATE_NOTSTARTED;
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
			Sound::play(Sound::START);
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

	state = STATE_NOTSTARTED;
}


void Game::reset()
{
	framesUntilFall = fallDelay;
	framesUntilMove = MOVEMENT_RECHARGE_TIME;
	linesThisLevel  = totalLines = 0;
	level = 1;
	score = 0;
	canRotate = true;

	if(currentShape)
		delete currentShape;
	currentShape = new Shape((Shape::ShapeType)(rand() % Shape::NUM_OF_SHAPES), &field);

	if(nextShape)
		delete nextShape;
	nextShape = new Shape((Shape::ShapeType)(rand() % Shape::NUM_OF_SHAPES), &field);

	field.reset();
}


void Game::play()
{
	state = STATE_INGAME;

	while(state == STATE_INGAME)
	{
		startFrame();
		Graphics::clear(0, 0, 0);

		eventHandler->handleEvents();

		if(currentShape)
		{
			if(framesUntilMove == 0)
			{
				bool hasMoved = false;

				if(isKeyDown(SDLK_a) && canRotate)
				{
					hasMoved = currentShape->rotateLeft();
					if(hasMoved)
						Sound::play(Sound::ROTATE);
					canRotate = false;
				}
				else if((isKeyDown(SDLK_s) || isKeyDown(SDLK_UP)) && canRotate)
				{
					hasMoved = currentShape->rotateRight();
					if(hasMoved)
						Sound::play(Sound::ROTATE);
					canRotate = false;
				}
				else if(isKeyDown(SDLK_LEFT))
					hasMoved = currentShape->moveLeft();
				else if(isKeyDown(SDLK_RIGHT))
					hasMoved = currentShape->moveRight();
				else if(isKeyDown(SDLK_DOWN))
					framesUntilFall = 0;

				if(!isKeyDown(SDLK_a) && !isKeyDown(SDLK_s) && !isKeyDown(SDLK_UP))
					canRotate = true;

				if(hasMoved)
					framesUntilMove = MOVEMENT_RECHARGE_TIME;
			}
			else
				framesUntilMove--;


			if(framesUntilFall-- == 0)
			{
				if(currentShape->moveDown() == false) // Shape has landed
				{
					if(currentShape->stop()) // Shape is within the well
					{
						int completeLines = field.checkForLines(currentShape);

						if(completeLines > 0)
							Sound::play(Sound::LINE);
						else
							Sound::play(Sound::THUD);

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
						state = STATE_GAMEOVER;
						Sound::play(Sound::GAMEOVER);
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
			nextShape    = new Shape((Shape::ShapeType)(rand() % Shape::NUM_OF_SHAPES), &field);
		}

		if(field.update())
			Sound::play(Sound::THUD);

		redraw();
		endFrame();
	}
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
	if(state == STATE_INGAME)
	{
		field.draw();

		if(currentShape)
			currentShape->draw();

		if(nextShape)
			nextShape->draw(100, 100);
	}
	else if(state == STATE_TITLE)
	{
		field.drawOutline();
		Graphics::draw(Graphics::LOGO, 582, 242);
	}

	Graphics::draw(Graphics::STATUS_NEXT, 100, 50);

	Graphics::draw(Graphics::STATUS_LINES, 100, 250);
	Graphics::drawNumber(totalLines, 100, 300);

	Graphics::draw(Graphics::STATUS_LEVEL, 100, 400);
	Graphics::drawNumber(level, 100, 450);

	Graphics::draw(Graphics::STATUS_SCORE, 100, 550);
	Graphics::drawNumber(score, 100, 600);

	Graphics::redraw();
}


bool Game::isKeyDown(SDL_Keycode keycode)
{
    return keystate[SDL_GetScancodeFromKey(keycode)] != 0;
}
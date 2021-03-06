#ifndef GAME_H
#define GAME_H

#include "Shape.h"
#include <SDL/SDL.h>

class Game
{
protected:
	enum State
	{
		STATE_NOTSTARTED = 0,
		STATE_TITLE      = 1,
		STATE_INGAME     = 2,
		STATE_GAMEOVER   = 3,
		STATE_QUITTING   = 4
	};

public:
	Game();
	virtual ~Game();
	void start();
	void play();
	void redraw();

protected:
	class GameEventHandler
	{
	public:
		GameEventHandler(Game *parentObj)
		{
			parent = parentObj;
		}

		bool isKeyDown(Uint8* keystate)
		{
			bool keyDown = false;

			for(int i = SDLK_FIRST; i <= SDLK_LAST; i++)
				if(keystate[i] != 0)
					keyDown = true;

			return keyDown;
		}

		void handleEvents()
		{
			SDL_Event event;
			parent->keyPressed = false;

			while(parent->state != STATE_QUITTING && SDL_PollEvent(&event))
			{
				// Handle SDL Events
				switch(event.type)
				{
					case SDL_QUIT:
						parent->state = STATE_QUITTING;
						break;

					case SDL_KEYDOWN:
						switch(event.key.keysym.sym)
						{						
							case SDLK_ESCAPE:
								parent->state = STATE_TITLE;
								break;
						
							case SDLK_F4:
								if(event.key.keysym.mod & KMOD_ALT)
									parent->state = STATE_QUITTING;
								break;
						
							case SDLK_LALT:
							case SDLK_RALT:
								break;
						
							default:
								parent->keyPressed = true;
						}
						break;

					case SDL_VIDEOEXPOSE:
						parent->redraw();
						break;
				}
			}
		}

	protected:
		Game *parent;
	};

	static const int FRAMES_PER_SECOND  = 25;
	static const int INITIAL_FALL_DELAY = 20;
	static const int MOVEMENT_RECHARGE_TIME = 2;

	bool keyPressed;
	State state;
	int level;
	int score;
	int fallDelay;
	int framesUntilFall;
	int framesUntilMove;
	int linesThisLevel, totalLines;
	Uint32 frameStart, timePerFrame;

	GameEventHandler *eventHandler;
	PlayField field;

	Shape *currentShape, *nextShape;
	Uint8 *keystate;
	bool canRotate;

	void startFrame();
	void endFrame();
	void reset();
};

#endif // GAME_H

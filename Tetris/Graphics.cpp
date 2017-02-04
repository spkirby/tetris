#include "Graphics.h"
#include "Shape.h"
#include <stdio.h>
#include <SDL/SDL.h>

SDL_Surface* Graphics::screen = NULL;
SDL_Surface* Graphics::icon   = NULL;
SDL_Surface* Graphics::images[NUM_OF_IMAGES];
SDL_Rect Graphics::digitRects[10] =
{
	{   2, 0, 56, 43 },
	{  67, 0, 40, 43 },
	{ 113, 0, 50, 43 },
	{ 174, 0, 53, 43 },
	{ 236, 0, 50, 43 },
	{ 298, 0, 50, 43 },
	{ 360, 0, 50, 43 },
	{ 422, 0, 44, 43 },
	{ 478, 0, 50, 43 },
	{ 540, 0, 49, 43 }
};

void Graphics::init()
{
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF);
	setIcon();

	if(!screen)
		throw SDL_GetError();

	// Fill image pointer array with NULLs
	for(int i=0; i < NUM_OF_IMAGES; i++)
		images[i] = NULL;

	loadImages();
}

void Graphics::shutdown()
{
	for(int i=0; i < NUM_OF_IMAGES; i++)
	{
		SDL_FreeSurface(images[i]);
		images[i] = NULL;
	}

	// Don't free framebuffer surface; it's freed by SDL_Quit()
}

void Graphics::setIcon()
{
	icon = loadImageFile("gfx/icon.bmp");
	SDL_SetColorKey(icon, SDL_SRCCOLORKEY, SDL_MapRGB(icon->format, 255, 255, 255));
	SDL_WM_SetIcon(icon, NULL);
}

void Graphics::loadImages()
{
	int blockSize = Shape::BLOCK_SIZE;

	SDL_Surface* blocks = loadImageFile("gfx/blocks.bmp");
	images[BLOCK_EMPTY] = getSubImage(blocks, blockSize * 0, 0, blockSize, blockSize);
	images[BLOCK_I]     = getSubImage(blocks, blockSize * 1, 0, blockSize, blockSize);
	images[BLOCK_J]     = getSubImage(blocks, blockSize * 2, 0, blockSize, blockSize);
	images[BLOCK_L]     = getSubImage(blocks, blockSize * 3, 0, blockSize, blockSize);
	images[BLOCK_O]     = getSubImage(blocks, blockSize * 4, 0, blockSize, blockSize);
	images[BLOCK_S]     = getSubImage(blocks, blockSize * 5, 0, blockSize, blockSize);
	images[BLOCK_T]     = getSubImage(blocks, blockSize * 6, 0, blockSize, blockSize);
	images[BLOCK_Z]     = getSubImage(blocks, blockSize * 7, 0, blockSize, blockSize);
	images[BOUNDARY]    = getSubImage(blocks, blockSize * 8, 0, blockSize, blockSize);
	SDL_FreeSurface(blocks);

	images[STATUS_LINES] = loadImageFile("gfx/lines.bmp");
	images[STATUS_LEVEL] = loadImageFile("gfx/level.bmp");
	images[STATUS_SCORE] = loadImageFile("gfx/score.bmp");
	images[STATUS_NEXT]  = loadImageFile("gfx/next.bmp");
	images[DIGITS]       = loadImageFile("gfx/digits.bmp");
	images[LOGO]         = loadImageFile("gfx/logo.bmp");
}


SDL_Surface* Graphics::loadImageFile(const char* filename)
{
	SDL_Surface *raw, *image;

	if( ( raw   = SDL_LoadBMP(filename)  ) == NULL ||
		( image = SDL_DisplayFormat(raw) ) == NULL )
		throw SDL_GetError();

	SDL_FreeSurface(raw);
	return image;
}


SDL_Surface* Graphics::getSubImage(SDL_Surface *src, int x, int y, int w, int h)
{
	SDL_Surface *sub;
	SDL_Rect srcRect  = {x, y, w, h};
	SDL_Rect destRect = {0, 0, 0, 0};

	sub = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, src->format->BitsPerPixel,
		src->format->Rmask, src->format->Gmask,
		src->format->Bmask, src->format->Amask);

	if(sub)
		SDL_BlitSurface(src, &srcRect, sub, &destRect);
	else
		throw SDL_GetError();

	return sub;
}


void Graphics::clear(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, r, g, b));
}


void Graphics::draw(ImageID imageIndex, int x, int y)
{
	SDL_Rect dest = { x, y, 0, 0 };
	SDL_BlitSurface(images[imageIndex], NULL, screen, &dest);
}


void Graphics::drawNumber(int num, int x, int y)
{
	if(num < 0)
		throw "Invalid number";
	else if(num > 999999)
		num = 999999;

	SDL_Rect dest = { x, y };

	char buffer[7]; // "999999\0"
	sprintf(buffer, "%d", num);

	for(int i=0; buffer[i]; i++)
	{
		int index = buffer[i] - '0';
		SDL_BlitSurface(images[DIGITS], &digitRects[index], screen, &dest);
		dest.x += digitRects[index].w + 4;
	}
}


void Graphics::redraw()
{
	SDL_Flip(screen);
}

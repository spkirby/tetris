#include "Graphics.h"
#include "Shape.h"
#include <stdio.h>
#include "SDL.h"

SDL_Window* Graphics::window = NULL;
SDL_Renderer* Graphics::renderer = NULL;
SDL_Surface* Graphics::icon   = NULL;
SDL_Texture* Graphics::images[NUM_OF_IMAGES];
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
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Tetris");

	setIcon();

	// Fill image pointer array with NULLs
	for(int i=0; i < NUM_OF_IMAGES; i++)
		images[i] = NULL;

	loadImages();
}

void Graphics::shutdown()
{
	for(int i=0; i < NUM_OF_IMAGES; i++)
	{
        SDL_DestroyTexture(images[i]);
		images[i] = NULL;
	}

	// Don't free framebuffer surface; it's freed by SDL_Quit()
}

void Graphics::setIcon()
{
	icon = loadImageFile("gfx/icon.bmp");
	SDL_SetColorKey(icon, SDL_TRUE, SDL_MapRGB(icon->format, 255, 255, 255));
	SDL_SetWindowIcon(window, icon);
}

void Graphics::loadImages()
{
	int blockSize = Shape::BLOCK_SIZE;

	SDL_Surface* blocks = loadImageFile("gfx/blocks.bmp");
	images[BLOCK_EMPTY] = getSubTexture(blocks, blockSize * 0, 0, blockSize, blockSize);
	images[BLOCK_I]     = getSubTexture(blocks, blockSize * 1, 0, blockSize, blockSize);
	images[BLOCK_J]     = getSubTexture(blocks, blockSize * 2, 0, blockSize, blockSize);
	images[BLOCK_L]     = getSubTexture(blocks, blockSize * 3, 0, blockSize, blockSize);
	images[BLOCK_O]     = getSubTexture(blocks, blockSize * 4, 0, blockSize, blockSize);
	images[BLOCK_S]     = getSubTexture(blocks, blockSize * 5, 0, blockSize, blockSize);
	images[BLOCK_T]     = getSubTexture(blocks, blockSize * 6, 0, blockSize, blockSize);
	images[BLOCK_Z]     = getSubTexture(blocks, blockSize * 7, 0, blockSize, blockSize);
	images[BOUNDARY]    = getSubTexture(blocks, blockSize * 8, 0, blockSize, blockSize);
	SDL_FreeSurface(blocks);

	images[STATUS_LINES] = loadTexture("gfx/lines.bmp");
	images[STATUS_LEVEL] = loadTexture("gfx/level.bmp");
	images[STATUS_SCORE] = loadTexture("gfx/score.bmp");
	images[STATUS_NEXT]  = loadTexture("gfx/next.bmp");
	images[DIGITS]       = loadTexture("gfx/digits.bmp");
	images[LOGO]         = loadTexture("gfx/logo.bmp");
}


SDL_Surface* Graphics::loadImageFile(const char* filename)
{
	SDL_Surface *raw, *image;

	if( ( raw   = SDL_LoadBMP(filename)  ) == NULL ||
		( image = SDL_ConvertSurfaceFormat(raw, SDL_GetWindowPixelFormat(window), 0) ) == NULL )
		throw SDL_GetError();

	SDL_FreeSurface(raw);
	return image;
}

SDL_Texture* Graphics::loadTexture(const char* filename)
{
    SDL_Surface *surface = loadImageFile(filename);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

SDL_Texture* Graphics::getSubTexture(SDL_Surface *src, int x, int y, int w, int h)
{
    SDL_Surface *subSurface = SDL_CreateRGBSurface(
        0,
        w,
        h,
        src->format->BitsPerPixel,
        src->format->Rmask,
        src->format->Gmask,
        src->format->Bmask,
        src->format->Amask);

    if (subSurface == NULL)
    {
        throw SDL_GetError();
    }

    SDL_Rect srcRect = { x, y, w, h };
    SDL_Rect destRect = { 0, 0, 0, 0 };
    SDL_BlitSurface(src, &srcRect, subSurface, &destRect);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, subSurface);
    SDL_FreeSurface(subSurface);

    return texture;
}


void Graphics::clear(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_RenderClear(renderer);
	//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, r, g, b));
}


void Graphics::draw(ImageID imageIndex, int x, int y)
{
    Uint32 format;
    int access;
    int w, h;
    SDL_QueryTexture(images[imageIndex], &format, &access, &w, &h);

	SDL_Rect dest = { x, y, w, h };
    SDL_RenderCopy(renderer, images[imageIndex], NULL, &dest);
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
        SDL_RenderCopy(renderer, images[DIGITS], &digitRects[index], &dest);
		dest.x += digitRects[index].w + 4;
	}
}


void Graphics::redraw()
{
    SDL_RenderPresent(renderer);
}

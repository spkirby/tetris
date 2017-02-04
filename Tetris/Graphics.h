#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL/SDL.h>

class Graphics
{
public:
	enum ImageID
	{
		BLOCK_EMPTY = 0, // Must be zero
		BLOCK_I,
		BLOCK_J,
		BLOCK_L,
		BLOCK_O,
		BLOCK_S,
		BLOCK_T,
		BLOCK_Z,
		BOUNDARY,
		STATUS_LINES,
		STATUS_LEVEL,
		STATUS_SCORE,
		STATUS_NEXT,
		DIGITS,
		LOGO,
		NUM_OF_IMAGES
	};

	static void init();
	static void shutdown();
	static void clear(Uint8 r, Uint8 g, Uint8 b);
	static void draw(ImageID imageIndex, int x, int y);
	static void drawNumber(int num, int x, int y);
	static void redraw();

	static const int SCREEN_WIDTH  = 1024;
	static const int SCREEN_HEIGHT = 768;
	static const int SCREEN_DEPTH  = 32;

protected:
	static SDL_Surface* screen;  // The framebuffer surface
	static SDL_Surface* icon;
	static SDL_Surface* images[NUM_OF_IMAGES];
	static SDL_Rect digitRects[10];

private:
	Graphics();  // Graphics is a static class
	static void setIcon();
	static void loadImages();
	static SDL_Surface* loadImageFile(const char* filename);
	static SDL_Surface* getSubImage(SDL_Surface *src, int x, int y, int w, int h);
};

#endif // GRAPHICS_H

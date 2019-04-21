#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"

enum ImageId
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

class Graphics
{
public:
    Graphics();
    ~Graphics();

    void clear(Uint8 r, Uint8 g, Uint8 b);
    void draw(ImageId imageIndex, int x, int y);
    void drawNumber(int num, int x, int y);
    void redraw();

protected:
    static SDL_Rect digitRects[10];
    static const int SCREEN_WIDTH = 1024;
    static const int SCREEN_HEIGHT = 768;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* icon = nullptr;
    SDL_Texture* images[NUM_OF_IMAGES] = { nullptr };

    void setIcon();
    void loadImages();
    SDL_Surface* loadImageFile(const char* filename);
    SDL_Texture* loadTexture(const char* filename);
    SDL_Texture* getSubTexture(SDL_Surface *src, int x, int y, int w, int h);
};

#endif // GRAPHICS_H

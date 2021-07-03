#pragma once
#include "SDL.h"

enum ImageId
{
    IMAGE_BLOCK_EMPTY = 0, // Must be zero
    IMAGE_BLOCK_I,
    IMAGE_BLOCK_J,
    IMAGE_BLOCK_L,
    IMAGE_BLOCK_O,
    IMAGE_BLOCK_S,
    IMAGE_BLOCK_T,
    IMAGE_BLOCK_Z,
    IMAGE_BOUNDARY,
    IMAGE_STATUS_LINES,
    IMAGE_STATUS_LEVEL,
    IMAGE_STATUS_SCORE,
    IMAGE_STATUS_NEXT,
    IMAGE_DIGITS,
    IMAGE_LOGO,
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

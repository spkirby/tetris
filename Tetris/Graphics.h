#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include "enums.h"

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
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* icon;
    SDL_Texture* images[NUM_OF_IMAGES];
    SDL_Rect digitRects[10];

    static const int SCREEN_WIDTH = 1024;
    static const int SCREEN_HEIGHT = 768;

    void setIcon();
    void loadImages();
    SDL_Surface* loadImageFile(const char* filename);
    SDL_Texture* loadTexture(const char* filename);
    SDL_Texture* getSubTexture(SDL_Surface *src, int x, int y, int w, int h);
};

#endif // GRAPHICS_H

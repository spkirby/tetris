#pragma once
#include "Enums.h"
#include "Point.h"
#include "SDL.h"

class Graphics
{
public:
    Graphics();
    ~Graphics();

    void clear(Uint8 r, Uint8 g, Uint8 b);
    SDL_Texture* getImage(ImageId imageId);

    /// <summary>
    /// Renders a digit image at the given position. Returns the width
    /// of the rendered image.
    /// </summary>
    int renderDigit(int digit, Point& point);

    void renderImage(ImageId imageId, Point& point);
    void setClippingRect(SDL_Rect* rect);
    void update();

protected:
    static SDL_Rect digitRects[10];
    static const int SCREEN_WIDTH = 1024;
    static const int SCREEN_HEIGHT = 768;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* icon = nullptr;
    SDL_Texture* images[(int)ImageId::Count] = { nullptr };
    SDL_Rect* clippingRect = nullptr;

    SDL_Texture* getSubTexture(SDL_Surface *src, int x, int y, int w, int h);
    void loadImages();
    void loadBlockImages();
    SDL_Surface* loadImageFile(const char* filename);
    SDL_Texture* loadTexture(const char* filename);
    void render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect);
    void setIcon();
    SDL_Texture* setImage(ImageId imageId, SDL_Texture* image);
};

#include <cstdio>
#include <cmath>
#include <stdexcept>
#include "Enums.h"
#include "Graphics.h"
#include "Point.h"
#include "Shape.h"
#include "SDL.h"

// Static member. Position and size of digit graphics.
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

Graphics::Graphics()
{
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Tetris");
    setIcon();
    loadImages();
}

Graphics::~Graphics()
{
    for (int i = 0; i < (int)ImageId::Count; i++)
    {
        if (images[i])
        {
            SDL_DestroyTexture(images[i]);
            images[i] = nullptr;
        }
    }

    if (icon)
    {
        SDL_FreeSurface(icon);
        icon = nullptr;
    }

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

SDL_Texture* Graphics::getImage(ImageId imageId)
{
    if (imageId < (ImageId)0 || imageId >= ImageId::Count)
    {
        throw new std::out_of_range("Invalid Image ID");
    }

    return images[(int)imageId];
}

SDL_Texture* Graphics::setImage(ImageId imageId, SDL_Texture* image)
{
    SDL_Texture* oldImage = nullptr;

    if (images[(int)imageId])
    {
        oldImage = images[(int)imageId];
    }

    images[(int)imageId] = image;

    return oldImage;
}

void Graphics::setIcon()
{
    icon = loadImageFile("gfx/icon.bmp");
    SDL_SetColorKey(icon, SDL_TRUE, SDL_MapRGB(icon->format, 255, 255, 255));
    SDL_SetWindowIcon(window, icon);
}

void Graphics::loadImages()
{
    loadBlockImages();

    setImage(ImageId::StatusLines, loadTexture("gfx/lines.bmp"));
    setImage(ImageId::StatusLevel, loadTexture("gfx/level.bmp"));
    setImage(ImageId::StatusScore, loadTexture("gfx/score.bmp"));
    setImage(ImageId::StatusNext, loadTexture("gfx/next.bmp"));
    setImage(ImageId::Digits, loadTexture("gfx/digits.bmp"));
    setImage(ImageId::Logo, loadTexture("gfx/logo.bmp"));
}

void Graphics::loadBlockImages()
{
    int blockSize = Shape::BLOCK_SIZE;
    SDL_Surface* blocks = loadImageFile("gfx/blocks.bmp");

    for (int i = (int)ImageId::BlockEmpty; i <= (int)ImageId::Boundary; i++)
    {
        setImage((ImageId)i, getSubTexture(blocks, blockSize * i, 0, blockSize, blockSize));
    }

    SDL_FreeSurface(blocks);
}

SDL_Surface* Graphics::loadImageFile(const char* filename)
{
    SDL_Surface *raw = SDL_LoadBMP(filename);

    if (!raw)
    {
        throw SDL_GetError();
    }

    SDL_Surface *image = SDL_ConvertSurfaceFormat(raw, SDL_GetWindowPixelFormat(window), 0);
    
    if (!image)
    {
        throw SDL_GetError();
    }

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

    if (subSurface == nullptr)
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
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void Graphics::renderImage(ImageId imageId, Point& point)
{
    int w, h;
    SDL_QueryTexture(getImage(imageId), nullptr, nullptr, &w, &h);

    SDL_Rect destRect =
    {
        point.x,
        point.y,
        w,
        h
    };

    SDL_RenderCopy(renderer, getImage(imageId), nullptr, &destRect);
}

int Graphics::renderDigit(int digit, Point& point)
{
    if (digit < 0 || digit > 9)
    {
        throw new std::out_of_range("Invalid digit");
    }

    SDL_Rect* srcRect = &digitRects[digit];
    SDL_Rect destRect =
    {
         point.x,
         point.y,
         srcRect->w,
         srcRect->h
    };

    SDL_RenderCopy(renderer, getImage(ImageId::Digits), srcRect, &destRect);

    return destRect.w;
}

void Graphics::update()
{
    SDL_RenderPresent(renderer);
}

void Graphics::setClippingRect(SDL_Rect* rect)
{
    SDL_RenderSetClipRect(renderer, rect);
}

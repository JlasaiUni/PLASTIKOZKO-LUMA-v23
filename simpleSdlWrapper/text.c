
#include <SDL.h>
#include <SDL_ttf.h>

#include "graphics.h"
#include "imagen.h"
#include "text.h"
#include <stdio.h>

TTF_Font *font = 0;

void textuaGaitu(void)
{
    font = TTF_OpenFontIndex("OpenSans-Regular.ttf", 16, 0);
    if (!font)
    {
        printf("TTF_OpenFontIndex: %s\n", TTF_GetError());
        // handle error
    }
}

void textuaIdatzi(int x, int y, char *str)
{
    SDL_Surface *textSurface;
    SDL_Texture *mTexture;
    SDL_Color textColor = {0xFF, 0xFF, 0xFF}; // Txuria
    SDL_Rect src, dst;
    SDL_Renderer *gRenderer;

    if (font == 0)
    {
        return;
    }
    gRenderer = getRenderer();
    textSurface = TTF_RenderText_Solid(font, str, textColor);
    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    src.x = 0;
    dst.x = x;
    src.y = 0;
    dst.y = y;
    src.w = dst.w = textSurface->w;
    src.h = dst.h = textSurface->h;
    SDL_RenderCopy(gRenderer, mTexture, &src, &dst);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(mTexture);
}

void textuaIdatzibeltza(int x, int y, char *str)
{
    SDL_Surface *textSurface;
    SDL_Texture *mTexture;
    SDL_Color textColor = {0x00, 0x00, 0x00}; // Beltza
    SDL_Rect src, dst;
    SDL_Renderer *gRenderer;

    if (font == 0)
    {
        return;
    }
    gRenderer = getRenderer();
    textSurface = TTF_RenderText_Solid(font, str, textColor);
    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    src.x = 0;
    dst.x = x;
    src.y = 0;
    dst.y = y;
    src.w = dst.w = textSurface->w;
    src.h = dst.h = textSurface->h;
    SDL_RenderCopy(gRenderer, mTexture, &src, &dst);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(mTexture);
}

void textuaDesgaitu(void)
{
    if (font != 0)
    {
        TTF_CloseFont(font);
    }
    font = 0;
}

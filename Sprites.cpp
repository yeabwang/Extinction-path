#include "Sprites.h"
#include <cstdlib>
#include <cstdio>

Sprites::Sprites(SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int NoS, int posX, int posY, int sWidth, int sHeight, int width, int height, const char* description, bool colorKey, int df)
    : position(posX, posY), Size(width, height)
{
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    this->NOS = NoS;
    this->sRect = new SDL_Rect*[NoS]{ NULL };
    this->dRect = new SDL_Rect{ posX, posY, width, height };
    this->ClassDescription = description;

    SDL_Surface* SD_Surface = IMG_Load(Path);
    if (!SD_Surface)
    {
        printf("Failed to load image: %s\n", IMG_GetError());
        return;
    }

    if (colorKey)
        SDL_SetColorKey(SD_Surface, SDL_TRUE, SDL_MapRGB(SD_Surface->format, 0xFF, 0xFF, 0xFF));

    Texture = SDL_CreateTextureFromSurface(gRenderer, SD_Surface);
    if (!Texture)
    {
        printf("Failed to create texture: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(SD_Surface);

    for (int i = 0; i < NOS; i++)
    {
        sRect[i] = new SDL_Rect{ df + i * sWidth, 0, sWidth, sHeight };
    }
}

Sprites::Sprites(SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int NoS, int sWidth, int sHeight, SDL_Rect* externalDestination, const char* description, bool colorKey, int df)
    : position(externalDestination->x, externalDestination->y), Size(externalDestination->w, externalDestination->h)
{
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    this->NOS = NoS;
    this->sRect = new SDL_Rect*[NoS]{ NULL };
    this->dRect = externalDestination;
    this->ClassDescription = description;

    SDL_Surface* SD_Surface = IMG_Load(Path);
    if (!SD_Surface)
    {
        printf("Failed to load image: %s\n", IMG_GetError());
        return;
    }

    if (colorKey)
        SDL_SetColorKey(SD_Surface, SDL_TRUE, SDL_MapRGB(SD_Surface->format, 0xFF, 0xFF, 0xFF));

    Texture = SDL_CreateTextureFromSurface(gRenderer, SD_Surface);
    if (!Texture)
    {
        printf("Failed to create texture: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(SD_Surface);

    for (int i = 0; i < NOS; i++)
    {
        sRect[i] = new SDL_Rect{ df + i * sWidth, 0, sWidth, sHeight };
    }
}

void Sprites::moveDestinationArea(int x, int y)
{
    this->dRect->x += x;
    this->dRect->y += y;
    this->position.set_X(dRect->x);
    this->position.set_Y(dRect->y);
}

void Sprites::moveSpriteArea(int x)
{
    if (((sRect[cs]->x + 600) <= 3600))
        this->sRect[cs]->x += x;
}

void Sprites::render(int Frame, SDL_RendererFlip flip)
{
    if (Frame)
    {
        if (!(Frame % NOS))
            cs += 1;
    }
    else
    {
        cs += 1;
    }

    if (cs == NOS)
        cs = 0;

    SDL_RenderCopyEx(gRenderer, Texture, sRect[cs], dRect, 0, 0, flip);
}

int Sprites::get_NOS()
{
    return NOS;
}

void Sprites::set_CS(int n)
{
    if (n <= NOS)
        cs = n;
    else
        printf("Invalid input!\n");
}

Point Sprites::get_Position()
{
    Point temp(dRect->x, dRect->y);
    return position;
}

Point Sprites::get_Size()
{
    Point temp(dRect->w, dRect->h);
    return Size;
}

Sprites::~Sprites()
{
    for (int i = 0; i < NOS; i++)
    {
        delete sRect[i];
    }
    delete[] sRect;

    if (Texture)
    {
        SDL_DestroyTexture(Texture);
    }
}
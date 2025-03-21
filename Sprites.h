#ifndef SPRITES_H
#define SPRITES_H

#include "SDL.h"
#include "SDL_image.h"
#include "Point.h"
#include <cstdio> // For C-style I/O

class Sprites
{
public:
    Sprites(SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int NoS, int posX, int posY, int sWidth, int sHeight, int width, int height, const char* description, bool colorKey = false, int df = 0);
    Sprites(SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int NoS, int sWidth, int sHeight, SDL_Rect* externalDestination, const char* description, bool colorKey = false, int df = 0);

    void moveDestinationArea(int x = 0, int y = 0); // Moves Destination rectangle (Moves Image on screen)
    void moveSpriteArea(int x = 0); // Moves current sprite
    void render(int Frame = 0, SDL_RendererFlip flip = SDL_FLIP_NONE); // Renders animated sprite
    Point get_Position(); // Returns current position of sprite
    Point get_Size(); // Returns size of sprite
    int get_NOS(); // Returns number of clips
    void set_CS(int n); // Sets current selected clip
    virtual ~Sprites();

    // Disable copy constructor and assignment operator
    Sprites(const Sprites&) = delete;
    Sprites& operator=(const Sprites&) = delete;

protected:
    int cs = 0; // Index of currentSprite
    int NOS; // Number of Sprites in this texture
    SDL_Texture* Texture; // Texture of Image
    Point Size; // Size of the sprite
    Point position; // Position of sprite renderer
    SDL_Window* gWindow; // Main Window
    SDL_Renderer* gRenderer; // Main Renderer
    SDL_Rect** sRect; // Source Rectangle
    SDL_Rect* dRect; // Destination Rectangle
    const char* ClassDescription; // Description or name
};

#endif // SPRITES_H
#ifndef SPRITES_H
#define SPRITES_H

#include "SDL.h"
#include "SDL_image.h"
#include "Point.h"
#include <string>
using namespace std;

class Sprites {
public:
    // Constructor with full initialization
    Sprites(SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int NoS, int posX, int posY, int sWidth, int sHeight, int width, int height, string description, bool colorKey = false, int df = 0);

    // Constructor with external destination rectangle
    Sprites(SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int NoS, int sWidth, int sHeight, SDL_Rect* externalDestination, string description, bool colorKey = false, int df = 0);

    // Move the destination rectangle (moves the image on the screen)
    void moveDestinationArea(int x = 0, int y = 0);

    // Move the current sprite within the source rectangle
    void moveSpriteArea(int x = 0);

    // Render the sprite with optional frame and flip settings
    void render(int Frame = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Get the current position of the sprite
    Point get_Position() const;

    // Get the size of the sprite
    Point get_Size() const;

    // Get the number of clips (sprites in the texture)
    int get_NOS() const;

    // Set the current selected clip (sprite index)
    void set_CS(int n);

    // Destructor
    virtual ~Sprites();

    // Delete default constructor, copy constructor, and assignment operator
    Sprites() = delete;
    Sprites(const Sprites&) = delete;
    Sprites& operator=(const Sprites&) = delete;

protected:
    int cs = 0; // Index of the current sprite
    int NOS; // Number of sprites in this texture
    SDL_Texture* Texture; // Texture of the image
    Point Size; // Size of the sprite
    Point position; // Position of the sprite renderer
    SDL_Window* gWindow; // Main window
    SDL_Renderer* gRenderer; // Main renderer
    SDL_Rect** sRect; // Array of source rectangles
    SDL_Rect* dRect; // Destination rectangle
    string ClassDescription; // Description or name of the sprite
};

#endif // SPRITES_H

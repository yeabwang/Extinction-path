#ifndef SPRITES_H
#define SPRITES_H

#include "SDL.h"
#include "SDL_image.h"
#include "Point.h"
#include <cstdio>

class Sprites {
public:
    // Constructor for initializing with explicit position and size
    Sprites(SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int NoS, int posX, int posY, 
            int sWidth, int sHeight, int width, int height, const char* description, bool colorKey = false, int df = 0);
    // Constructor for linking to an external destination rectangle
    Sprites(SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int NoS, int sWidth, int sHeight, 
            SDL_Rect* externalDestination, const char* description, bool colorKey = false, int df = 0);

    bool isValid() const { return Texture != nullptr; } // Check if texture is loaded
    void moveDestinationArea(int x = 0, int y = 0);     // Move the destination rectangle
    void moveSpriteArea(int x = 0);                      // Move the source rectangle (for animation)
    void render(int Frame = 0, SDL_RendererFlip flip = SDL_FLIP_NONE, double overrideAngle = 0.0); // Render with optional angle override
    void setAngle(double a);                             // Set persistent angle
    double getAngle() const { return angle; }            // Get persistent angle (added)
    Point get_Position();                                // Get sprite position
    Point get_Size();                                    // Get sprite size
    int get_NOS();                                       // Get number of sprites
    void set_CS(int n);                                  // Set current sprite index
    virtual ~Sprites();

    Sprites(const Sprites&) = delete;                    // Disable copying
    Sprites& operator=(const Sprites&) = delete;

    SDL_Rect* dRect;                                     // Public destination rectangle (moved from protected)

protected:
    double angle = 0.0;                                  // Persistent angle for rotation
    int cs = 0;                                          // Current sprite index
    int NOS;                                             // Number of sprites
    SDL_Texture* Texture;                                // Texture for rendering
    Point Size;                                          // Sprite dimensions
    Point position;                                      // Sprite position
    SDL_Window* gWindow;                                 // Window reference
    SDL_Renderer* gRenderer;                             // Renderer reference
    SDL_Rect** sRect;                                    // Array of source rectangles for animation
    const char* ClassDescription;                        // Descriptive string
};

#endif // SPRITES_H
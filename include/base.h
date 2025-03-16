#ifndef BASE_H
#define BASE_H

#include <SDL.h>
#include <SDL_image.h>
#include <cmath> // Added for sqrt, sin, cos, etc.

#define LEVELWIDTH 2000  // Terrain dimensions from your friend's code
#define LEVELHEIGHT 1500
#define TRANSPARENT 0x00000000  // Transparent pixel (RGBA: 0,0,0,0)
#define EARTH 0xFF8B4513  // Brown color for terrain (example; adjust if needed)

// Simple Vector2 class for 2D coordinates
class Vector2 {
public:
    float x, y;
    Vector2(float x = 0, float y = 0) : x(x), y(y) {}
    void add(Vector2 v) { x += v.x; y += v.y; }
    void mul(float s) { x *= s; y *= s; }
    void normalize() {
        float len = sqrt(x * x + y * y);
        if (len > 0) { x /= len; y /= len; }
    }
};

// Color class to extract RGBA from a pixel
class colorRGBA {
public:
    Uint8 r, g, b, a;
    void fromPixel32(Uint32 pixel, SDL_PixelFormat* format) {
        SDL_GetRGBA(pixel, format, &r, &g, &b, &a);
    }
};

// Base Image class for rendering textures
class Image {
public:
    SDL_Renderer* renderer;  // Use SDL_Renderer* instead of GameWindow
    SDL_Texture* tex;
    SDL_Rect texr;
    Vector2 pos;
    Image(SDL_Renderer* renderer) : renderer(renderer), tex(nullptr), pos(0, 0) {
        texr = {0, 0, 0, 0};
    }
    virtual ~Image() { if (tex) SDL_DestroyTexture(tex); }
    SDL_Texture* textureFromSurface(SDL_Surface* surface) {
        return SDL_CreateTextureFromSurface(renderer, surface);
    }
};

// Utility functions for pixel manipulation
Uint32 get_pixel32(SDL_Surface* surface, int x, int y);
void put_pixel32(SDL_Surface* surface, int x, int y, Uint32 pixel);

#endif // BASE_H
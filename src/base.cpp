#include "base.h"

Uint32 get_pixel32(SDL_Surface* surface, int x, int y) {
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) return 0;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
    return *(Uint32*)p;
}

void put_pixel32(SDL_Surface* surface, int x, int y, Uint32 pixel) {
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) return;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
    *(Uint32*)p = pixel;
}
#include "Sprites.h"  // Include the Sprites class header file
#include "cstdlib"    // Include standard library for general utilities

// Constructor for the Sprites class (with explicit position and size)
Sprites::Sprites(SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int NoS, int posX, int posY, int sWidth, int sHeight, int width, int height, string description, bool colorKey, int df)
    : gWindow(gWindow), gRenderer(gRenderer), NOS(NoS), cs(0), Size(width, height), position(posX, posY), ClassDescription(description) {
    sRect = new SDL_Rect*[NoS]{nullptr};  // Allocate memory for source rectangles
    dRect = new SDL_Rect{posX, posY, width, height};  // Initialize destination rectangle
    SDL_Surface* SD_Surface = IMG_Load(Path.c_str());  // Load the image from the specified path
    if (!SD_Surface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;  // Print error if loading fails
        return;
    }
    if (colorKey)
        SDL_SetColorKey(SD_Surface, SDL_TRUE, SDL_MapRGB(SD_Surface->format, 0xFF, 0xFF, 0xFF));  // Set color key for transparency
    Texture = SDL_CreateTextureFromSurface(gRenderer, SD_Surface);  // Create texture from surface
    SDL_FreeSurface(SD_Surface);  // Free the surface after creating the texture
    if (!Texture) {
        cerr << "Failed to create texture: " << SDL_GetError() << endl;  // Print error if texture creation fails
        return;
    }
    for (int i = 0; i < NOS; i++) {
        sRect[i] = new SDL_Rect{df + i * sWidth, 0, sWidth, sHeight};  // Initialize source rectangles
    }
}

// Constructor for the Sprites class (with external destination rectangle)
Sprites::Sprites(SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int NoS, int sWidth, int sHeight, SDL_Rect* externalDestination, string description, bool colorKey, int df)
    : gWindow(gWindow), gRenderer(gRenderer), NOS(NoS), cs(0), Size(externalDestination->w, externalDestination->h), position(externalDestination->x, externalDestination->y), ClassDescription(description) {
    sRect = new SDL_Rect*[NoS]{nullptr};  // Allocate memory for source rectangles
    dRect = externalDestination;  // Use the provided destination rectangle
    SDL_Surface* SD_Surface = IMG_Load(Path.c_str());  // Load the image from the specified path
    if (!SD_Surface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;  // Print error if loading fails
        return;
    }
    if (colorKey)
        SDL_SetColorKey(SD_Surface, SDL_TRUE, SDL_MapRGB(SD_Surface->format, 0xFF, 0xFF, 0xFF));  // Set color key for transparency
    Texture = SDL_CreateTextureFromSurface(gRenderer, SD_Surface);  // Create texture from surface
    SDL_FreeSurface(SD_Surface);  // Free the surface after creating the texture
    if (!Texture) {
        cerr << "Failed to create texture: " << SDL_GetError() << endl;  // Print error if texture creation fails
        return;
    }
    for (int i = 0; i < NOS; i++) {
        sRect[i] = new SDL_Rect{df + i * sWidth, 0, sWidth, sHeight};  // Initialize source rectangles
    }
}

// Method to move the destination rectangle
void Sprites::moveDestinationArea(int x, int y) {
    dRect->x += x;  // Move the destination rectangle in the x-direction
    dRect->y += y;  // Move the destination rectangle in the y-direction
    position.set_X(dRect->x);  // Update the position's x-coordinate
    position.set_Y(dRect->y);  // Update the position's y-coordinate
}

// Method to move the sprite within the source rectangle
void Sprites::moveSpriteArea(int x) {
    if ((sRect[cs]->x + x) <= (NOS * sRect[cs]->w)) {  // Check if the move is within bounds
        sRect[cs]->x += x;  // Move the sprite within the source rectangle
    }
}

// Method to render the sprite
void Sprites::render(int Frame, SDL_RendererFlip flip) {
    if (Frame > 0) {
        cs = Frame % NOS;  // Set the current sprite index based on the frame
    } else {
        cs = (cs + 1) % NOS;  // Cycle through the sprites
    }
    SDL_RenderCopyEx(gRenderer, Texture, sRect[cs], dRect, 0, 0, flip);  // Render the sprite
}

// Method to get the number of sprites
int Sprites::get_NOS() const {
    return NOS;  // Return the number of sprites
}

// Method to set the current sprite index
void Sprites::set_CS(int n) {
    if (n < NOS) {
        cs = n;  // Set the current sprite index
    } else {
        cerr << "Invalid input!" << endl;  // Print error if the input is invalid
    }
}

// Method to get the position of the sprite
Point Sprites::get_Position() const {
    return Point(dRect->x, dRect->y);  // Return the position as a Point object
}

// Method to get the size of the sprite
Point Sprites::get_Size() const {
    return Point(dRect->w, dRect->h);  // Return the size as a Point object
}

// Destructor for the Sprites class
Sprites::~Sprites() {
    if (Texture) {
        SDL_DestroyTexture(Texture);  // Destroy the texture
        Texture = nullptr;  // Set the texture pointer to null
    }
    for (int i = 0; i < NOS; i++) {
        delete sRect[i];  // Delete each source rectangle
    }
    delete[] sRect;  // Delete the array of source rectangles
    if (dRect) {
        delete dRect;  // Delete the destination rectangle
        dRect = nullptr;  // Set the destination rectangle pointer to null
    }
}

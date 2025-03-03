#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 5

typedef struct {
    float x, y;
    float angle;
    bool isFiring;
    bool isCrouching;
} Player;

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    return texture;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Run and Gun Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Player player = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, false, false};

    SDL_Texture* playerTexture = loadTexture("player.png", renderer); // Replace with your player sprite
    if (playerTexture == NULL) {
        printf("Failed to load player texture!\n");
        return -1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Handle keyboard input
        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        // Movement
        if (keystate[SDL_SCANCODE_W]) player.y -= PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_S]) player.y += PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_A]) player.x -= PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_D]) player.x += PLAYER_SPEED;

        // Crouching
        player.isCrouching = keystate[SDL_SCANCODE_LCTRL]; // Left Control for crouching

        // Firing
        if (keystate[SDL_SCANCODE_H] || keystate[SDL_SCANCODE_SPACE]) { // H or Space for firing
            player.isFiring = true;
        } else {
            player.isFiring = false;
        }

        // Keyboard Aiming
        if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_I]) { // Aim Up
            player.angle = -90; // Point upwards
        } else if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_K]) { // Aim Down
            player.angle = 90; // Point downwards
        } else if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_J]) { // Aim Left
            player.angle = 180; // Point left
        } else if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_L]) { // Aim Right
            player.angle = 0; // Point right
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render player
        SDL_Rect playerRect;
        if (player.isCrouching) {
            playerRect = (SDL_Rect){player.x - 16, player.y - 8, 32, 16}; // Smaller rect for crouching
        } else {
            playerRect = (SDL_Rect){player.x - 16, player.y - 16, 32, 32}; // Normal rect
        }
        SDL_RenderCopyEx(renderer, playerTexture, NULL, &playerRect, player.angle, NULL, SDL_FLIP_NONE);

        // Render bullets or handle firing logic here
        if (player.isFiring) {
            // Add bullet spawning logic here
            printf("Firing at angle: %.2f\n", player.angle); // Placeholder for firing logic
        }

        // Update screen
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Cap frame rate to ~60 FPS
    }

    // Cleanup
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
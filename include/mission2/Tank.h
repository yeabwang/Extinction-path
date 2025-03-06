#ifndef TANK_H  // Header guard to prevent multiple inclusions
#define TANK_H

#include "cstdlib"          // Include standard library for general utilities
#include "Bullet.h"         // Include Bullet class for bullet-related functionality
#include "List.h"           // Include List class for managing a list of game objects
#include "GameObjects.h"    // Include GameObjects class as a base class
#include <../Character.h>  // Include Character class for inheritance
#include <Health.h>         // Include Health class for managing health
#include "SoundEffects.h"   // Include SoundEffects class for sound management
#include "fstream"          // Include fstream for file input/output operations

// Tank class declaration, inheriting from Character
class Tank : public Character
{
    public:
        // Constructor for the Tank class
        Tank(SDL_Window* gWindow, SDL_Renderer* gRenderer, int posX, int posY, List<GameObjects*>* bullets);

        // Method to get the type of the object
        string getType();

        // Method to render the tank
        void render(int frames = 0);

        // Method to check if the tank is alive
        bool IsAlive();

        // Method to handle collision impacts
        void CollisionImpact(GameObjects* CollidedWith);

        // Method to get the tank's position
        Point get_Position();

        // Method to get the tank's size
        Point get_Size();

        // Method to handle events (currently empty)
        void EventsController(SDL_Event* e);

        // Method to move the tank
        void Move(int x = 0, int y = 0);

        // Method to set the tank's alive status
        void setAlive(bool alive);

        // Destructor for the Tank class
        virtual ~Tank();

        // Method to fire a bullet
        void fire();

        // Friend function for saving tank data to a file
        friend ofstream& operator<<(ofstream& file, Tank* tank);

        // Friend function for loading tank data from a file
        friend ifstream& operator>>(ifstream& file, Tank* tank);

    protected:
        // No protected members in this class

    private:
        bool inframe = false;  // Flag to check if the tank is in the frame
        int cs = 0;            // Current sprite index (0: tank, 1: explosion)
        int counter = 0;       // Counter for explosion animation
        Health health;         // Health object to manage the tank's health
        int bulletsCount = 0;  // Counter for the number of bullets fired
        bool moving = true;    // Flag to check if the tank is moving
        float moveX = 0;       // Movement speed in the x-direction
        SDL_Window* gWindow;   // Pointer to the SDL window
        SDL_Renderer* gRenderer;  // Pointer to the SDL renderer
        bool Alive;           // Flag to check if the tank is alive
        Sprites* sprite[2];   // Array of sprites for the tank and explosion
        SDL_Rect* dRect;      // Pointer to the tank's destination rectangle
        List<GameObjects*>* bullets;  // Pointer to the list of bullets
        SoundEffects* sounds[2]{NULL};  // Array of sound effects (currently only one sound)
};

#endif // TANK_H  // End of header guard

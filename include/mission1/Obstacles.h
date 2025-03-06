#ifndef OBSTACLES_H  // Header guard to prevent multiple inclusions
#define OBSTACLES_H

#include <iostream>    // Include for standard input/output operations
#include <cstdlib>     // Include for general utilities
#include <GameObjects.h>  // Include the base GameObjects class for inheritance
#include "SoundEffects.h" // Include for sound effects functionality
#include "Sprites.h"      // Include for sprite management
#include "GameScreen.h"   // Include for GameScreen interaction
#include "fstream"        // Include for file input/output operations
using namespace std;      // Use the standard namespace

// Obstacles class declaration, inheriting from GameObjects
class Obstacles : public GameObjects
{
    public:
        // Constructor for the Obstacles class
        Obstacles(SDL_Window* gWindow, SDL_Renderer* grenderer, int NOS, string path, int posX, int posY, int sWidth, int sHeight, int width, int height, GameScreen* gs);

        // Method to get the type of the object
        string getType();

        // Method to check if the obstacle is alive (in frame)
        bool IsAlive();

        // Method to render the obstacle
        void render(int frames = 0);

        // Method to set the alive state of the obstacle
        void setAlive(bool alive);

        // Method to get the position of the obstacle
        Point get_Position();

        // Method to get the size of the obstacle
        Point get_Size();

        int objectId;  // Unique ID for the obstacle

        // Method to move the obstacle
        void Move(int x = 0, int y = 0);

        // Method to handle collision impacts
        void CollisionImpact(GameObjects* CollidedWith);

        // Destructor for the Obstacles class
        virtual ~Obstacles();

        // Method to set the obstacle as alive
        void setAlive();

        static int ID;  // Static counter for assigning unique IDs to obstacles

        // Friend function to overload the output stream operator for saving obstacle data
        friend ofstream& operator<<(ofstream& file, Obstacles* ob);

        // Friend function to overload the input stream operator for loading obstacle data
        friend ifstream& operator>>(ifstream& file, Obstacles* ob);

    protected:
        // No protected members in this class

    private:
        SoundEffects* sounds[1];  // Array of sound effects (currently only one sound)
        Sprites* sprite[2];       // Array of sprites for the obstacle and explosion
        int counter = 0;          // Counter for explosion animation
        bool inFrame = true;      // Flag to check if the obstacle is in the frame
        int cs = 0;               // Current sprite index (0: obstacle, 1: explosion)
        GameScreen* gamescreen = NULL;  // Pointer to the GameScreen
        SDL_Rect* dRect;         // Pointer to the destination rectangle
};

#endif // OBSTACLES_H  // End of header guard

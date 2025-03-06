#include "Obstacles.h"  // Include the Obstacles class header file

// Static member initialization
int Obstacles::ID = 0;

// Constructor for the Obstacles class
Obstacles::Obstacles(SDL_Window* gWindow, SDL_Renderer* grenderer, int NOS, string path, int posX, int posY, int sWidth, int sHeight, int width, int height, GameScreen* gs)
{
    ID += 1;  // Increment the static ID counter
    objectId = ID;  // Assign the unique ID to the obstacle
    sounds[0] = new SoundEffects("data\\common\\blast.wav");  // Load the blast sound effect
    dRect = new SDL_Rect{posX, posY, width, height};  // Initialize the destination rectangle
    sprite[0] = new Sprites(gWindow, grenderer, path, NOS, sWidth, sHeight, dRect, "obstacle", true);  // Load the obstacle sprite
    sprite[1] = new Sprites(gWindow, grenderer, "data\\tanks\\Image\\blast1.png", 7, 945 / 7, 176, dRect, "", true);  // Load the explosion sprite
    gamescreen = gs;  // Store the GameScreen pointer
}

// Method to get the type of the object
string Obstacles::getType()
{
    return "OBSTACLE";  // Return the type as "OBSTACLE"
}

// Method to check if the obstacle is alive (in frame)
bool Obstacles::IsAlive()
{
    return inFrame;  // Return the inFrame flag
}

// Method to render the obstacle
void Obstacles::render(int frames)
{
    if (gamescreen->IsMoved())  // Check if the game screen is moving
    {
        Move(-3);  // Move the obstacle left by 3 units
    }

    // Handle explosion animation
    if (counter > 0)  // If the explosion counter is active
    {
        if (counter == 1)  // If the explosion animation is complete
            inFrame = false;  // Set the obstacle as out of frame
        counter -= 1;  // Decrement the explosion counter
    }

    sprite[cs]->render(frames);  // Render the current sprite (obstacle or explosion)

    // Check if the obstacle is out of the frame
    if (get_Position().get_X() + get_Size().get_X() < 0)
        inFrame = false;  // Set the obstacle as out of frame
}

// Method to set the alive state of the obstacle
void Obstacles::setAlive(bool alive)
{
    this->inFrame = alive;  // Update the inFrame flag
}

// Method to get the position of the obstacle
Point Obstacles::get_Position()
{
    Point p(dRect->x, dRect->y);  // Create a Point object with the obstacle's position
    return p;  // Return the position
}

// Method to get the size of the obstacle
Point Obstacles::get_Size()
{
    Point p(dRect->w, dRect->h);  // Create a Point object with the obstacle's size
    return p;  // Return the size
}

// Method to move the obstacle
void Obstacles::Move(int x, int y)
{
    sprite[cs]->moveDestinationArea(x, y);  // Move the obstacle's sprite
}

// Method to handle collision impacts
void Obstacles::CollisionImpact(GameObjects* CollidedWith)
{
    if (CollidedWith->getType() == "TANK")  // Check if the collision is with a tank
    {
        SDL_Rect collide = {(CollidedWith->get_Position()).get_X(), (CollidedWith->get_Position()).get_Y(), (CollidedWith->get_Size()).get_X(), (CollidedWith->get_Size()).get_Y()};  // Get the collision rectangle
        SDL_Rect* dRect = new SDL_Rect{get_Position().get_X(), get_Position().get_Y(), get_Size().get_X(), get_Size().get_Y()};  // Get the obstacle's rectangle
        if (SDL_HasIntersection(&collide, dRect))  // Check if the rectangles intersect
        {
            sounds[0]->Play();  // Play the blast sound effect
            if (counter == 0)  // If the explosion counter is not already set
            {
                counter = 40;  // Set the explosion counter
            }
            cs = 1;  // Switch to the explosion sprite
        }
    }
}

// Destructor for the Obstacles class
Obstacles::~Obstacles()
{
    for (int i = 0; i < 2; i++)  // Delete all sprites
        delete sprite[i];
}

// Method to set the obstacle as alive
void Obstacles::setAlive()
{
    inFrame = true;  // Set the inFrame flag to true
}

// Overloaded output stream operator for saving obstacle data
ofstream& operator<<(ofstream& file, Obstacles* ob)
{
    file << "---OBSTACLE---" << endl;  // Write obstacle header
    file << ob->inFrame << endl;  // Write inFrame status
    file << ob->cs << endl;  // Write current sprite index
    file << ob->counter << endl;  // Write explosion counter
    file << ob->dRect->y << endl;  // Write y position
    file << ob->dRect->x << endl;  // Write x position
    return file;  // Return the file stream
}

// Overloaded input stream operator for loading obstacle data
ifstream& operator>>(ifstream& file, Obstacles* ob)
{
    string str;  // Temporary string for reading data
    file >> str;  // Read inFrame status
    ob->inFrame = atoi(str.c_str());
    file >> str;  // Read current sprite index
    ob->cs = atoi(str.c_str());
    file >> str;  // Read explosion counter
    ob->counter = atoi(str.c_str());
    file >> str;  // Read y position
    ob->dRect->y = atoi(str.c_str());
    file >> str;  // Read x position
    ob->dRect->x = atoi(str.c_str());
    return file;  // Return the file stream
}

#include "Tank.h"  // Include the Tank class header file

// Constructor for the Tank class
Tank::Tank(SDL_Window* gWindow, SDL_Renderer* gRenderer, int posX, int posY, List<GameObjects*>* bullets)
    : health(100, gWindow, gRenderer, posX, posY - 20)  // Initialize health bar
{
    Alive = true;  // Set the tank as alive
    this->gWindow = gWindow;  // Store the SDL window pointer
    this->gRenderer = gRenderer;  // Store the SDL renderer pointer
    this->bullets = bullets;  // Store the list of bullets
    dRect = new SDL_Rect{posX, posY, 250, 150};  // Initialize the tank's destination rectangle
    sprite[0] = new Sprites(gWindow, gRenderer, "data\\tanks\\Image\\Tank.png", 20, 1320 / 20, 56, dRect, "", true);  // Load tank sprite
    sprite[1] = new Sprites(gWindow, gRenderer, "data\\tanks\\Image\\blast1.png", 7, 945 / 7, 176, dRect, "", true);  // Load explosion sprite
    sounds[0] = new SoundEffects("data\\common\\blast.wav");  // Load explosion sound effect
}

// Method to get the type of the object
string Tank::getType()
{
    return "TANK";  // Return the type as "TANK"
}

// Method to render the tank
void Tank::render(int frames)
{
    static bool start = false;  // Flag to control initial rendering behavior
    if (!inframe)  // Check if the tank is not fully in the frame
    {
        if (dRect->x == 1250)  // If the tank reaches the right edge
        {
            inframe = true;  // Set the tank as in frame
        }
        else
        {
            dRect--;  // Move the tank left (decrement x position)
        }
    }
    else
    {
        if (start && counter == 0)  // If the tank is in frame and not exploding
        {
            if (bulletsCount == 3)  // If the tank has fired 3 bullets
            {
                if (frames % 100 == 0 && moving)  // Move the tank every 100 frames
                {
                    moveX += 1.99;  // Increment movement speed
                }

                if ((dRect->x) < 50 && moving)  // If the tank reaches the left edge
                {
                    moving = false;  // Stop moving
                    moveX = -2;  // Set movement speed to the left
                }
                else if ((dRect->x) > 1250 && !moving)  // If the tank reaches the right edge
                {
                    moving = true;  // Start moving
                    moveX = 0;  // Reset movement speed
                    bulletsCount = 0;  // Reset bullet count
                }
                Move(-moveX, 0);  // Move the tank
            }
            else
            {
                if (frames % 100 == 0)  // Fire a bullet every 100 frames
                {
                    fire();  // Fire a bullet
                    bulletsCount += 1;  // Increment bullet count
                }
            }
        }
    }

    if (counter > 0)  // If the tank is exploding
    {
        if (counter == 1)  // If the explosion animation is complete
            Alive = false;  // Set the tank as dead
        counter -= 1;  // Decrement the explosion counter
    }

    health.display(dRect->x, dRect->y);  // Display the health bar
    sprite[cs]->render(frames, SDL_FLIP_HORIZONTAL);  // Render the tank or explosion sprite

    start = true;  // Set the start flag to true after the first render
}

// Method to check if the tank is alive
bool Tank::IsAlive()
{
    return Alive;  // Return the alive status
}

// Method to handle collision impacts
void Tank::CollisionImpact(GameObjects* CollidedWith)
{
    if (CollidedWith->getType() == "HEROBULLET")  // Check if collided with a hero bullet
    {
        SDL_Rect collide = {(CollidedWith->get_Position()).get_X(), (CollidedWith->get_Position()).get_Y(), (CollidedWith->get_Size()).get_X(), (CollidedWith->get_Size()).get_Y()};  // Get collision rectangle
        if (SDL_HasIntersection(&collide, dRect))  // Check if the bullet intersects with the tank
        {
            CollidedWith->setAlive(false);  // Set the bullet as dead
            health.decrease(1);  // Decrease the tank's health
            if (health.get_Health() == 0)  // If the tank's health reaches 0
            {
                sounds[0]->Play();  // Play the explosion sound
                if (counter == 0)  // If the explosion counter is not already set
                {
                    counter = 45;  // Set the explosion counter
                }
                cs = 1;  // Switch to the explosion sprite
            }
        }
    }
}

// Method to get the tank's position
Point Tank::get_Position()
{
    return sprite[cs]->get_Position();  // Return the position of the current sprite
}

// Method to get the tank's size
Point Tank::get_Size()
{
    return sprite[cs]->get_Size();  // Return the size of the current sprite
}

// Method to handle events (currently empty)
void Tank::EventsController(SDL_Event* e)
{
    // No implementation yet
}

// Method to move the tank
void Tank::Move(int x, int y)
{
    sprite[cs]->moveDestinationArea(x, y);  // Move the tank's sprite
}

// Method to set the tank's alive status
void Tank::setAlive(bool alive)
{
    this->Alive = alive;  // Update the alive status
}

// Destructor for the Tank class
Tank::~Tank()
{
    for (int i = 0; i < 2; i++)  // Delete all sprites
        delete sprite[i];
    for (int i = 0; i < 1; i++)  // Delete all sound effects
        delete sounds[i];
}

// Method to fire a bullet
void Tank::fire()
{
    bullets->add(new Bullet(gWindow, gRenderer, dRect->x, dRect->y + 55, -10, 0, "ENEMYBULLET"));  // Add a new bullet to the list
}

// Overloaded output stream operator for saving tank data
ofstream& operator<<(ofstream& file, Tank* tank)
{
    file << "---TANK---" << endl;  // Write tank header
    file << tank->inframe << endl;  // Write inframe status
    file << tank->health.get_Health() << endl;  // Write health
    file << tank->cs << endl;  // Write current sprite index
    file << tank->counter << endl;  // Write explosion counter
    file << tank->bulletsCount << endl;  // Write bullet count
    file << tank->moving << endl;  // Write moving status
    file << tank->moveX << endl;  // Write movement speed
    file << tank->Alive << endl;  // Write alive status
    file << (tank->dRect->x) << endl;  // Write x position
    file << (tank->dRect->y) << endl;  // Write y position
    return file;  // Return the file stream
}

// Overloaded input stream operator for loading tank data
ifstream& operator>>(ifstream& file, Tank* tank)
{
    string str;  // Temporary string for reading data
    file >> str;  // Read inframe status
    tank->inframe = atoi(str.c_str());
    file >> str;  // Read health
    tank->health.set_Health(atoi(str.c_str()));
    file >> str;  // Read current sprite index
    tank->cs = atoi(str.c_str());
    file >> str;  // Read explosion counter
    tank->counter = atoi(str.c_str());
    file >> str;  // Read bullet count
    tank->bulletsCount = atoi(str.c_str());
    file >> str;  // Read moving status
    tank->moving = atoi(str.c_str());
    file >> str;  // Read movement speed
    tank->moveX = atoi(str.c_str());
    file >> str;  // Read alive status
    tank->Alive = atoi(str.c_str());
    file >> str;  // Read x position
    tank->dRect->x = atoi(str.c_str());
    file >> str;  // Read y position
    tank->dRect->y = atoi(str.c_str());
    return file;  // Return the file stream
}

#include "LoadAndSave.h"  // Include the LoadAndSave class header file

// Constructor for the LoadAndSave class
LoadAndSave::LoadAndSave(Game* game, GameScreen* gamescreen, SDL_Window* window, SDL_Renderer* renderer)
{
    this->gamescreen = gamescreen;  // Store the GameScreen pointer
    this->game = game;             // Store the Game pointer
    gRenderer = renderer;          // Store the SDL renderer pointer
    gWindow = window;              // Store the SDL window pointer
}

// Method to save game data to a file
bool LoadAndSave::Save(List<GameObjects*>* list, string path)
{
    ofstream file(path.c_str());  // Open the file for writing
    file << game;  // Save the game state

    // Iterate through the list of game objects
    Node<GameObjects*>* tempNode = list->getStart();
    while (tempNode)
    {
        GameObjects* obj = tempNode->value;  // Get the current game object

        // Save the object based on its type
        if (obj->getType() == "HERO")
        {
            file << ((Hero*)obj);  // Save Hero object
        }
        else if (obj->getType() == "ENEMY")
        {
            file << ((Enemy*)obj);  // Save Enemy object
        }
        else if (obj->getType() == "TANK")
        {
            file << ((Tank*)obj);  // Save Tank object
        }
        else if (obj->getType() == "HELICOPTER")
        {
            file << ((Helicopter*)obj);  // Save Helicopter object
        }
        else if (obj->getType() == "BOSS")
        {
            file << ((Boss*)obj);  // Save Boss object
        }
        else if (obj->getType() == "OBSTACLE")
        {
            file << ((Obstacles*)obj);  // Save Obstacle object
        }

        tempNode = tempNode->next;  // Move to the next object in the list
    }

    return true;  // Return true to indicate successful saving
}

// Method to load game data from a file
bool LoadAndSave::Load(List<GameObjects*>* list, string path)
{
    string line = "";  // Temporary string for reading lines from the file
    ifstream file(path.c_str());  // Open the file for reading

    // Read the file line by line
    while (getline(file, line))
    {
        if (line == "---GAME---")  // Check if the line indicates game data
        {
            file >> game;  // Load the game state
        }
        else if (line == "---HERO---")  // Check if the line indicates Hero data
        {
            file >> (Hero*)(list->getStart())->value;  // Load Hero object
        }
        else if (line == "---ENEMY---")  // Check if the line indicates Enemy data
        {
            // Create a new Enemy object and load its data
            GameObjects* enemy = new Enemy(gWindow, gRenderer, 1000, list, 400);
            file >> ((Enemy*)enemy);
            list->add(enemy);  // Add the Enemy to the list
        }
        else if (line == "---TANK---")  // Check if the line indicates Tank data
        {
            // Create a new Tank object and load its data
            GameObjects* tank = new Tank(gWindow, gRenderer, 1250, 500, list);
            file >> ((Tank*)tank);
            list->add(tank);  // Add the Tank to the list
        }
        else if (line == "---HELICOPTER---")  // Check if the line indicates Helicopter data
        {
            // Create a new Helicopter object and load its data
            GameObjects* helicopter = new Helicopter(gWindow, gRenderer, 100, 50, list);
            file >> ((Helicopter*)helicopter);
            list->add(helicopter);  // Add the Helicopter to the list
        }
        else if (line == "---BOSS---")  // Check if the line indicates Boss data
        {
            // Create a new Boss object and load its data
            GameObjects* boss = new Boss(gWindow, gRenderer, 10, 10, list);
            file >> ((Boss*)boss);
            list->add(boss);  // Add the Boss to the list
        }
        else if (line == "---OBSTACLE---")  // Check if the line indicates Obstacle data
        {
            // Create a new Obstacle object and load its data
            GameObjects* obs = new Obstacles(gWindow, gRenderer, 1, "data\\Obstacles\\armyTruck.png", 1600, 500, 138, 71, 250, 150, gamescreen);
            file >> ((Obstacles*)obs);
            list->add(obs);  // Add the Obstacle to the list
        }
    }

    return true;  // Return true to indicate successful loading
}

// Destructor for the LoadAndSave class
LoadAndSave::~LoadAndSave()
{
    // No dynamic memory to clean up, so the destructor is empty
}

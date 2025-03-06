#include "Menu.h"  // Include the Menu class header file

// Constructor for the Menu class
Menu::Menu(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int width, int height)
{
    // Initialize the background sprite using the provided path, dimensions, and renderer
    this->Background = new Sprites(gWindow, gRenderer, Path, 1, 0, 0, 1598, 900, width, height, "");

    // Initialize the buttons for the menu
    this->Buttons[0] = new Button(gRenderer, gWindow, "Data\\Buttons\\MainMenu\\start0.png", {500, 350}, {422, 100});  // Start button
    this->Buttons[1] = new Button(gRenderer, gWindow, "Data\\Buttons\\MainMenu\\load0.png", {500, 460}, {422, 100});   // Load button
    this->Buttons[2] = new Button(gRenderer, gWindow, "Data\\Buttons\\MainMenu\\quit0.png", {500, 570}, {422, 100});   // Quit button

    this->e = e;  // Store the SDL_Event pointer
    Enable = false;  // Initialize the Enable flag to false
}

// Method to check if the Menu is enabled
bool Menu::IsEnable()
{
    return Enable;  // Return the current state of the Enable flag
}

// Method to set the enabled state of the Menu
void Menu::setEnabled(bool e)
{
    Enable = e;  // Update the Enable flag with the provided value
}

// Method to check which button is pressed
int Menu::getButtonPresed()
{
    int ButtonCount = -1;  // Initialize the button count to -1 (no button pressed)

    // Check if the Start button is clicked
    if (Buttons[0]->IsClicked(e))
    {
        ButtonCount = 0;  // Set the button count to 0 (Start button)
    }
    // Check if the Load button is clicked
    else if (Buttons[1]->IsClicked(e))
    {
        ButtonCount = 1;  // Set the button count to 1 (Load button)
    }
    // Check if the Quit button is clicked
    else if (Buttons[2]->IsClicked(e))
    {
        ButtonCount = 2;  // Set the button count to 2 (Quit button)
    }

    return ButtonCount;  // Return the index of the clicked button
}

// Method to render the Menu
void Menu::Render()
{
    this->Background->render();  // Render the background sprite
    this->Buttons[0]->Render();  // Render the Start button
    this->Buttons[1]->Render();  // Render the Load button
    this->Buttons[2]->Render();  // Render the Quit button
}

// Method to get the size of the Menu
Point Menu::getSize()
{
    return Background->get_Size();  // Return the size of the background sprite
}

// Destructor for the Menu class
Menu::~Menu()
{
    delete Background;  // Delete the background sprite
    for (int i = 0; i < 3; i++)  // Delete all buttons
}

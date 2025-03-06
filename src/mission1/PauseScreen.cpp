#include "PauseScreen.h"  // Include the PauseScreen class header file

// Constructor for the PauseScreen class
PauseScreen::PauseScreen(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int width, int height)
{
    // Initialize the background sprite using the provided path, dimensions, and renderer
    this->Background = new Sprites(gWindow, gRenderer, Path, 1, 0, 0, 2500, 1000, width, height, "");

    // Initialize the buttons for the pause screen
    this->Buttons[0] = new Button(gRenderer, gWindow, "Data\\Buttons\\Pause\\resume0.png", {500, 350}, {422, 100});  // Resume button
    this->Buttons[1] = new Button(gRenderer, gWindow, "Data\\Buttons\\Pause\\quit0.png", {500, 460}, {422, 100});    // Quit button

    this->e = e;  // Store the SDL_Event pointer
    Enable = false;  // Initialize the Enable flag to false
}

// Method to check if the PauseScreen is enabled
bool PauseScreen::IsEnable()
{
    return Enable;  // Return the current state of the Enable flag
}

// Method to set the enabled state of the PauseScreen
void PauseScreen::setEnabled(bool e)
{
    Enable = e;  // Update the Enable flag with the provided value
}

// Method to check which button is pressed
int PauseScreen::getButtonPresed()
{
    int ButtonCount = -1;  // Initialize the button count to -1 (no button pressed)

    // Check if the Resume button is clicked
    if (Buttons[0]->IsClicked(e))
    {
        ButtonCount = 0;  // Set the button count to 0 (Resume button)
    }

    // Check if the Quit button is clicked
    if (Buttons[1]->IsClicked(e))
    {
        ButtonCount = 1;  // Set the button count to 1 (Quit button)
    }

    return ButtonCount;  // Return the index of the clicked button
}

// Method to render the PauseScreen
void PauseScreen::Render()
{
    this->Background->render();  // Render the background sprite
    this->Buttons[0]->Render();  // Render the Resume button
    this->Buttons[1]->Render();  // Render the Quit button
}

// Method to get the size of the PauseScreen
Point PauseScreen::getSize()
{
    return Background->get_Size();  // Return the size of the background sprite
}

// Destructor for the PauseScreen class
PauseScreen::~PauseScreen()
{
    for (int i = 0; i < 2; i++)  // Delete all buttons
        delete Buttons[i];
    delete Background;  // Delete the background sprite
}

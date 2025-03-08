#include "Missions.h"

Missions::Missions(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int width, int height)
{
    this->Background = new Sprites(gWindow, gRenderer, Path, 1, 0, 0, 2500, 1000, width, height, "");
    this->Buttons[0] = new Button(gRenderer, gWindow, "Data\\Buttons\\Pause\\resume0.png", { 500, 350 }, { 422, 100 });
    this->Buttons[1] = new Button(gRenderer, gWindow, "Data\\Buttons\\Pause\\quit0.png", { 500, 460 }, { 422, 100 });
    this->e = e;
    Enable = false;
    roundNumber = 1; // Initialize round number
}

bool Missions::IsEnable()
{
    return Enable;
}

void Missions::setEnabled(bool e)
{
    Enable = e;
}

int Missions::getButtonPresed()
{
    int ButtonCount = -1;

    if (Buttons[0]->IsClicked(e))
    {
        ButtonCount = 0;
    }
    if (Buttons[1]->IsClicked(e))
    {
        ButtonCount = 1;
    }
    return ButtonCount;
}

void Missions::Render()
{
    this->Background->render();
    this->Buttons[0]->Render();
    this->Buttons[1]->Render();

    // Render the round number (use SDL_ttf or similar)
    // Example: Render text "Round X" on the screen
}

void Missions::setRoundNumber(int round)
{
    roundNumber = round;
    // Update the background or text to reflect the new round number
}

Point Missions::getSize()
{
    return Background->get_Size();
}

Missions::~Missions()
{
    for (int i = 0; i < 2; i++)
        delete Buttons[i];
    delete Background;
}
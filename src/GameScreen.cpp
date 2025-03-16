#include "GameScreen.h"
#include "Hero.h"
#include "Game.h"

GameScreen::GameScreen(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int width, int height, Hero* h, List<GameObjects*>* mainList)
{
    this->gRenderer = gRenderer;
    this->gWindow = gWindow;
    coordX = 0;
    this->mainList = mainList;
    this->Background = new Sprites(gWindow, gRenderer, Path, 1, 0, 0, 600, 600, width, height, "");
    ButtonsList[0] = new Button(gRenderer, gWindow, "Data\\Buttons\\Images\\Pause0.png", { 10, 10 }, { 50, 50 });
    this->e = e;
    Enable = false;
    hero = h;
    Size.set_X(width);   
    Size.set_Y(height);  
}

bool GameScreen::IsMoved()
{
    return moved;
}

bool GameScreen::IsEnable()
{
    return Enable;
}

void GameScreen::setEnabled(bool e)
{
    Enable = e;
}

int GameScreen::getButtonPresed()
{
    int ButtonCount = -1;
    if (ButtonsList[0]->IsClicked(e))
    {
        ButtonCount = 0;
    }
    return ButtonCount;
}

void GameScreen::Render()
{
    Game* game = hero->getGamePtr();  
    if (hero->IsMoved() && !game->free)
    {
        moved = true;
        move(2);
        coordX += 2;
        if (coordX + 1000 >= game->Current_Stage + 1000)
        {
            game->free = true;
            // Replace direct assignment with SetCurrentStage
            // game->free = true is enough to signal GameLogic to proceed
        }
    }
    else
    {
        moved = false;
    }
    this->Background->render();
    this->ButtonsList[0]->Render();
}

void GameScreen::move(int x)
{
    Background->moveSpriteArea(x);
}

Point GameScreen::getSize()
{
    return Size;
}

GameScreen::~GameScreen()
{
    delete Background;
    delete ButtonsList[0];
}
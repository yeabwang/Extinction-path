#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Button.h"
#include "Sprites.h"
#include "Screen.h"
#include "List.h"
#include "GameObjects.h"
#include <cstdio>

class Hero;

class GameScreen : public Screen
{
public:
    GameScreen(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int width, int height, Hero* hero, List<GameObjects*>* mainList);
    GameScreen() = delete; 
    GameScreen(const GameScreen&) = delete; 
    GameScreen& operator=(const GameScreen&) = delete; 

    bool IsEnable();
    void setEnabled(bool e);
    int getButtonPresed();
    void Render();
    Point getSize();
    void move(int x);
    bool IsMoved();
    SDL_Texture* getBackgroundTexture(); // Add this method
    void setBackgroundTexture(SDL_Texture* texture); // Add this method
    virtual ~GameScreen();

protected:
    SDL_Renderer* gRenderer;
    SDL_Window* gWindow;
    int coordX;
    bool moved; // Checks if the background was moved
    Hero* hero; // Stores hero's pointer because background movement depends on hero's movement
    bool Enable;
    Sprites* Background;
    Button* ButtonsList[1];
    Point Size;
    List<GameObjects*>* mainList;
    SDL_Event* e;
    SDL_Texture* backgroundTexture; // Add this member
};

#endif // GAMESCREEN_H
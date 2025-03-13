#ifndef LOADANDSAVE_H
#define LOADANDSAVE_H

#include "SDL.h"
#include "Game.h"
#include "GameScreen.h"
#include "List.h"
#include "GameObjects.h"
#include "Hero.h"
#include "Enemy.h"
#include "Tank.h"
#include "Helicopter.h"
#include "Boss.h"
#include "Obstacles.h"

class LoadAndSave {
public:
    LoadAndSave(Game* game, GameScreen* gamescreen, SDL_Window* window, SDL_Renderer* renderer);
    bool Save(List<GameObjects*>* list, const char* path);
    bool Load(List<GameObjects*>* list, const char* path);
    virtual ~LoadAndSave();

protected:
    GameScreen* gamescreen;
    Game* game;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;

    friend void SaveGameToFile(FILE* file, Game* game);
    friend void LoadGameFromFile(FILE* file, Game* game);
    friend void SaveHeroToFile(FILE* file, Hero* hero);
    friend void LoadHeroFromFile(FILE* file, Hero* hero);
    friend void SaveEnemyToFile(FILE* file, Enemy* enemy); 
    friend void LoadEnemyFromFile(FILE* file, Enemy* enemy); 
    friend void SaveTankToFile(FILE* file, Tank* tank); 
    friend void LoadTankFromFile(FILE* file, Tank* tank); 
    friend void SaveHelicopterToFile(FILE* file, Helicopter* helicopter); 
    friend void LoadHelicopterFromFile(FILE* file, Helicopter* helicopter); 
    friend void SaveBossToFile(FILE* file, Boss* boss); 
    friend void LoadBossFromFile(FILE* file, Boss* boss); 
    friend void SaveObstaclesToFile(FILE* file, Obstacles* obs); 
    friend void LoadObstaclesFromFile(FILE* file, Obstacles* obs);
};

#endif // LOADANDSAVE_H
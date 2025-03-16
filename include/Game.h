#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "SplashScreen.h"
#include "WinScreen.h"
#include "Menu.h"
#include "GameScreen.h"
#include "PauseScreen.h"
#include "List.h"
#include "GameObjects.h"
#include "Hero.h"
#include "Enemy.h"
#include "Tank.h"
#include "Helicopter.h"
#include "Boss.h"
#include "Dragon.h"      
#include "terrain.h"
#include "Obstacles.h"
#include "Music.h"
#include "Missions.h"

// Forward declaration
class LoadAndSave;

class Game {
private:
    SDL_Window* gWindow;
    SDL_Renderer* gRenederer;
    SDL_Event e;

    SplashScreen* splashScreen;
    WinScreen* win;
    WinScreen* lose;
    Menu* menu;
    GameScreen* gs;
    PauseScreen* pauseScreen;
    Missions* missions;
    Music* themeMusic;

    Hero* hero;
    terrain* ter;

    List<GameObjects*> ListofObjects;

    LoadAndSave* File;

    SDL_Rect screen;

    int counter;
    int spawnCounter; // Moved from GameLogic to class scope
    bool Quit;
    bool free;
    bool roundScreenShown;

    int Current_Stage;
    int EnemyKillCount;
    int OnScreenEnemies;

    bool TankKilled;
    bool TankGenerated;
    bool HelicopterKilled;
    bool HelicopterGenerated;
    bool FinalEnemiesGenerated;
    bool BossGenerated;
    bool DragonGenerated;
    bool DragonKilled;

    struct WindowSize {
        int w;
        int h;
        WindowSize(int width, int height) : w(width), h(height) {}
    } WindowSize;

    bool Initialize_components();
    void GameLogic();
    void ObjectsManager();
    bool EventController();
    void SaveGame();
    void LoadGame();

public:
    Game(int width, int height, LoadAndSave* file);
    ~Game();
    void SetCurrentStage(int stage);

    friend class Hero;
    friend class GameScreen;
    friend class LoadAndSave;

    // Friend functions
    friend void SaveGameToFile(FILE* file, Game* game) {
        fprintf(file, "---GAME---\n");
        fprintf(file, "%d\n", game->Current_Stage);
        fprintf(file, "%d\n", game->EnemyKillCount);
        fprintf(file, "%d\n", game->OnScreenEnemies);
        fprintf(file, "%d\n", game->free ? 1 : 0);
        fprintf(file, "%d\n", game->roundScreenShown ? 1 : 0);
        fprintf(file, "%d\n", game->TankKilled ? 1 : 0);
        fprintf(file, "%d\n", game->TankGenerated ? 1 : 0);
        fprintf(file, "%d\n", game->HelicopterKilled ? 1 : 0);
        fprintf(file, "%d\n", game->HelicopterGenerated ? 1 : 0);
        fprintf(file, "%d\n", game->FinalEnemiesGenerated ? 1 : 0);
        fprintf(file, "%d\n", game->BossGenerated ? 1 : 0);
        fprintf(file, "%d\n", game->DragonGenerated ? 1 : 0);
        fprintf(file, "%d\n", game->DragonKilled ? 1 : 0);
    }

    friend void LoadGameFromFile(FILE* file, Game* game) {
        int temp;
        fscanf(file, "%*s"); // Skip "---GAME---"
        fscanf(file, "%d", &game->Current_Stage);
        fscanf(file, "%d", &game->EnemyKillCount);
        fscanf(file, "%d", &game->OnScreenEnemies);
        fscanf(file, "%d", &temp); game->free = (temp != 0);
        fscanf(file, "%d", &temp); game->roundScreenShown = (temp != 0);
        fscanf(file, "%d", &temp); game->TankKilled = (temp != 0);
        fscanf(file, "%d", &temp); game->TankGenerated = (temp != 0);
        fscanf(file, "%d", &temp); game->HelicopterKilled = (temp != 0);
        fscanf(file, "%d", &temp); game->HelicopterGenerated = (temp != 0);
        fscanf(file, "%d", &temp); game->FinalEnemiesGenerated = (temp != 0);
        fscanf(file, "%d", &temp); game->BossGenerated = (temp != 0);
        fscanf(file, "%d", &temp); game->DragonGenerated = (temp != 0);
        fscanf(file, "%d", &temp); game->DragonKilled = (temp != 0);
    }
};

#endif
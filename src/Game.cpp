#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <cstdio> 
#include <cstring> 

#include "GameScreen.h"
#include "Sprites.h"
#include "Button.h"
#include "GameObjects.h"
#include "Character.h"
#include "Obstacles.h"
#include "Hero.h"
#include "SoundEffects.h"
#include "Music.h"
#include "SplashScreen.h"
#include "Menu.h"
#include "Enemy.h"
#include "Health.h"
#include "LoadAndSave.h"
#include "Tank.h"
#include "Helicopter.h"
#include "Boss.h"
#include "PauseScreen.h"
#include "Missions.h"

bool jump = false;
int j_loop = 0;
int movex = 0;
int movey = 0;
bool jumping = false;

Game::Game(int width, int height, LoadandSave* file) : WindowSize(width, height)
{
    counter = 0;
    Quit = false;
    File = file;
    roundScreenShown = false;
    free = false;
    Current_Stage = 1000; 
    EnemyKillCount = 0;
    OnScreenEnemies = 0;
    TankKilled = false;
    TankGenerated = false;
    HelicopterKilled = false;
    HelicopterGenerated = false;
    FinalEnemiesGenerated = false;
    BossGenerated = false;

    if (Initialize_components()) 
    {
        SDL_Rect x;
        screen = x; // Note: This copies an uninitialized SDL_Rect; we'll fix this
        x.w = 1440;
        x.h = 900;
        screen.w = x.w; // set dimensions
        screen.h = x.h;
        screen.x = 0;   // Initialize position
        screen.y = 0;

        gWindow = SDL_CreateWindow("Extinction path", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x.w, x.h, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return;
        }

        gRenederer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
        if (gRenederer == NULL) {
            printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            return;
        }

        hero = new Hero(gWindow, gRenederer, &ListofObjects, this);
        ListofObjects.add(hero);

        splashScreen = new SplashScreen(&e, gWindow, gRenederer, "data\\SplashScreen\\splash1.png", x.w, x.h);
        win = new WinScreen(&e, gWindow, gRenederer, "data\\SplashScreen\\win.png", x.w, x.h);
        lose = new WinScreen(&e, gWindow, gRenederer, "data\\SplashScreen\\lose.png", x.w, x.h);
        menu = new Menu(&e, gWindow, gRenederer, "data\\SplashScreen\\menu.png", x.w, x.h);
        gs = new GameScreen(&e, gWindow, gRenederer, "data\\Backgrounds\\main.png", x.w, x.h, (Hero*)hero, &ListofObjects);
        pauseScreen = new PauseScreen(&e, gWindow, gRenederer, "data\\SplashScreen\\menu.png", x.w, x.h);
        missions = new Missions(&e, gWindow, gRenederer, "data\\Backgrounds\\main.png", x.w, x.h);
        themeMusic = new Music("theme.mp3");

        splashScreen->setEnabled(true);
        themeMusic->Play();

        while (!Quit)
        {
            while (SDL_PollEvent(&e))
            {
                EventController();
                if (e.type == SDL_QUIT)
                    Quit = true;
                if (ListofObjects.getStart() != NULL && gs->IsEnable())
                    ((Character*)hero)->EventsController(&e);
            }

            SDL_SetRenderDrawColor(gRenederer, 255, 255, 255, 255);
            SDL_RenderClear(gRenederer);

            if (win->IsEnable())
                win->Render();
            else if (lose->IsEnable())
                lose->Render();
            else if (pauseScreen->IsEnable())
                pauseScreen->Render();
            else if (menu->IsEnable())
                menu->Render();
            else if (missions->IsEnable())
                missions->Render();
            else if (gs->IsEnable())
            {
                gs->Render();
                GameLogic();
                ObjectsManager();
                counter += 1;
                if (counter >= 1000)
                    counter = 0;
            }
            else if (splashScreen->IsEnable())
                splashScreen->Render();

            SDL_RenderPresent(gRenederer);
        }

        SaveGame();
    }
    else
    {
        printf("Game Cannot be started!\n");
    }
}

bool Game::Initialize_components()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void Game::SaveGame()
{
    LoadAndSave Save(this, gs, gWindow, gRenederer);
    Save.Save(&ListofObjects, "data//files//Saved.txt");
}

void Game::LoadGame()
{
    LoadAndSave file(this, gs, gWindow, gRenederer);
    file.Load(&ListofObjects, "data//files//Saved.txt");
}

void SaveGameToFile(FILE* file, Game* game)
{
    fprintf(file, "---GAME---\n");
    fprintf(file, "%d\n", game->EnemyKillCount);
    fprintf(file, "%d\n", game->OnScreenEnemies);
    fprintf(file, "%d\n", game->TankKilled ? 1 : 0);
    fprintf(file, "%d\n", game->TankGenerated ? 1 : 0);
    fprintf(file, "%d\n", game->HelicopterKilled ? 1 : 0);
    fprintf(file, "%d\n", game->HelicopterGenerated ? 1 : 0);
    fprintf(file, "%d\n", game->FinalEnemiesGenerated ? 1 : 0);
    fprintf(file, "%d\n", game->BossGenerated ? 1 : 0);
    fprintf(file, "%d\n", game->Current_Stage);
}

void LoadGameFromFile(FILE* file, Game* game)
{
    int tempInt;
    fscanf(file, "%*s"); // Skip the first line
    fscanf(file, "%d", &game->EnemyKillCount);
    fscanf(file, "%d", &game->OnScreenEnemies);
    fscanf(file, "%d", &tempInt); game->TankKilled = (tempInt != 0);
    fscanf(file, "%d", &tempInt); game->TankGenerated = (tempInt != 0);
    fscanf(file, "%d", &tempInt); game->HelicopterKilled = (tempInt != 0);
    fscanf(file, "%d", &tempInt); game->HelicopterGenerated = (tempInt != 0);
    fscanf(file, "%d", &tempInt); game->FinalEnemiesGenerated = (tempInt != 0);
    fscanf(file, "%d", &tempInt); game->BossGenerated = (tempInt != 0);
    fscanf(file, "%d", &game->Current_Stage);
}

void Game::GameLogic()
{
    if (EnemyKillCount <= 12 && Current_Stage == 1000)
    {
        if (OnScreenEnemies < 2)
        {
            if (!roundScreenShown) // Only show the round screen if it hasn't been shown yet
            {
                missions->setRoundNumber(1);
                missions->setEnabled(true);
                gs->setEnabled(false);
                roundScreenShown = true;
            }

            if (rand() % 3 == 0)
            {
                ListofObjects.add(new Obstacles(gWindow, gRenederer, 1, "data\\Obstacles\\armyTruck.png", screen.w * 1.111, screen.h * 0.555, 138, 71, screen.w * 0.173, screen.h * 0.166, this->gs));
                printf("%f %f\n", screen.w * 1.111, screen.h * 0.555);
            }
            ListofObjects.add(new Enemy(gWindow, gRenederer, 1840, &ListofObjects, 150));
            ListofObjects.add(new Enemy(gWindow, gRenederer, 2040, &ListofObjects, 100));
            OnScreenEnemies += 2;
        }
    }
    else if (Current_Stage == 1000)
    {
        free = false;
        roundScreenShown = false;
    }
    else if (!TankGenerated && Current_Stage == 2000)
    {
        if (!roundScreenShown)
        {
            missions->setRoundNumber(2);
            missions->setEnabled(true);
            gs->setEnabled(false);
            roundScreenShown = true;
        }

        ListofObjects.add(new Tank(gWindow, gRenederer, 1250, 500, &ListofObjects));
        TankGenerated = true;
    }
    else if (TankKilled && Current_Stage == 2000)
    {
        free = false;
        roundScreenShown = false;
    }
    else if (TankKilled && !HelicopterGenerated && Current_Stage == 3000)
    {
        if (!roundScreenShown)
        {
            missions->setRoundNumber(3);
            missions->setEnabled(true);
            gs->setEnabled(false);
            roundScreenShown = true;
        }

        ListofObjects.add(new Helicopter(gWindow, gRenederer, 1440, 50, &ListofObjects));
        HelicopterGenerated = true;
    }
    else if (HelicopterKilled && Current_Stage == 3000)
    {
        free = false;
        roundScreenShown = false;
    }
    else if (HelicopterKilled && !FinalEnemiesGenerated)
    {
        ListofObjects.add(new Enemy(gWindow, gRenederer, 1840, &ListofObjects, 200));
        ListofObjects.add(new Enemy(gWindow, gRenederer, 2040, &ListofObjects, 100));
        ListofObjects.add(new Enemy(gWindow, gRenederer, 2300, &ListofObjects, 150));
        ListofObjects.add(new Enemy(gWindow, gRenederer, 2540, &ListofObjects, 100));
        ListofObjects.add(new Enemy(gWindow, gRenederer, 2740, &ListofObjects, 300));
        ListofObjects.add(new Enemy(gWindow, gRenederer, 2840, &ListofObjects, 200));
        FinalEnemiesGenerated = true;
    }
    else if (FinalEnemiesGenerated && EnemyKillCount >= 18 && !BossGenerated && Current_Stage == 4000)
    {
        ListofObjects.add(new Boss(gWindow, gRenederer, 10, 10, &ListofObjects));
        BossGenerated = true;
    }
}

void Game::ObjectsManager()
{
    Node<GameObjects*>* temNode = ListofObjects.getStart();
    ListofObjects.HasTank = false;
    while (temNode)
    {
        GameObjects* obj = temNode->value;
        if (obj->IsAlive())
        {
            if (strcmp(obj->getType(), "TANK") == 0)
            {
                ListofObjects.HasTank = true;
            }

            Node<GameObjects*>* tNode = ListofObjects.getStart();
            while (tNode)
            {
                obj->CollisionImpact(tNode->value);
                tNode = tNode->next;
            }
            obj->render(counter);
            temNode = temNode->next;
        }
        else
        {
            if (strcmp(obj->getType(), "ENEMY") == 0)
            {
                EnemyKillCount += 1;
                OnScreenEnemies -= 1;
            }
            else if (strcmp(obj->getType(), "TANK") == 0)
            {
                TankKilled = true;
            }
            else if (strcmp(obj->getType(), "HELICOPTER") == 0)
            {
                HelicopterKilled = true;
            }
            if (strcmp(obj->getType(), "BOSS") == 0)
            {
                EnemyKillCount = 0;
                OnScreenEnemies = 0;
                TankKilled = false;
                TankGenerated = false;
                HelicopterKilled = false;
                HelicopterGenerated = false;
                FinalEnemiesGenerated = false;
                Current_Stage = 1000;
                BossGenerated = false;
                win->setEnabled(true);
                gs->setEnabled(false);
                ListofObjects.freeMemory();
                temNode = NULL;
            }
            else if (strcmp(obj->getType(), "HERO") == 0)
            {
                gs->setEnabled(false);
                lose->setEnabled(true);
                EnemyKillCount = 0;
                OnScreenEnemies = 0;
                TankKilled = false;
                TankGenerated = false;
                HelicopterKilled = false;
                HelicopterGenerated = false;
                FinalEnemiesGenerated = false;
                Current_Stage = 1000;
                BossGenerated = false;
                lose->setEnabled(true);
                gs->setEnabled(false);
                ListofObjects.freeMemory();
                temNode = NULL;
            }
            else
            {
                Node<GameObjects*>* toBeDeleted = temNode;

                if (temNode->previous == NULL)
                {
                    temNode = temNode->next;
                    delete ListofObjects.pop(0);
                }
                else if (temNode->next == NULL)
                {
                    temNode = temNode->next;
                    GameObjects* g = ListofObjects.pop();
                    delete g;
                }
                else
                {
                    temNode->next->previous = temNode->previous;
                    temNode->previous->next = temNode->next;
                    delete obj;
                    temNode = temNode->next;
                    delete toBeDeleted;
                }
            }
        }
    }
}

bool Game::EventController()
{
    if (splashScreen->IsEnable())
    {
        if (splashScreen->getButtonPresed() == 1)
        {
            splashScreen->setEnabled(false);
            menu->setEnabled(true);
        }
    }
    else if (menu->IsEnable())
    {
        if (menu->getButtonPresed() == 0)
        {
            if (win->IsEnable())
                win->setEnabled(false);
            if (lose->IsEnable())
                lose->setEnabled(false);

            hero->setAlive(true);
            gs->setEnabled(true);
            menu->setEnabled(false);
        }
        else if (menu->getButtonPresed() == 1)
        {
            LoadGame();
            gs->setEnabled(true);
            menu->setEnabled(false);
        }
        else if (menu->getButtonPresed() == 2)
        {
            Quit = true; // Exit the game
        }
    }
    else if (missions->IsEnable())
    {
        if (missions->getButtonPresed() == 0) // Resume button
        {
            missions->setEnabled(false);
            gs->setEnabled(true);
        }
        else if (missions->getButtonPresed() == 1) // Quit button
        {
            missions->setEnabled(false);
            menu->setEnabled(true); // Return to the main menu
        }
    }
    else if (gs->IsEnable())
    {
        if (gs->getButtonPresed() == 0)
        {
            pauseScreen->setEnabled(true);
            gs->setEnabled(false);
        }
    }
    else if (pauseScreen->IsEnable())
    {
        if (pauseScreen->getButtonPresed() == 0)
        {
            pauseScreen->setEnabled(false);
            gs->setEnabled(true);
        }
        else if (pauseScreen->getButtonPresed() == 1)
        {
            Quit = true; // Exit the game
        }
    }
    else if (win->IsEnable())
    {
        if (win->getButtonPresed())
        {
            win->setEnabled(false);
            menu->setEnabled(true);
        }
    }
    else if (lose->IsEnable())
    {
        if (lose->getButtonPresed())
        {
            lose->setEnabled(false);
            menu->setEnabled(true);
        }
    }
    return true;
}

Game::~Game()
{
    delete hero;
    delete splashScreen;
    delete win;
    delete lose;
    delete menu;
    delete gs;
    delete pauseScreen;
    delete missions;
    delete themeMusic;

    SDL_DestroyRenderer(gRenederer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
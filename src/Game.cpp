#include "Game.h"
#include "LoadAndSave.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <map>

Game::Game(int width, int height, LoadAndSave* file) : WindowSize(width, height) {
    counter = 0;
    spawnCounter = 0; // Initialize new member
    Quit = false;
    File = file;
    roundScreenShown = false;
    free = false;
    Current_Stage = 0;
    EnemyKillCount = 0;
    OnScreenEnemies = 0;
    TankKilled = false;
    TankGenerated = false;
    HelicopterKilled = false;
    HelicopterGenerated = false;
    FinalEnemiesGenerated = false;
    BossGenerated = false;
    DragonGenerated = false;
    DragonKilled = false;
    ter = nullptr;

    printf("Constructor - Current_Stage set to: %d\n", Current_Stage);

    if (Initialize_components()) {
        SDL_Rect x = {0, 0, 1440, 900};
        screen = x;

        gWindow = SDL_CreateWindow("Extinction path", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x.w, x.h, SDL_WINDOW_SHOWN);
        if (!gWindow) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return;
        }

        gRenederer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
        if (!gRenederer) {
            printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            return;
        }

        ter = new terrain(gRenederer);
        ter->pos.x = 0;
        ter->pos.y = 0;

        hero = new Hero(gWindow, gRenederer, &ListofObjects, this);
        ListofObjects.add(hero);

        splashScreen = new SplashScreen(&e, gWindow, gRenederer, "data\\SplashScreen\\Main_splash.png", x.w, x.h);
        win = new WinScreen(&e, gWindow, gRenederer, "data\\SplashScreen\\win_screen.png", x.w, x.h);
        lose = new WinScreen(&e, gWindow, gRenederer, "data\\SplashScreen\\game_over.png", x.w, x.h);
        menu = new Menu(&e, gWindow, gRenederer, "data\\Backgrounds\\menu.jpeg", x.w, x.h);
        gs = new GameScreen(&e, gWindow, gRenederer, "data\\Backgrounds\\main_background.png", x.w, x.h, hero, &ListofObjects);
        pauseScreen = new PauseScreen(&e, gWindow, gRenederer, "data\\Backgrounds\\menu.jpeg", x.w, x.h);
        missions = new Missions(&e, gWindow, gRenederer, "data\\SplashScreen\\missions.png", x.w, x.h);
        themeMusic = new Music("notyet.mp3");

        splashScreen->setEnabled(true);
        themeMusic->Play();

        while (!Quit) {
            while (SDL_PollEvent(&e)) {
                EventController();
                if (e.type == SDL_QUIT)
                    Quit = true;
                if (ListofObjects.getStart() != NULL && gs->IsEnable())
                    hero->EventsController(&e);
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
            else if (gs->IsEnable()) {
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
    } else {
        printf("Game Cannot be started!\n");
    }
}


bool Game::Initialize_components() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void Game::SetCurrentStage(int stage) {
    printf("SetCurrentStage called - Changing Current_Stage from %d to %d at spawnCounter: %d\n", Current_Stage, stage, spawnCounter);
    Current_Stage = stage;
}

void Game::GameLogic() {
    spawnCounter++;
    printf("GameLogic - Current_Stage: %d, EnemyKillCount: %d, OnScreenEnemies: %d, spawnCounter: %d\n", Current_Stage, EnemyKillCount, OnScreenEnemies, spawnCounter);

    // Temporary check to enforce stage progression
    if (Current_Stage > 1 && EnemyKillCount < 12) { // Allow Stage 1 after 12 kills
        printf("Unexpected Current_Stage change detected! Forcing back to 0 (was %d)\n", Current_Stage);
        SetCurrentStage(0);
    } else if (Current_Stage > 2 && EnemyKillCount < 12) { // Reset if too high after Stage 1
        printf("Unexpected Current_Stage change detected! Forcing back to 1 (was %d)\n", Current_Stage);
        SetCurrentStage(1);
    }

    // Stage 0: Initial Enemies
    if (Current_Stage == 0) {
        if (EnemyKillCount < 12 && OnScreenEnemies < 2 && spawnCounter % 60 == 0) {
            if (!roundScreenShown) {
                missions->setRoundNumber(1);
                missions->setEnabled(true);
                gs->setEnabled(false);
                roundScreenShown = true;
            }
            if (rand() % 3 == 0) {
                ListofObjects.add(new Obstacles(gWindow, gRenederer, 1, "data\\Obstacles\\armyTruck.png", screen.w * 1.111, screen.h * 0.555, 138, 71, screen.w * 0.173, screen.h * 0.166, this->gs));
                printf("Spawning obstacle at %f, %f\n", screen.w * 1.111, screen.h * 0.555);
            }
            ListofObjects.add(new Enemy(gWindow, gRenederer, 1840, &ListofObjects, 150, hero));
            ListofObjects.add(new Enemy(gWindow, gRenederer, 2040, &ListofObjects, 100, hero));
            OnScreenEnemies += 2;
            printf("Spawning 2 enemies, OnScreenEnemies: %d, EnemyKillCount: %d\n", OnScreenEnemies, EnemyKillCount);
        }
        if (EnemyKillCount >= 12) {
            free = false;
            roundScreenShown = false;
            SetCurrentStage(1);
            OnScreenEnemies = 0;
            printf("Progressing to Stage 1, EnemyKillCount: %d\n", EnemyKillCount);
        }
    }

    // Stage 1: Tank
    if (Current_Stage == 1 && !TankGenerated) {
        if (!roundScreenShown) {
            missions->setRoundNumber(2);
            missions->setEnabled(true);
            gs->setEnabled(false);
            roundScreenShown = true;
        }   
        ListofObjects.add(new Tank(gWindow, gRenederer, 1250, 500, &ListofObjects));
        ListofObjects.add(new Dragon(gWindow, gRenederer, 1440, 50, &ListofObjects, ter, hero));
        TankGenerated = true;
        printf("Spawning Tank\n");
    } else if (Current_Stage == 1 && TankKilled) {
        free = false;
        roundScreenShown = false;
        SetCurrentStage(2);
        printf("Progressing to Stage 2\n");
    }

    // Stage 2: Dragon
    if (Current_Stage == 2 && !DragonGenerated) {
        if (!roundScreenShown) {
            missions->setRoundNumber(3);
            missions->setEnabled(true);
            gs->setEnabled(false);
            roundScreenShown = true;
        }
        ListofObjects.add(new Dragon(gWindow, gRenederer, 1440, 50, &ListofObjects, ter, hero));
        DragonGenerated = true;
        printf("Spawning Dragon\n");
    } else if (Current_Stage == 2 && DragonKilled) {
        free = false;
        roundScreenShown = false;
        SetCurrentStage(3);
        printf("Progressing to Stage 3\n");
    }

    // Stage 3: Helicopter
    if (Current_Stage == 3 && !HelicopterGenerated) {
        if (!roundScreenShown) {
            missions->setRoundNumber(4);
            missions->setEnabled(true);
            gs->setEnabled(false);
            roundScreenShown = true;
        }
        ListofObjects.add(new Helicopter(gWindow, gRenederer, 1440, 50, &ListofObjects));
        HelicopterGenerated = true;
        printf("Spawning Helicopter\n");
    } else if (Current_Stage == 3 && HelicopterKilled) {
        free = false;
        roundScreenShown = false;
        SetCurrentStage(4);
        printf("Progressing to Stage 4\n");
    }

    // Stage 4: Final Enemies
    if (Current_Stage == 4 && !FinalEnemiesGenerated) {
        if (!roundScreenShown) {
            missions->setRoundNumber(5);
            missions->setEnabled(true);
            gs->setEnabled(false);
            roundScreenShown = true;
        }
        ListofObjects.add(new Enemy(gWindow, gRenederer, 1840, &ListofObjects, 200, hero));
        ListofObjects.add(new Enemy(gWindow, gRenederer, 2040, &ListofObjects, 100, hero));
        ListofObjects.add(new Enemy(gWindow, gRenederer, 2300, &ListofObjects, 150, hero));
        ListofObjects.add(new Enemy(gWindow, gRenederer, 2540, &ListofObjects, 100, hero));
        ListofObjects.add(new Enemy(gWindow, gRenederer, 2740, &ListofObjects, 300, hero));
        ListofObjects.add(new Enemy(gWindow, gRenederer, 2840, &ListofObjects, 200, hero));
        FinalEnemiesGenerated = true;
        OnScreenEnemies += 6;
        printf("Spawning 6 final enemies, OnScreenEnemies: %d\n", OnScreenEnemies);
    } else if (Current_Stage == 4 && EnemyKillCount >= 18) {
        free = false;
        roundScreenShown = false;
        SetCurrentStage(5);
        OnScreenEnemies = 0;
        printf("Progressing to Stage 5\n");
    }

    // Stage 5: Boss
    if (Current_Stage == 5 && !BossGenerated) {
        if (!roundScreenShown) {
            missions->setRoundNumber(6);
            missions->setEnabled(true);
            gs->setEnabled(false);
            roundScreenShown = true;
        }
        ListofObjects.add(new Boss(gWindow, gRenederer, 10, 10, &ListofObjects));
        BossGenerated = true;
        printf("Spawning Boss\n");
    } else if (Current_Stage == 5 && BossGenerated) {
        free = false;
        roundScreenShown = false;
        SetCurrentStage(6);
        printf("Progressing to Stage 6\n");
    }

    // Stage 6: Final Dragon and Win
    if (Current_Stage == 6 && !DragonGenerated) {
        if (!roundScreenShown) {
            missions->setRoundNumber(7);
            missions->setEnabled(true);
            gs->setEnabled(false);
            roundScreenShown = true;
        }
        ListofObjects.add(new Dragon(gWindow, gRenederer, 1440, 50, &ListofObjects, ter, hero));
        DragonGenerated = true;
        printf("Spawning Final Dragon\n");
    } else if (Current_Stage == 6 && DragonKilled) {
        free = false;
        roundScreenShown = false;
        win->setEnabled(true);
        gs->setEnabled(false);
        printf("Game Won!\n");
    }
}

void Game::ObjectsManager() {
    Node<GameObjects*>* temNode = ListofObjects.getStart();
    ListofObjects.HasTank = false;
    static std::map<GameObjects*, bool> renderedLogged;
    static std::map<GameObjects*, bool> removedLogged;

    while (temNode) {
        GameObjects* obj = temNode->value;
        if (!obj) {
            temNode = temNode->next;
            continue;
        }

        if (obj->IsAlive()) {
            if (!renderedLogged[obj]) {
                printf("Rendering %s\n", obj->getType());
                renderedLogged[obj] = true;
            }
            if (strcmp(obj->getType(), "TANK") == 0) {
                ListofObjects.HasTank = true;
            }

            Node<GameObjects*>* tNode = ListofObjects.getStart();
            while (tNode) {
                if (tNode->value && tNode->value != obj) {
                    obj->CollisionImpact(tNode->value);
                    if (strcmp(obj->getType(), "HERO") == 0 && strcmp(tNode->value->getType(), "ENEMYBULLET") == 0 && !tNode->value->IsAlive()) {
                        printf("Hero hit by ENEMYBULLET\n");
                    }
                    if (strcmp(obj->getType(), "ENEMY") == 0 && strcmp(tNode->value->getType(), "HEROBULLET") == 0) {
                        printf("Checking ENEMY vs HEROBULLET collision - Bullet alive: %d\n", tNode->value->IsAlive());
                        if (!tNode->value->IsAlive()) {
                            printf("Enemy hit by HEROBULLET\n");
                            obj->setAlive(false);
                            printf("Enemy IsAlive after hit: %d\n", obj->IsAlive());
                        }
                    }
                }
                tNode = tNode->next;
            }
            obj->render(counter);
            temNode = temNode->next;
        } else {
            if (!removedLogged[obj]) {
                printf("Removing %s\n", obj->getType());
                removedLogged[obj] = true;

                if (strcmp(obj->getType(), "ENEMY") == 0) {
                    EnemyKillCount += 1;
                    if (OnScreenEnemies > 0) OnScreenEnemies -= 1;
                    printf("Enemy killed, EnemyKillCount: %d, OnScreenEnemies: %d\n", EnemyKillCount, OnScreenEnemies);
                } else if (strcmp(obj->getType(), "TANK") == 0) {
                    TankKilled = true;
                } else if (strcmp(obj->getType(), "HELICOPTER") == 0) {
                    HelicopterKilled = true;
                } else if (strcmp(obj->getType(), "BOSS") == 0) {
                    win->setEnabled(true);
                    gs->setEnabled(false);
                } else if (strcmp(obj->getType(), "DRAGON") == 0) {
                    DragonKilled = true;
                } else if (strcmp(obj->getType(), "HERO") == 0) {
                    lose->setEnabled(true);
                    gs->setEnabled(false);
                }
            }

            Node<GameObjects*>* toBeDeleted = temNode;
            temNode = temNode->next;
            if (toBeDeleted->previous == NULL) {
                ListofObjects.pop(0);
            } else if (toBeDeleted->next == NULL) {
                ListofObjects.pop();
            } else {
                toBeDeleted->previous->next = toBeDeleted->next;
                toBeDeleted->next->previous = toBeDeleted->previous;
                delete toBeDeleted->value;
                delete toBeDeleted;
            }
        }
    }
}

bool Game::EventController() {
    if (splashScreen->IsEnable()) {
        if (splashScreen->getButtonPresed() == 1) {
            splashScreen->setEnabled(false);
            menu->setEnabled(true);
        }
    } else if (menu->IsEnable()) {
        if (menu->getButtonPresed() == 0) {
            if (win->IsEnable()) win->setEnabled(false);
            if (lose->IsEnable()) lose->setEnabled(false);
            hero->setAlive(true);
            gs->setEnabled(true);
            menu->setEnabled(false);
        } else if (menu->getButtonPresed() == 1) {
            printf("LoadGame called - Current_Stage before: %d\n", Current_Stage);
            LoadGame();
            printf("LoadGame called - Current_Stage after: %d\n", Current_Stage);
            gs->setEnabled(true);
            menu->setEnabled(false);
        } else if (menu->getButtonPresed() == 2) {
            Quit = true;
        }
    } else if (missions->IsEnable()) {
        if (missions->getButtonPresed() == 0) {
            missions->setEnabled(false);
            gs->setEnabled(true);
        } else if (missions->getButtonPresed() == 1) {
            missions->setEnabled(false);
            menu->setEnabled(true);
        }
    } else if (gs->IsEnable()) {
        if (gs->getButtonPresed() == 0) {
            pauseScreen->setEnabled(true);
            gs->setEnabled(false);
        }
    } else if (pauseScreen->IsEnable()) {
        if (pauseScreen->getButtonPresed() == 0) {
            pauseScreen->setEnabled(false);
            gs->setEnabled(true);
        } else if (pauseScreen->getButtonPresed() == 1) {
            Quit = true;
        }
    } else if (win->IsEnable()) {
        if (win->getButtonPresed()) {
            win->setEnabled(false);
            menu->setEnabled(true);
        }
    } else if (lose->IsEnable()) {
        if (lose->getButtonPresed()) {
            lose->setEnabled(false);
            menu->setEnabled(true);
        }
    }
    return true;
}

void Game::SaveGame() {
    LoadAndSave file(this, gs, gWindow, gRenederer);
    file.Save(&ListofObjects, "data//files//Saved.txt");
}

void Game::LoadGame() {
    LoadAndSave file(this, gs, gWindow, gRenederer);
    file.Load(&ListofObjects, "data//files//Saved.txt");
    if (ter) {
        delete ter;
        ter = new terrain(gRenederer);
        ter->pos.x = 0;
        ter->pos.y = 0;
    }
    printf("LoadGame - Current_Stage after load: %d\n", Current_Stage);
}


Game::~Game() {
    delete splashScreen;
    delete win;
    delete lose;
    delete menu;
    delete gs;
    delete pauseScreen;
    delete missions;
    delete themeMusic;
    delete ter;
    delete hero;
    SDL_DestroyRenderer(gRenederer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}
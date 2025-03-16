#include "LoadAndSave.h"
#include <cstring> 

LoadAndSave::LoadAndSave(Game* game, GameScreen* gamescreen, SDL_Window* window, SDL_Renderer* renderer) {
    this->gamescreen = gamescreen;
    this->game = game;
    gRenderer = renderer;
    gWindow = window;
}

bool LoadAndSave::Save(List<GameObjects*>* list, const char* path) {
    FILE* file = fopen(path, "w");
    if (!file) {
        printf("Failed to open file for saving!\n");
        return false;
    }

    SaveGameToFile(file, game); // Uses Game.h friend function

    Node<GameObjects*>* tempNode = list->getStart();
    while (tempNode) {
        GameObjects* obj = tempNode->value;
        if (strcmp(obj->getType(), "HERO") == 0) {
            SaveHeroToFile(file, (Hero*)obj);
        } else if (strcmp(obj->getType(), "ENEMY") == 0) {
            SaveEnemyToFile(file, (Enemy*)obj); 
        } else if (strcmp(obj->getType(), "TANK") == 0) {
            SaveTankToFile(file, (Tank*)obj);
        } else if (strcmp(obj->getType(), "HELICOPTER") == 0) {
            SaveHelicopterToFile(file, (Helicopter*)obj); 
        } else if (strcmp(obj->getType(), "BOSS") == 0) {
            SaveBossToFile(file, (Boss*)obj); 
        } else if (strcmp(obj->getType(), "OBSTACLE") == 0) {
            SaveObstaclesToFile(file, (Obstacles*)obj); 
        }
        tempNode = tempNode->next;
    }

    fclose(file);
    return true;
}

bool LoadAndSave::Load(List<GameObjects*>* list, const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        printf("Failed to open file for loading!\n");
        return false;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "---GAME---") == 0) {
            LoadGameFromFile(file, game); // Uses Game.h friend function
        } else if (strcmp(line, "---HERO---") == 0) {
            Hero* hero = (Hero*)list->getStart()->value; 
            LoadHeroFromFile(file, hero);
        } else if (strcmp(line, "---ENEMY---") == 0) {
            GameObjects* enemy = new Enemy(gWindow, gRenderer, 1000, list, 400);
            LoadEnemyFromFile(file, (Enemy*)enemy); 
            list->add(enemy);
        } else if (strcmp(line, "---TANK---") == 0) {
            GameObjects* tank = new Tank(gWindow, gRenderer, 1250, 500, list);
            LoadTankFromFile(file, (Tank*)tank); 
            list->add(tank);
        } else if (strcmp(line, "---HELICOPTER---") == 0) {
            GameObjects* helicopter = new Helicopter(gWindow, gRenderer, 100, 50, list);
            LoadHelicopterFromFile(file, (Helicopter*)helicopter); 
            list->add(helicopter);
        } else if (strcmp(line, "---BOSS---") == 0) {
            GameObjects* boss = new Boss(gWindow, gRenderer, 10, 10, list);
            LoadBossFromFile(file, (Boss*)boss); 
            list->add(boss);
        } else if (strcmp(line, "---OBSTACLE---") == 0) {
            GameObjects* obs = new Obstacles(gWindow, gRenderer, 1, "data\\Obstacles\\armyTruck.png", 1600, 500, 138, 71, 250, 150, gamescreen);
            LoadObstaclesFromFile(file, (Obstacles*)obs); 
            list->add(obs);
        }
    }

    fclose(file);
    return true;
}

LoadAndSave::~LoadAndSave() {
    // No dynamic memory to free here currently
}
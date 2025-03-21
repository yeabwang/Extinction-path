#ifndef TANK_H
#define TANK_H

#include <cstdlib> 
#include "Bullet.h"
#include "List.h"
#include "GameObjects.h"
#include "Character.h"
#include "Health.h"
#include "SoundEffects.h"
#include <stdio.h> 

class Tank : public Character {
public:
    Tank(SDL_Window* gWindow, SDL_Renderer* gRenderer, int posX, int posY, List<GameObjects*>* bullets);
    const char* getType(); 
    void render(int frames = 0);
    bool IsAlive();
    void CollisionImpact(GameObjects* CollidedWith);
    Point get_Position();
    Point get_Size();
    void EventsController(SDL_Event* e);
    void Move(int x = 0, int y = 0);
    void setAlive(bool alive);
    virtual ~Tank();
    void fire();

    friend void SaveTankToFile(FILE* file, Tank* tank);
    friend void LoadTankFromFile(FILE* file, Tank* tank);

private:
    bool inframe;
    int cs;
    int counter;
    Health health;
    int bulletsCount;
    bool moving;
    float moveX;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    bool Alive;
    Sprites* sprite[2];
    SDL_Rect* dRect;
    List<GameObjects*>* bullets;
    SoundEffects* sounds[2];
};

#endif // TANK_H
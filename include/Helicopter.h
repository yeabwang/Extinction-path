#ifndef HELICOPTER_H
#define HELICOPTER_H

#include <SDL.h>
#include "Character.h"
#include "List.h"
#include "SoundEffects.h"
#include "Bullet.h"
#include <stdio.h> 

class Helicopter : public Character {
public:
    Helicopter(SDL_Window* gWindow, SDL_Renderer* gRenderer, int posX, int posY, List<GameObjects*>* bullets);
    const char* getType(); 
    void render(int frames);
    bool IsAlive();
    void CollisionImpact(GameObjects* CollidedWith);
    Point get_Position();
    Point get_Size();
    void EventsController(SDL_Event* e);
    void Move(int x = 0, int y = 0);
    void setAlive(bool alive);
    virtual ~Helicopter();
    void fire();

    friend void SaveHelicopterToFile(FILE* file, Helicopter* helicopter);
    friend void LoadHelicopterFromFile(FILE* file, Helicopter* helicopter);

private:
    bool blasted;
    int counter;
    int CounterOfBlast;
    int cs;
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
    SoundEffects* sounds[1];
};

#endif // HELICOPTER_H
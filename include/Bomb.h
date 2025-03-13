#ifndef BOMB_H
#define BOMB_H

#include "List.h"
#include "Sprites.h"
#include "GameObjects.h"
#include "SoundEffects.h"
#include "Hero.h"
#include <cstdio> 

class Bomb : public GameObjects
{
public:
    Bomb(SDL_Window* gWindow, SDL_Renderer* grenderer, int posX, int posY, float moveX, float moveY, const char* description);
    const char* getType();
    bool IsAlive();
    void render(int frames = 0);
    Point get_Position();
    Point get_Size();
    void setAlive(bool alive);
    bool Inframe();
    void Move(int x = 0, int y = 0);
    void CollisionImpact(GameObjects* CollidedWith);
    virtual ~Bomb();

private:
    SoundEffects* sounds[1];
    int counter = 0;
    Sprites* Image;
    Sprites* blast;
    const char* description;
    bool inFrame;
    float x;
    float y;
};

#endif // BOMB_H
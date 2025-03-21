#ifndef BULLET_H
#define BULLET_H

#include "Sprites.h"
#include "GameObjects.h"
#include <cstdio> 

class Bullet : public GameObjects
{
public:
    Bullet(SDL_Window* gWindow, SDL_Renderer* grenderer, int posX, int posY, float moveX, float moveY, const char* description);
    const char* getType(); // Returns type of bullet
    bool IsAlive(); // Returns if the bullet is alive or not
    void render(int frames = 0);
    Point get_Position();
    Point get_Size();
    void setAlive(bool alive);
    bool Inframe(); // Returns whether the bullet is in frame or not
    void Move(int x = 0, int y = 0);
    void CollisionImpact(GameObjects* CollidedWith);
    virtual ~Bullet();

    Bullet() = delete;
    Bullet(const Bullet&) = delete;
    Bullet& operator=(const Bullet&) = delete;

private:
    Sprites* Image;
    const char* description;
    bool inFrame;
    float x;
    float y;
};

#endif // BULLET_H
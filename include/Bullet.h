#ifndef BULLET_H
#define BULLET_H

#include "Sprites.h"
#include "GameObjects.h"
#include <cstdio>

class Bullet : public GameObjects {
public:
    Bullet(SDL_Window* gWindow, SDL_Renderer* grenderer, int posX, int posY, float moveX, float moveY, const char* description, const char* spritePath = "data/bullets/bullet.png");
    const char* getType() override;
    bool IsAlive() override;
    void render(int frames = 0) override;
    Point get_Position() override;
    Point get_Size() override;
    void setAlive(bool alive);
    bool Inframe();
    void Move(int x = 0, int y = 0);
    void CollisionImpact(GameObjects* CollidedWith) override;
    void setTarget(Point target); // Added for homing
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
    bool homing;       // Added for homing behavior
    Point target;      // Target position for homing
};

#endif // BULLET_H
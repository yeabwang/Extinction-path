#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(SDL_Window* gWindow, SDL_Renderer* grenderer, int posX, int posY, float moveX, float moveY, const char* description)
{
    Image = new Sprites(gWindow, grenderer, "data\\bullets\\final.png", 1, posX, posY, 80, 10, 80, 10, "Bullet", true);
    this->x = moveX;
    this->y = moveY;
    this->description = description;
    inFrame = true;
}

const char* EnemyBullet::getType()
{
    return description;
}

bool EnemyBullet::IsAlive()
{
    return inFrame;
}

void EnemyBullet::render(int frames)
{
    Move();
    Image->render();
}

Point EnemyBullet::get_Position()
{
    return Image->get_Position();
}

Point EnemyBullet::get_Size()
{
    return Image->get_Size();
}

void EnemyBullet::setAlive(bool alive)
{
    inFrame = alive;
}

bool EnemyBullet::Inframe()
{
    return inFrame;
}

void EnemyBullet::Move(int x, int y)
{
    if (inFrame)
    {
        if (x != 0)
            this->x = x;
        if (y != 0)
            this->y = y;

        if ((Image->get_Position()).get_X() > 1440 || (Image->get_Position()).get_X() < 0 || (Image->get_Position()).get_Y() > 900 || (Image->get_Position()).get_X() < 0)
        {
            inFrame = false;
        }
        else
        {
            Image->moveDestinationArea(this->x, this->y);
        }
    }
}

void EnemyBullet::CollisionImpact(GameObjects* CollidedWith)
{
    // No implementation needed
}

EnemyBullet::~EnemyBullet()
{
    delete Image;
}
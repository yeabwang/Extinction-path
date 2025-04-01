#include "Bullet.h"

Bullet::Bullet(SDL_Window* gWindow, SDL_Renderer* grenderer, int posX, int posY, float moveX, float moveY, const char* description)
{
    Image = new Sprites(gWindow, grenderer, "data\\bullets\\bullet.png", 1, posX, posY, 16, 11, 16, 11, "Bullet", true);
    this->x = moveX;
    this->y = moveY;
    this->description = description;
    inFrame = true;
}

const char* Bullet::getType()
{
    return description;
}

bool Bullet::IsAlive()
{
    return inFrame;
}

void Bullet::render(int frames)
{
    Move();
    Image->render();
}

Point Bullet::get_Position()
{
    return Image->get_Position();
}

Point Bullet::get_Size()
{
    return Image->get_Size();
}

void Bullet::setAlive(bool alive)
{
    inFrame = alive;
}

bool Bullet::Inframe()
{
    return inFrame;
}

void Bullet::Move(int x, int y)
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

void Bullet::CollisionImpact(GameObjects* CollidedWith)
{
    // No implementation needed
}

Bullet::~Bullet()
{
    delete Image;
}
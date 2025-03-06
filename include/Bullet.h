#ifndef BULLET_H
#define BULLET_H
#include "Sprites.h"

#include "GameObjects.h"
class Bullet: public GameObjects
{
    public:
        Bullet(SDL_Window* gWindow,SDL_Renderer* grenderer,int posX,int posY,float moveX,float moveY,string description);
        string getType();/// returns type of bullet
        bool IsAlive();/// returns if the bullet is alive or not
        void render(int frames=0);
        Point get_Position();
        Point get_Size();
        void setAlive(bool alive);
        bool Inframe();/// returns whether the bullet is in frame or not
        void Move(int x=0,int y=0);
        void CollisionImpact(GameObjects* CollidedWith);
        virtual ~Bullet();
        Bullet()=delete;///deleted this because we will always use overloaded constructor
        Bullet(const Bullet&)=delete; ///deleted this because we won't make any copy
        Bullet& operator=(const Bullet&) = delete;///deleted this because we won't make any assignment

    private:
        Sprites* Image;
        string description;
        bool inFrame;
        float x;
        float y;


};

#endif // BULLET_H

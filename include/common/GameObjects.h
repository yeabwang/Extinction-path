#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include "Point.h"

#include <iostream>
using namespace std;

class GameObjects
{
    public:

        virtual string getType()=0; ///returns type of the object
        virtual void render(int frames=0)=0; /// renders object on screen
        virtual Point get_Position()=0; ///return position of object
        virtual Point get_Size()=0; /// returns size of object
        virtual void Move(int x=0,int y=0)=0; /// moves object
        virtual bool IsAlive()=0; ///returns whether the object is alive or not
        virtual void setAlive(bool alive)=0;
        virtual void CollisionImpact(GameObjects* CollidedWith)=0;///checks collision and does respective action
        virtual ~GameObjects();


    protected:

    private:
};

#endif // GAMEOBJECTS_H

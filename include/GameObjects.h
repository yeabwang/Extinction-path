#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "Point.h"
#include <cstdio> 

class GameObjects
{
public:
    virtual const char* getType() = 0; // Returns type of the object
    virtual void render(int frames = 0) = 0; // Renders object on screen
    virtual Point get_Position() = 0; // Returns position of object
    virtual Point get_Size() = 0; // Returns size of object
    virtual void Move(int x = 0, int y = 0) = 0; // Moves object
    virtual bool IsAlive() = 0; // Returns whether the object is alive or not
    virtual void setAlive(bool alive) = 0; // Sets the alive state of the object
    virtual void CollisionImpact(GameObjects* CollidedWith) = 0; // Checks collision and performs respective action
    virtual ~GameObjects(); // Virtual destructor

protected:
    // No protected members
private:
    // No private members
};

#endif // GAMEOBJECTS_H
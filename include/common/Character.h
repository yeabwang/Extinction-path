#pragma once
#include "SDL.h"
#include "iostream"
#include "Point.h"
#include"Health.h"
#include "GameObjects.h"

using namespace std;

class Character:public GameObjects
{
public:
    virtual void EventsController(SDL_Event* e)=0;///event controlling function
    virtual Point get_Position()=0; /// returns current position of the character
    virtual void Move(int x=0,int y=0)=0;/// moves character
    virtual void render(int frame=0)=0;/// renders character
    virtual ~Character(){}///destructor of character

};

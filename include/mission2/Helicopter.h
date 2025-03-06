#ifndef HELICOPTER_H
#define HELICOPTER_H

#include <../Character.h>
#include "cstdlib"
#include "List.h"
#include "SoundEffects.h"
#include "Bullet.h"
#include "fstream"


class Helicopter : public Character
{
    public:
        Helicopter(SDL_Window* gWindow,SDL_Renderer* gRenderer,int posX,int posY,List<GameObjects*>* bullets);
        string getType();
        void render(int frames);
        bool IsAlive();
        void CollisionImpact(GameObjects* CollidedWith);
        Point get_Position();
        Point get_Size();
        void EventsController(SDL_Event* e);
        void Move(int x=0,int y=0);
        void setAlive(bool alive);
        virtual ~Helicopter();
        void fire();
    protected:


    private:
        bool blasted = false;
        int counter = 0;
        int CounterOfBlast = 0;
        int cs = 0;
        Health health;
        int bulletsCount = 0;
        bool moving = true;
        float moveX = 0;
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
        bool Alive;
        Sprites* sprite[2];
        SDL_Rect* dRect;
        List<GameObjects*>* bullets;
        SoundEffects* sounds[1]{NULL};
        friend  ifstream& operator>>(ifstream& file,Helicopter* helicopter);
        friend  ofstream& operator<<(ofstream& file,Helicopter* helicopter);


    protected:

    private:
};

#endif // HELICOPTER_H

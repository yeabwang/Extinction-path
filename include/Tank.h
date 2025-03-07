#ifndef TANK_H
#define TANK_H
#include "cstdlib"
#include "Bullet.h"
#include "List.h"
#include "GameObjects.h"
#include <../Character.h>
#include <Health.h>
#include "SoundEffects.h"
#include "fstream"


class Tank : public Character
{
    public:
        Tank(SDL_Window* gWindow,SDL_Renderer* gRenderer,int posX,int posY,List<GameObjects*>* bullets);
        string getType();
        void render(int frames=0);
        bool IsAlive();
        void CollisionImpact(GameObjects* CollidedWith);
        Point get_Position();
        Point get_Size();
        void EventsController(SDL_Event* e);
        void Move(int x=0,int y=0);
        void setAlive(bool alive);
        virtual ~Tank();
        void fire();
        friend  ofstream& operator<<(ofstream& file,Tank* tank);
        friend  ifstream& operator>>(ifstream& file,Tank* tank);

    protected:


    private:
        bool inframe = false;
        int cs=0;
        int counter=0;
        Health health;
        int bulletsCount =0;
        bool moving = true;
        float moveX=0;
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
        bool Alive;
        Sprites* sprite[2];
        SDL_Rect* dRect;
        List<GameObjects*>* bullets;
        SoundEffects* sounds[2]{NULL};


};

#endif // TANK_H

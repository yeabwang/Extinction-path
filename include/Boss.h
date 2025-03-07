#ifndef BOSS_H
#define BOSS_H
#include "Bomb.h"
#include "List.h"
#include "SoundEffects.h"
#include <../Character.h>
#include "Bullet.h"


class Boss : public Character
{
    public:
        Boss(SDL_Window* gWindow,SDL_Renderer* gRenderer,int posX,int posY,List<GameObjects*>* bullets);
        virtual ~Boss();
        string getType();
        void render(int frames=0);
        bool IsAlive();
        void CollisionImpact(GameObjects* CollidedWith);
        Point get_Position();
        Point get_Size();
        void EventsController(SDL_Event* e);
        void Move(int x=0,int y=0);
        void setAlive(bool alive);
        void fire(int frame);
        friend ifstream& operator>>(ifstream& file,Boss* boss);
        friend ofstream& operator<<(ofstream& file,Boss* boss);



    protected:


    private:
        bool blasted = false;
        bool left = true;
        int counter = 0;
        int CounterOfBlast = 0;
        int cs = 0;
        Health health;
        int bulletsCount = 0;
        bool moving = true;
        int moveX = 0;
        SDL_Window* gWindow;
        SDL_Renderer* gRenderer;
        bool Alive;
        Sprites* sprite[2];
        SDL_Rect* dRect;
        List<GameObjects*>* bullets;
        SoundEffects* sounds[2]{NULL};




    protected:

    private:
};

#endif // BOSS_H

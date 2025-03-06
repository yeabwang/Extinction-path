#ifndef ENEMY_H
#define ENEMY_H
#include "cstdlib"
#include <../Character.h>
#include "Bullet.h"
#include "SoundEffects.h"
#include "List.h"
#include "Hero.h"
class Enemy : public Character
{
    public:
        /// for description of these functions see description of Character.h
        Enemy(SDL_Window* gWindow,SDL_Renderer* grenderer,int posX,List<GameObjects*>* bullets,int delay);
        void EventsController(SDL_Event* e){};
        Point get_Position();
        void Move(int x=0,int  y=0);
        void setAlive(bool alive);
        void render(int frame=0);
        bool fire(int frame);
        virtual ~Enemy();
        string getType();
        Point get_Size();
        void CollisionImpact(GameObjects* CollidedWith);
        bool IsAlive();
        Enemy()=delete;///deleted this because we will always use overloaded constructor
        Enemy(const Bullet&)=delete; ///deleted this because we won't make any copy
        Enemy& operator=(const Bullet&) = delete;///deleted this because we won't make any assignment

        friend ofstream& operator<<(ofstream& file,Enemy* enemy);
        friend ifstream& operator>>(ifstream& file,Enemy* enemy);


    private:
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        SDL_Rect screen;
        Hero* hero;
        int delay ;
        int count =0;
        bool fired=false;
        bool alive=true;
        SDL_Window* gWindow;
        SDL_Renderer* grenderer;
        List<GameObjects*>* bullets;//enemy bullet list
        SDL_Rect* dRect=NULL;
        int movey = false;
        int movex = false;
        int cs=0;
        string description = "ENEMY";
        SoundEffects* sound[2];
        Sprites* EnemyStates[2]{NULL};
        int health=5;

};

#endif // ENEMY_H

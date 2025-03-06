#ifndef HERO_H
#define HERO_H
#include"cstdlib"
#include "Sprites.h"
#include "Bullet.h"
#include "List.h"
#include <../Character.h>
#include "SoundEffects.h"
#include "iostream"
#include "fstream"
#include <sstream>
#include "Obstacles.h"
using namespace std;
class Game;
class Hero : public Character
{
    SDL_Rect screen;
    Health health; /// created an object of health
    SDL_RendererFlip flip = SDL_FLIP_NONE; ///stores flipping state
    bool moved = false; /// keep track if the object is moved or not
    bool Alive = true;
    bool collided= false; /// for checking top collision
    int count =0; /// for sprite changing purposes
    bool shootUp=false; /// for sprite changing purposes
    bool fire=false;
    SDL_Window* gWindow; /// storing this because bullets will need this for rendering
    SDL_Renderer* grenderer; /// storing this because bullets will need this for rendering
    List<GameObjects*>* bullets; /// storing this because bullets fired by hero will be added in this
    bool jump = false; /// will be true when Up button will be pressed will become false when hero will reach peak
    bool jumping = false; /// will be true when Up button will be pressed and will stay true until jump is complete
    int movey = 0;
    int movex = 0;
    bool onground=true; /// true if object is on ground
    int ground =0; /// stores grounds y coordinate
    int cs=0; /// keeps track of current sprite
    SoundEffects* sound[2];
    Sprites* HeroStates[4];
    bool running = false;
    int CollidedWithId = 0;
    SDL_Rect* dRect=NULL;
    Hero()=delete;///deleted this because we will always use overloaded constructor
    Hero(const Hero&)=delete; ///deleted this because we won't make any copy
    Hero& operator=(const Hero&) = delete;///deleted this because we won't make any assignment

public:
    /// see Object.h for the description these functions
    Hero(SDL_Window* gWindow,SDL_Renderer* grenderer,List<GameObjects*>* lst,Game* gm_ptr);
    bool IsMoved();
    void setAlive(bool alive);
    bool IsAlive();
    void render(int frames);
    void Move(int x=0,int y=0);
    void EventsController(SDL_Event* e);
    Point get_Position();
    Point get_Size();
    string getType();
    void DecreaseHealth(); ///decreases health by 1
    void CollisionImpact(GameObjects* CollidedWith);
    friend  ofstream& operator<<(ofstream& file,Hero* hero);
    friend  ifstream& operator>>(ifstream& file,Hero* hero);
    Game* gm_ptr;
    virtual ~Hero();



};



#endif // HERO_H

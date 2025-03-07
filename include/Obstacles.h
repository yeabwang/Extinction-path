#ifndef OBSTACLES_H
#define OBSTACLES_H
#include <iostream>
#include <cstdlib>
#include <GameObjects.h>
#include "SoundEffects.h"
#include "Sprites.h"
#include "GameScreen.h"

#include "fstream"
using namespace std;




class Obstacles : public GameObjects
{

    public:

        Obstacles(SDL_Window* gWindow,SDL_Renderer* grenderer,int NOS,string path ,int posX,int posY,int sWidth,int sHeight,int width, int height,GameScreen* gs);
        string getType();
        bool IsAlive();
        void render(int frames=0);
        void setAlive(bool alive);
        Point get_Position();
        Point get_Size();
        int objectId;
        void Move(int x=0,int y=0);
        void CollisionImpact(GameObjects* CollidedWith);
        virtual ~Obstacles();
        void setAlive();
        static int  ID;
        friend ofstream& operator<<(ofstream& file,Obstacles* ob);
        friend ifstream& operator>>(ifstream& file,Obstacles* ob);

    protected:

    private:

        SoundEffects* sounds[1];
         Sprites* sprite[2];
         int counter =0;
        bool inFrame = true;
        int cs=0;
        GameScreen * gamescreen=NULL;
        SDL_Rect* dRect;
};

#endif // OBSTACLES_H

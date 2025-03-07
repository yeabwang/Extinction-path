#include "Obstacles.h"


int Obstacles::ID=0;


Obstacles::Obstacles(SDL_Window* gWindow,SDL_Renderer* grenderer,int NOS,string path ,int posX,int posY,int sWidth,int sHeight,int width, int height,GameScreen* gs)
        {
            ID+=1;
            objectId = ID;
            sounds[0] = new SoundEffects("data\\common\\blast.wav");
            dRect = new SDL_Rect{posX,posY,width,height};
            sprite[0] = new Sprites(gWindow,grenderer,path,NOS,sWidth,sHeight,dRect,"obstacle",true);
            sprite[1] = new Sprites(gWindow,grenderer,"data\\tanks\\Image\\blast1.png",7,945/7,176,dRect,"",true);
            gamescreen = gs;

        }



string Obstacles::getType()
        {
            return "OBSTACLE";
        }

bool Obstacles::IsAlive()
        {
            return inFrame;
        }

void Obstacles::render(int frames)
{
    if (gamescreen->IsMoved())
    {
        Move(-3);
    }
    ///counter for blast
    if (counter>0)
    {
        if(counter==1)
            inFrame= false;
        counter-=1;

    }

    sprite[cs]->render(frames);
    if(get_Position().get_X()+get_Size().get_X()<0)
        inFrame = false;

}

void Obstacles::setAlive(bool alive)
{
    this->inFrame = alive;
}

Point Obstacles::get_Position()
{
    Point p(dRect->x,dRect->y);
    return p;
}
Point Obstacles::get_Size()
{
    Point p(dRect->w,dRect->h);
    return p;
}

void Obstacles::Move(int x,int y)
{
    sprite[cs]->moveDestinationArea(x,y);
}


void Obstacles::CollisionImpact(GameObjects* CollidedWith)
{
    if(CollidedWith->getType()=="TANK")
    {

        SDL_Rect collide ={(CollidedWith->get_Position()).get_X(),(CollidedWith->get_Position()).get_Y(),(CollidedWith->get_Size()).get_X(),(CollidedWith->get_Size()).get_Y()};

        SDL_Rect* dRect = new SDL_Rect{get_Position().get_X(),get_Position().get_Y(),get_Size().get_X(),get_Size().get_Y()};
        if(SDL_HasIntersection(&collide,dRect))
        {

            sounds[0]->Play();
            if(counter==0)
            {

                counter=40;

            }
            cs=1;
        }
    }
}



Obstacles:: ~Obstacles()
{
    for (int i=0;i<2;i++)
        delete  sprite[i];
}



void Obstacles::setAlive()
{
    inFrame = true;
}




ofstream& operator<<(ofstream& file,Obstacles* ob)
{
    file<<"---OBSTACLE---"<<endl;
    file<<ob->inFrame<<endl;
    file<<ob->cs<<endl;
    file<<ob->counter<<endl;
    file<<ob->dRect->y<<endl;
    file<<ob->dRect->x<<endl;
    return file;
}


ifstream& operator>>(ifstream& file,Obstacles* ob)
{

    string str;
    file>>str;
    ob->inFrame= atoi(str.c_str());
    file>>str;
    ob->cs= atoi(str.c_str());
    file>>str;
    ob->counter = atoi(str.c_str());
    file>>str;
    ob->dRect->y = atoi(str.c_str());
    file>>str;
    ob->dRect->x = atoi(str.c_str());
    return file;


}

#include "Health.h"
Health::Health(int health,SDL_Window* gWindow,SDL_Renderer* gRenderer,int posx,int posy)
{
    intitalHealth = health;
    dRect1 = new SDL_Rect{posx,posy,health,5};
    dRect = new SDL_Rect{posx,posy,health,5};
    bar[0] = new Sprites(gWindow,gRenderer,"data\\common\\bar.png",1,100,3,dRect1,"");
    bar[1] = new Sprites(gWindow,gRenderer,"data\\common\\highHealth.png",1,100,3,dRect,"");
    bar[2] = new Sprites(gWindow,gRenderer,"data\\common\\lowHealth.png",1,100,3,dRect,"");
    bar[3] = new Sprites(gWindow,gRenderer,"data\\common\\verylowHealth.png",1,100,3,dRect,"");
    this->health = health;
}
void Health:: display(int x, int y)
{
    dRect->x = x;
    dRect->y = y;
    dRect1->x = x;
    dRect1->y = y;

    bar[0]->render();
    if(health>50)
    {
        cs=1;
    }
    else if(health>25)
    {
        cs=2;
    }
    else
    {
        cs=3;
    }




    bar[cs]->render();
}
int Health::get_Health()
{
    return health;
}



void Health::set_Health(int health)
{
    this->health = health;
     dRect->w=health;
}
void Health::decrease(int n)
{


        health-=n;
        dRect->w-=n;
    if(health<=0)
    {
        health=0;
        dRect->w=0;
    }


}
void Health::increase(int n)
{

        health+=n;
        dRect->w+=n;


    if(health>= intitalHealth )//se
    {
        health=intitalHealth;
        dRect->w=intitalHealth;
    }
}


Health::~Health()
{

    for (int i=0;i<4;i++)
    {
        delete bar[i];
    }

}

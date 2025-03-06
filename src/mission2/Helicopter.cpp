#include "Helicopter.h"

Helicopter::Helicopter(SDL_Window* gWindow,SDL_Renderer* gRenderer,int posX,int posY,List<GameObjects*>* bullets):health(100,gWindow,gRenderer,posX,posY-20)
{
    Alive = true;
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    this->bullets = bullets;
    dRect = new SDL_Rect{posX,posY,250,150};
    sprite[0] = new Sprites(gWindow,gRenderer,"data\\Aircrafts\\helicopter.png",16,2000/16,128,dRect,"",true);
    sprite[1] = new Sprites(gWindow,gRenderer,"data\\tanks\\Image\\blast1.png",7,945/7,176,dRect,"",true);
    sounds[0] = new SoundEffects("data\\common\\blast.wav");
}

string Helicopter::getType()
{
    return "HELICOPTER";
}

void Helicopter::render(int frames)
{
    GameObjects* hero = bullets->getStart()->value;
    int Hx = (hero->get_Position()).get_X();
            int Ex = get_Position().get_X();
            if(Ex-Hx>0)
            {
                Move(-2);
            }
            else
            {
                Move(2);
            }
    if(CounterOfBlast<0 && blasted)
    {

        Alive =false;
    }
    else if(blasted)
    {
        CounterOfBlast--;
    }

    fire();
    health.display(dRect->x,dRect->y);
    sprite[cs]->render(frames);
}

bool Helicopter::IsAlive()
{
    return Alive;
}

void Helicopter::CollisionImpact(GameObjects* CollidedWith)
{
    if (CollidedWith->getType()=="HEROBULLET")
    {
        SDL_Rect collide ={(CollidedWith->get_Position()).get_X(),(CollidedWith->get_Position()).get_Y(),(CollidedWith->get_Size()).get_X(),(CollidedWith->get_Size()).get_Y()};
        if(SDL_HasIntersection(&collide,dRect))
        {
            CollidedWith->setAlive(false);
            health.decrease(1);
            if(health.get_Health()==0)
            {

                if(CounterOfBlast==0)
                {
                    sounds[0]->Play();
                    blasted = true;
                    CounterOfBlast=30;
                    cs=1;
                }

            }

        }
    }


}

Point Helicopter::get_Position()
{
    return sprite[cs]->get_Position();
}



Point Helicopter::get_Size()
{
    return sprite[cs]->get_Size();
}

void Helicopter::EventsController(SDL_Event* e)
{

}


void Helicopter::Move(int x,int y)
{
    sprite[cs]->moveDestinationArea(x,y);
}

void Helicopter::setAlive(bool alive)
{
    this->Alive = alive;
}




Helicopter::~Helicopter()
{

    for(int i=0;i<2;i++)
        delete sprite[i];
    for(int i=0;i<1;i++)
        delete sounds[i];
}

void Helicopter::fire()
{

    GameObjects* haro = bullets->getStart()->value;
    SDL_Rect helicopter ={(dRect->x)+(dRect->w/3),(haro->get_Position()).get_Y(),dRect->w/3,dRect->h};
    SDL_Rect hero ={(haro->get_Position()).get_X(),(haro->get_Position()).get_Y(),(haro->get_Size()).get_Y(),(haro->get_Size()).get_Y()};
    if(counter == 0)
    {
      if((SDL_HasIntersection(&helicopter,&hero)))
        {
            bullets->add(new Bullet(gWindow,gRenderer,(dRect->x)+(dRect->w/2),(dRect->y)+(dRect->h),0,3,"ENEMYBULLET"));
            counter =50;
        }
    }
    else
    {
        counter--;
    }

}

ofstream& operator<<(ofstream& file,Helicopter* helicopter)
    {
        file<<"---HELICOPTER---"<<endl;
        file<<helicopter->blasted<<endl;
        file<<helicopter->counter<<endl;
        file<<helicopter->CounterOfBlast<<endl;
        file<<helicopter->cs<<endl;
        file<<helicopter->bulletsCount<<endl;
        file<<helicopter->moving<<endl;
        file<<helicopter->moveX<<endl;
        file<<helicopter->Alive<<endl;
        file<<(helicopter->dRect->x)<<endl;
        file<<(helicopter->dRect->y)<<endl;
        file<<helicopter->health.get_Health()<<endl;
        return file;
    }

ifstream& operator>>(ifstream& file,Helicopter* helicopter)
    {
        string str;
        file>>str;
        helicopter->blasted= atoi(str.c_str());
        file>>str;
        helicopter->counter= atoi(str.c_str());
        file>>str;
        helicopter->CounterOfBlast= atoi(str.c_str());
        file>>str;
        helicopter->cs= atoi(str.c_str());
        file>>str;
        helicopter->bulletsCount= atoi(str.c_str());
        file>>str;
        helicopter->moving= atoi(str.c_str());
        file>>str;
        helicopter->moveX= atoi(str.c_str());
        file>>str;
        helicopter->Alive= atoi(str.c_str());
        file>>str;
        helicopter->dRect->x = atoi(str.c_str());
        file>>str;
        helicopter->dRect->y = atoi(str.c_str());
        file>>str;
        helicopter->health.set_Health(atoi(str.c_str()));
        return file;
    }

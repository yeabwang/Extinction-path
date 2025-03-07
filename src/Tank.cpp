#include "Tank.h"

Tank::Tank(SDL_Window* gWindow,SDL_Renderer* gRenderer,int posX,int posY,List<GameObjects*>* bullets):health(100,gWindow,gRenderer,posX,posY-20)
{
    Alive = true;
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    this->bullets = bullets;
    dRect = new SDL_Rect{posX,posY,250,150};
    sprite[0] = new Sprites(gWindow,gRenderer,"data\\tanks\\Image\\Tank.png",20,1320/20,56,dRect,"",true);
    sprite[1] = new Sprites(gWindow,gRenderer,"data\\tanks\\Image\\blast1.png",7,945/7,176,dRect,"",true);
    sounds[0] = new SoundEffects("data\\common\\blast.wav");
}

string Tank::getType()
{
    return "TANK";
}

void Tank::render(int frames)
{
    static bool start= false;
    if(!inframe)
    {
        if(dRect->x==1250)
        {
            inframe=true;
        }
        else
        {
            dRect--;
        }
    }
    else
    {

        if (start && counter==0)
        {

            if(bulletsCount ==3)
            {
                if(frames%100==0 && moving)
                {
                    moveX+=1.99;
                }

                if ((dRect->x)<50 && moving)
                {
                   // exit(0);
                    moving= false;
                    moveX=-2;
                }
                else if ((dRect->x)>1250 && !moving)
                {
                    moving = true;
                    moveX=0;
                    bulletsCount =0;
                }
                Move(-moveX,0);
            }
            else
            {
                if(frames%100==0)
                {
                    fire();
                    bulletsCount+=1;
                }

            }
        }

    }



    if (counter>0)
    {
        if(counter==1)
            Alive= false;
        counter-=1;

    }

    health.display(dRect->x,dRect->y);
    sprite[cs]->render(frames,SDL_FLIP_HORIZONTAL);

    start= true;
}

bool Tank::IsAlive()
{
    return Alive;
}

void Tank::CollisionImpact(GameObjects* CollidedWith)
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
                sounds[0]->Play();
                if(counter==0)
                {

                    counter=45;

                }
                cs=1;
            }

        }
    }


}

Point Tank::get_Position()
{
    return sprite[cs]->get_Position();
}



Point Tank::get_Size()
{
    return sprite[cs]->get_Size();
}

void Tank::EventsController(SDL_Event* e)
{

}


void Tank::Move(int x,int y)
{
    sprite[cs]->moveDestinationArea(x,y);
}

void Tank::setAlive(bool alive)
{
    this->Alive = alive;
}




Tank::~Tank()
{

    for(int i=0;i<2;i++)
        delete sprite[i];
    for(int i=0;i<1;i++)
        delete sounds[i];



}

void Tank::fire()
{
    bullets->add(new Bullet(gWindow,gRenderer,dRect->x,dRect->y+55,-10,0,"ENEMYBULLET"));
}


ofstream& operator<<(ofstream& file,Tank* tank)
{
    file<<"---TANK---"<<endl;
    file<<tank->inframe<<endl;
    file<<tank->health.get_Health()<<endl;
    file<<tank->cs<<endl;
    file<<tank->counter<<endl;
    file<<tank->bulletsCount<<endl;
    file<<tank->moving<<endl;
    file<<tank->moveX<<endl;
    file<<tank->Alive<<endl;
    file<<(tank->dRect->x)<<endl;
    file<<(tank->dRect->y)<<endl;
    return file;
}


ifstream& operator>>(ifstream& file,Tank* tank)
{

    string str;///int lives= atoi(str.c_str());
    file>>str;
    tank->inframe= atoi(str.c_str());
    file>>str;
    tank->health.set_Health(atoi(str.c_str()));
    file>>str;
    tank->cs= atoi(str.c_str());
    file>>str;
    tank->counter = atoi(str.c_str());
    file>>str;
    tank->bulletsCount= atoi(str.c_str());
    file>>str;
    tank->moving = atoi(str.c_str());
    file>>str;
    tank->moveX = atoi(str.c_str());
    file>>str;
    tank->Alive = atoi(str.c_str());
    file>>str;
    tank->dRect->x = atoi(str.c_str());
    file>>str;
    tank->dRect->y = atoi(str.c_str());
    return file;

}

#include "Boss.h"

Boss::Boss(SDL_Window* gWindow,SDL_Renderer* gRenderer,int posX,int posY,List<GameObjects*>* bullets):health(150,gWindow,gRenderer,posX,posY-20)
{
    Alive = true;
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    this->bullets = bullets;
    dRect = new SDL_Rect{posX,posY,1200,400};
    sprite[0] = new Sprites(gWindow,gRenderer,"data\\Boss\\Boss.png",12,3264/12,146,dRect,"",true);
    sprite[1] = new Sprites(gWindow,gRenderer,"data\\tanks\\Image\\blast1.png",7,945/7,176,dRect,"",true);
    sounds[0] = new SoundEffects("data\\common\\blast.wav");
}

Boss:: ~Boss()
{
    for(int i=0; i<2;i++)
        delete sprite[i];
    for(int i=0; i<1;i++)
        delete sounds[i];

}
string Boss:: getType()
{
    return "BOSS";
}

void Boss::render(int frames)
{
    if(frames%100==0 && moving)
    {
        moveX+=1.99;
    }

    if ((dRect->x)<-100 && moving)
    {
       // exit(0);
        moving= false;
        moveX=-2;
    }
    else if ((dRect->x)+(dRect->w)>1500 && !moving)
    {
        moving = true;
        moveX=0;
        bulletsCount =0;


    }
            Move(-moveX,0);



    health.display(dRect->x,dRect->y);

    if(health.get_Health()<=0)
    {
        Alive = false;
    }



    sprite[cs]->render(frames);

    fire(frames);

}

bool Boss::IsAlive()
{
    return Alive;
}

void Boss::CollisionImpact(GameObjects* CollidedWith)
{

    if (CollidedWith->getType()=="HEROBULLET")
    {
        SDL_Rect collide ={(CollidedWith->get_Position()).get_X(),(CollidedWith->get_Position()).get_Y(),(CollidedWith->get_Size()).get_X(),(CollidedWith->get_Size()).get_Y()};
        SDL_Rect thisRect = {dRect->x,dRect->y,dRect->w,dRect->h-50};
        if(SDL_HasIntersection(&collide,&thisRect))
        {
            CollidedWith->setAlive(false);
            health.decrease(1);


        }
    }

}

Point Boss::get_Position()
{
    return sprite[cs]->get_Position();
}



Point Boss::get_Size()
{
    return sprite[cs]->get_Size();
}

void Boss::EventsController(SDL_Event* e)
{

}


void Boss::Move(int x,int y)
{
    sprite[cs]->moveDestinationArea(x,y);
}

void Boss::setAlive(bool alive)
{
    this->Alive = alive;
}


void Boss::fire(int frame)
{
    if(frame%200==0)
    {

        if(left)
        {
            bullets->add( new Bomb(gWindow,gRenderer,dRect->x+100,dRect->y+250,0,5,"BOMB"  ));
            left= false;
        }
        else
        {
            left =true;
            bullets->add( new Bomb(gWindow,gRenderer,dRect->x+1000,dRect->y+250,0,5,"BOMB")  );
        }

        bullets->add( new Bomb(gWindow,gRenderer,dRect->x+dRect->w/2,dRect->y+250,0,5,"BOMB")  );

    }

    if (frame%100==0)
        {
            bullets->add(new Bullet(gWindow,gRenderer,dRect->x+390,dRect->y+22,0,5,"ENEMYBULLET"));
            bullets->add(new Bullet(gWindow,gRenderer,dRect->x+790,dRect->y+22,0,5,"ENEMYBULLET"));
        }
}





































ofstream& operator<<(ofstream& file,Boss* boss)
    {

        file<<"---BOSS---"<<endl;
        file<<boss->left<<endl;
        file<<boss->blasted<<endl;
        file<<boss->counter<<endl;
        file<<boss->CounterOfBlast<<endl;
        file<<boss->cs<<endl;
        file<<boss->bulletsCount<<endl;
        file<<boss->moving<<endl;
        file<<boss->moveX<<endl;
        file<<boss->Alive<<endl;
        file<<(boss->dRect->x)<<endl;
        file<<(boss->dRect->y)<<endl;
        file<<boss->health.get_Health()<<endl;
        return file;
    }

ifstream& operator>>(ifstream& file,Boss* boss)
    {

        string str;
        file>>str;
        boss->left= atoi(str.c_str());
        file>>str;
        boss->blasted= atoi(str.c_str());
        file>>str;
        boss->counter= atoi(str.c_str());
        file>>str;
        boss->CounterOfBlast= atoi(str.c_str());
        file>>str;
        boss->cs= atoi(str.c_str());
        file>>str;
        boss->bulletsCount= atoi(str.c_str());
        file>>str;
        boss->moving= atoi(str.c_str());
        file>>str;
        boss->moveX= atoi(str.c_str());
        file>>str;
        boss->Alive= atoi(str.c_str());
        file>>str;
        boss->dRect->x = atoi(str.c_str());
        file>>str;
        boss->dRect->y = atoi(str.c_str());
        file>>str;
        boss->health.set_Health(atoi(str.c_str()));
        return file;
    }

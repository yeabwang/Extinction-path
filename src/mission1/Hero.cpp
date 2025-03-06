#include "Hero.h"
#include "Game.h"
Hero::Hero(SDL_Window* gWindow,SDL_Renderer* grenderer,List<GameObjects*>* lst,Game* gm_ptr):health(100,gWindow,grenderer,1,490)
{
    SDL_GetDisplayBounds(0,&screen);
    this->gm_ptr = gm_ptr;
    this->bullets =lst;
    this->gWindow= gWindow;
    this->grenderer= grenderer;
    dRect = new SDL_Rect{1,550,200,100};
    sound[0]= new SoundEffects("data\\hero\\sounds\\fire.wav");
    sound[1]= new SoundEffects("data\\hero\\sounds\\effected.wav");
    HeroStates[1] = new Sprites(gWindow,grenderer,"data\\hero\\running.png",12,576/12,41,dRect,"data\\hero\\standing.png",true);
    HeroStates[0] = new Sprites(gWindow,grenderer,"data\\hero\\standing.png",30,1200/30,44,dRect,"data\\hero\\standing.png",true);
    HeroStates[2] = new Sprites(gWindow,grenderer,"data\\hero\\fire.png",13,4000/13,191,dRect,"data\\hero\\standing.png",true);
    HeroStates[3] = new Sprites(gWindow,grenderer,"data\\hero\\fireUp.png",9,810/9,118,dRect,"data\\hero\\standing.png",true);

    dRect = dRect;
    ground = dRect->y+dRect->h;
    cout<<get_Position()<<"pic height:"<<get_Size()<<endl;
}
bool Hero::IsMoved()
{
    return moved;
}

void Hero:: setAlive(bool alive)
{
        this->Alive = alive;
        health.set_Health(100);
        dRect->x=1;
        dRect->y=550;
        dRect->w =200;
        dRect->h =100;
}

bool Hero::IsAlive()
{
    return Alive;
}
void Hero::render(int frames)
{
    ///checking whether the hero is alive or not
    if(health.get_Health()==0)
    {
        Alive = false;
    }
    /// checking for jump
    if (jump && jumping && movey<0)
    {
        movey*=0.95;

    }
    else if (jump && movey==0)
    {
        jump= false;
        movey= 1;
    }
    else if (jumping)
    {
        movey= 9;
        if ((this->get_Position()).get_Y()+(this->get_Size()).get_Y()>=ground)
            {
                movey=0;jump=0;jumping=0;dRect->y=550;
                onground = true;
            }
            if(collided )
                    movey =0;

    }
    /// checking for the movement in screen bounds
    if (!(gm_ptr->free))
    {
         if((HeroStates[cs]->get_Position()).get_X()+(HeroStates[cs]->get_Size()).get_X()+movex >=640  || (HeroStates[cs]->get_Position()).get_X()+(HeroStates[cs]->get_Size()).get_X()+movex <=10)
        {
            if( movex>0)
                 movex=0;
        }

    }
    else
    {
        if((HeroStates[cs]->get_Position()).get_X()+(HeroStates[cs]->get_Size()).get_X()+movex >=1400 || (HeroStates[cs]->get_Position()).get_X()+(HeroStates[cs]->get_Size()).get_X()+movex <=10)
            movex=0;
    }
    if (Alive)
    {
        if (!fire)
        {
            if (movex!=0 ||movey!=0 ||running)
            {
                cs=1;
                HeroStates[cs]->render(frames,flip);
            }
            else
            {
                cs=0;
                HeroStates[cs]->render(frames*2,flip);
            }
        }
        else
        {
            if (shootUp)
                {
                    cs=3;
                    HeroStates[cs]->render(0,flip);
                }
            else
                {
                    cs=2;
                    count--;
                    HeroStates[cs]->render(0,flip);
                }
        }
        if (count==0)
        {
            fire=false;
        }
    }

    Move(movex,movey);
    health.display(dRect->x,dRect->y-10);
}





void Hero::Move(int x,int y)
{
    if(dRect->x+x<1)
        x=0;
    HeroStates[cs]->moveDestinationArea(x,y);
}




void Hero::EventsController(SDL_Event* e)
{

    static int counter =0;
    if (counter !=0)
    {
        counter--;
    }
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        if (!jumping)
                {jump = true;movey = -30;jumping = true;onground=false;}


    }

    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        flip = SDL_FLIP_HORIZONTAL;
        running = true;
        jumping=true;
        movex=-6;

    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        running = true;
        flip = SDL_FLIP_NONE;

        jumping=true;
        movex =5;///5
        moved = true;
    }
     else
    {
        running = false;
        movex=0;jumping=true;
        moved = false;
    }

     if (currentKeyStates[ SDL_SCANCODE_X])
     {
         shootUp = true;
     }
     else
    {
        shootUp = false;
    }



        if(e->key.keysym.sym == SDLK_SPACE && e->type == SDL_KEYUP&& e->key.repeat==0)//.key.keysym.sym==SDLK_sp &&
        {

                count=20;
                if (shootUp)
                {
                     fire=true;
                     if (!flip)
                        bullets->add(new Bullet(gWindow,grenderer,(this->get_Position()).get_X()+50,(this->get_Position()).get_Y(),0,-10,"HEROBULLET"));
                     else
                        bullets->add(new Bullet(gWindow,grenderer,(this->get_Position()).get_X()+dRect->w-50,(this->get_Position()).get_Y(),0,-10,"HEROBULLET"));

                     sound[0]->Play();
                }
                else
                {
                     fire=true;
                     if (!flip)
                        bullets->add( new Bullet(gWindow,grenderer,(this->get_Position()).get_X()+(this->get_Size()).get_X(),(this->get_Position()).get_Y()+50,10,0,"HEROBULLET"));
                     else
                        bullets->add( new Bullet(gWindow,grenderer,(this->get_Position()).get_X(),(this->get_Position()).get_Y()+50,-10,0,"HEROBULLET"));

                     sound[0]->Play();
                }
    }

}




Point Hero::get_Position()
{
    Point p(dRect->x,dRect->y);
    return p;
}


Point Hero::get_Size()
{
    Point p(dRect->w,dRect->h);
    return p;
}

string Hero::getType()
{
    return "HERO";
}

void Hero::DecreaseHealth()
{
    health.decrease(1);
}

void Hero::CollisionImpact(GameObjects* CollidedWith)
{
    SDL_Rect collide ={(CollidedWith->get_Position()).get_X(),(CollidedWith->get_Position()).get_Y(),(CollidedWith->get_Size()).get_X(),(CollidedWith->get_Size()).get_Y()};
    SDL_Rect thisLeft={dRect->x,dRect->y,1,dRect->h};
    SDL_Rect thisRight={dRect->x+dRect->w,dRect->y,1,dRect->h};
    SDL_Rect thisbottom={dRect->x+(dRect->w/4),dRect->y+dRect->h,dRect->h/4,5};
    if (CollidedWith->getType()=="ENEMYBULLET")
    {
        if(SDL_HasIntersection( &collide,dRect))
        {
            CollidedWith->setAlive(false);
            health.decrease(1);
            sound[1]->Play();
            if (health.get_Health()==0)
            {

                Alive = false;
            }
        }
    }
    else if (CollidedWith->getType()=="BOSS")
    {
        SDL_Rect BossRect = {(CollidedWith->get_Position()).get_X(),(CollidedWith->get_Position()).get_Y(),(CollidedWith->get_Size()).get_X(),(CollidedWith->get_Size()).get_Y()-100};
         if(SDL_HasIntersection( &BossRect,dRect))
        {

            health.decrease(3);
            sound[1]->Play();

            jump = true;movey = 3;jumping = true;onground=false;movex=0;


            if (health.get_Health()<=0)
            {

                Alive = false;
            }
        }
    }
    else if(CollidedWith->getType()=="BOMB")
    {
        SDL_Rect collide ={(CollidedWith->get_Position()).get_X(),(CollidedWith->get_Position()).get_Y(),(CollidedWith->get_Size()).get_X(),(CollidedWith->get_Size()).get_Y()};

        if(SDL_HasIntersection(&collide,dRect))
            {


            CollidedWith->CollisionImpact(this);

            health.decrease(20);
            sound[1]->Play();
            if (health.get_Health()==0)
            {
                Alive = false;
            }

            CollidedWith->setAlive(false);
            }
    }
    else if (CollidedWith->getType()=="TANK")
    {
         if(SDL_HasIntersection( &collide,dRect))
        {
            health.decrease(3);
            sound[1]->Play();


            if(dRect->x>collide.x)
            {
             jump = true;movey = -30;jumping = true;onground=false;movex=50;
            }
            else
            {
                jump = true;movey = -30;jumping = true;onground=false;movex=-30;
            }

            if (health.get_Health()==0)
            {

                Alive = false;
            }
        }
    }
    else if (CollidedWith->getType()=="OBSTACLE")
    {
        if (CollidedWithId==0 || CollidedWithId == ((Obstacles*)CollidedWith)->objectId )
        {
            if (jumping && SDL_HasIntersection( &collide,&thisbottom))
            {
                CollidedWithId = ((Obstacles*)CollidedWith)->objectId;
                collided = true;
                onground = false;

            }
            else{
                 CollidedWithId = 0;
                collided =false;
                onground =true;
            }


            if (onground){
                if (SDL_HasIntersection( &collide,&thisRight))
                {
                    if(movex>0)
                    {
                        movex=0;
                    }

                    if(((this->get_Position()).get_X()+(this->get_Size()).get_X())>=collide.x)
                    {
                        int difference = ((this->get_Position()).get_X()+(this->get_Size()).get_X())-collide.x;
                        Move(-(difference+2));

                    }
                    jumping=true;
                    moved = false;

                }
                else if (SDL_HasIntersection( &collide,&thisLeft))
                {
                    if(movex<0)
                        {
                            movex=0;
                        }
                    if(((this->get_Position()).get_X()+(this->get_Size()).get_X())<=(collide.x+collide.w))
                    {
                        int difference = collide.x-((this->get_Position()).get_X()+(this->get_Size()).get_X());
                        Move(difference+2);

                    }
                    jumping=true;
                    moved = false;
                }
            }
       }
    }
}





ofstream& operator<<(ofstream& file,Hero* hero)
{
    file<<"---HERO---"<<endl;
    file<<hero->flip<<endl;
    file<<hero->moved<<endl;
    file<<hero->Alive<<endl;
    file<<hero->collided<<endl;
    file<<hero->count<<endl;
    file<<hero->shootUp<<endl;
    file<<hero->fire<<endl;
    file<<hero->jump<<endl;
    file<<hero->jumping<<endl;
    file<<hero->movey <<endl;
    file<<hero->movex<<endl;
    file<<hero->onground<<endl;
    file<<hero->ground<<endl;
    file<<hero->cs<<endl;
    file<<(hero->get_Position().get_X())<<endl;
    file<<(hero->get_Position().get_Y())<<endl;
    file<<hero->health.get_Health()<<endl;
    return file;
}


ifstream& operator>>(ifstream& file,Hero* hero)
{
    string str;
    file>>str;
    hero->flip = (SDL_RendererFlip)atoi(str.c_str());
    file>>str;
    hero->moved = atoi(str.c_str());
    file>>str;
    hero->Alive = atoi(str.c_str());
    file>>str;
    hero->collided = atoi(str.c_str());
    file>>str;
    hero->count = atoi(str.c_str());
    file>>str;
    hero->shootUp = atoi(str.c_str());
    file>>str;
    hero->fire = atoi(str.c_str());
    file>>str;
    hero->jump = atoi(str.c_str());
    file>>str;
    hero->jumping = atoi(str.c_str());
    file>>str;
    hero->movey  = atoi(str.c_str());
    file>>str;
    hero->movex = atoi(str.c_str());
    file>>str;
    hero->onground = atoi(str.c_str());
    file>>str;
    hero->ground = atoi(str.c_str());
    file>>str;
    hero->cs = atoi(str.c_str());
    file>>str;
    hero->dRect->x = atoi(str.c_str());
    file>>str;
    hero->dRect->y = atoi(str.c_str());
    file>>str;
    hero->health.set_Health( atoi(str.c_str()));
    return file;
}





Hero::~Hero()
{
    for(int i =0 ;i<2;i++)
    {
        delete sound[i];
    }
    for(int i =0 ;i<4;i++)
    {
        delete HeroStates[i];
    }
    delete dRect;
}

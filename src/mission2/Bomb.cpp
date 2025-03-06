#include "Bomb.h"

Bomb::Bomb(SDL_Window* gWindow,SDL_Renderer* grenderer,int posX,int posY,float moveX,float moveY,string description)
{
    SDL_Rect* dRect =new SDL_Rect{posX,posY,50,50};
    Image = new Sprites(gWindow,grenderer,"data\\Boss\\bomb.png",1,38,49,dRect,"Bullet",true);
    blast = new Sprites(gWindow,grenderer,"data\\Boss\\blast.png",25,1675/25,117,dRect,"Bullet",true);
    sounds[0] = new SoundEffects("data\\common\\blast.wav");
    this->x = moveX;
    this->y = moveY;
    this->description = description ;

}


string Bomb::getType()
{
    return description;
}

bool Bomb::IsAlive()
{
    return inFrame;
}




void Bomb::render(int frames)
{

        Move();
            if((get_Position()).get_Y()>=550)
            {
                if(!counter)
                    counter=10;


            }

        if(counter==1)
        {
            inFrame = false;
            sounds[0]->Play();
        }



        if(!counter)
            Image->render();
        else
        {
            blast->render();
            counter--;
        }


}



Point Bomb::get_Position()
{
    return Image->get_Position();
}



Point Bomb::get_Size()
{
    return Image->get_Size();
}


void Bomb::setAlive(bool alive)
{
    inFrame = alive;
}

bool Bomb::Inframe()
{
    return inFrame;
}



void Bomb::Move(int x,int y)
{
      if(inFrame)
        {
            if (x!=0)
                this->x = x;
            if (y!=0)
                this->y = y;

            if((Image->get_Position()).get_X()>1440 || (Image->get_Position()).get_X()<0 ||(Image->get_Position()).get_Y()>900 || (Image->get_Position()).get_X()<0)
            {
                inFrame = false;
            }
            else
            {
                Image->moveDestinationArea(this->x,this->y);

            }
        }

}
void Bomb::CollisionImpact(GameObjects* CollidedWith)
{
    if(CollidedWith->getType()=="HERO")
    {
    SDL_Rect collide ={(CollidedWith->get_Position()).get_X(),(CollidedWith->get_Position()).get_Y(),(CollidedWith->get_Size()).get_X(),(CollidedWith->get_Size()).get_Y()};
    SDL_Rect thisRect = {(Image->get_Position()).get_X(),(Image->get_Position()).get_Y(),(Image->get_Size()).get_X(),(Image->get_Size()).get_Y()};
    if(SDL_HasIntersection(&collide,&thisRect))
    {
        sounds[0]->Play();
        if(counter==0)
        {

            counter=15;
        }

    }
    }

}


Bomb::~Bomb()
{
    delete sounds[0];
    delete Image;
    delete blast;
}

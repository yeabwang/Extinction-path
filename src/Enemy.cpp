#include "Enemy.h"



Enemy::Enemy(SDL_Window* gWindow,SDL_Renderer* grenderer,int posX,List<GameObjects*>* bullets,int delay)
        {
           ///150 dRect = new SDL_Rect{1,screen.h*0.611,screen.w*0.084,screen.h*0.111};

            this->delay =delay;
            this->bullets = bullets;
            this->gWindow= gWindow;
            this->grenderer= grenderer;
            //SDL_GetDisplayBounds(0,&screen);
            dRect = new  SDL_Rect{posX,550,150,100};
            sound[0]= new SoundEffects("data\\Enemy\\fire.wav");
            sound[1]= new SoundEffects("data\\Enemy\\dead.wav");
            EnemyStates[0] = new Sprites(gWindow,grenderer,"data\\Enemy\\Images\\firing1.png",9,396/9,40,dRect,"Enemy",true);
            EnemyStates[1] = new Sprites(gWindow,grenderer,"data\\Enemy\\Images\\Running1.png",12,396/12,42,dRect,"Enemy",true);
            hero= (Hero*)((bullets->getStart())->value);

        }




Point Enemy::get_Position()
        {
            return EnemyStates[cs]->get_Position();
        }


void Enemy::Move(int x,int y)
        {
            EnemyStates[cs]->moveDestinationArea(x,y);

        }


void Enemy::setAlive(bool alive)
        {
            this->alive = alive;
        }


void Enemy::render(int frame)
        {
            if(alive){


                if(!fire(frame))
                {
                    int Hx = (hero->get_Position()).get_X();
                    int Ex = get_Position().get_X();
                    if(Ex-Hx>0)
                    {
                        flip = SDL_FLIP_NONE;
                        Move(-3);
                    }
                    else
                    {
                        flip = SDL_FLIP_HORIZONTAL;
                        Move(3);
                    }
                }
                if (count)
                    {cs=0;count--;}
                else
                    cs=1;
                EnemyStates[cs]->render(frame,flip);
            }
            else
                {
                    sound[1]->Play();
                }
        }


Enemy::~Enemy()
        {
            for(int i=0;i<2;i++)
            {
                delete EnemyStates[i] ;
            }
            for(int i=0;i<1;i++)
            {
                delete sound[i] ;
            }
            delete dRect;
        }









string Enemy::getType()
        {
            return description;
        }




Point Enemy::get_Size()
        {
            return EnemyStates[cs]->get_Size();
        }




void Enemy::CollisionImpact(GameObjects* CollidedWith)
        {
            if (CollidedWith->getType()=="HEROBULLET")
            {
                SDL_Rect collide ={(CollidedWith->get_Position()).get_X(),(CollidedWith->get_Position()).get_Y(),(CollidedWith->get_Size()).get_X(),(CollidedWith->get_Size()).get_Y()};
                SDL_Rect thisRect ={(this->get_Position()).get_X(),(this->get_Position()).get_Y(),(this->get_Size()).get_X(),(this->get_Size()).get_Y()};

                if(SDL_HasIntersection(&collide,&thisRect))
                {
                    CollidedWith->setAlive(false);
                   this->health--;
                }
                if(this->health==0)
                {
                    sound[1]->Play();

                        alive= false;
                }
            }
        }




bool Enemy::IsAlive()
        {
            return alive;
        }




bool Enemy::fire(int frame)
        {
            if(!(frame%delay))
            {

                        count=50;
                        fired=true;
                        sound[0]->Play();
                        int Hx = (hero->get_Position()).get_X();
                        int Ex = get_Position().get_X();
                        int xDiff = (hero->get_Position().get_X()-(this->get_Position().get_X()));
                        if (xDiff)
                        {
                            float slope =((hero->get_Position().get_Y())-(this->get_Position().get_Y()))/(hero->get_Position().get_X()-(this->get_Position().get_X()));
                            if(Ex-Hx>0)
                               bullets->add(new Bullet(gWindow,grenderer,(EnemyStates[cs]->get_Position()).get_X(),(EnemyStates[cs]->get_Position()).get_Y()+25,-13,-slope,"ENEMYBULLET"));
                            else
                                bullets->add(new Bullet(gWindow,grenderer,(EnemyStates[cs]->get_Position()).get_X()+dRect->w,(EnemyStates[cs]->get_Position()).get_Y()+25,13,slope,"ENEMYBULLET"));
                            return true;
                        }
                        else
                        {
                            hero->setAlive(false);
                        }

            }
            if (count==0)
            {
                fired=false;
            }
            return false;

}

ofstream& operator<<(ofstream& file,Enemy* enemy)
    {
        file<<"---ENEMY---"<<endl;
        file<<enemy->flip<<endl;
        file<<enemy->delay<<endl;
        file<<enemy->count<<endl;
        file<<enemy->fired<<endl;
        file<<enemy->alive<<endl;
        file<<enemy->movey <<endl;
        file<<enemy->movex<<endl;
        file<<enemy->cs<<endl;
        file<<(enemy->dRect->x)<<endl;
        file<<(enemy->dRect->y)<<endl;
        return file;
    }

ifstream& operator>>(ifstream& file,Enemy* enemy)
    {
        string str;
        file>>str;
        enemy->flip = (SDL_RendererFlip)atoi(str.c_str());
        file>>str;
        enemy->delay = atoi(str.c_str());
        file>>str;
        enemy->count = atoi(str.c_str());
        file>>str;
        enemy->fired = atoi(str.c_str());
        file>>str;
        enemy->alive = atoi(str.c_str());
        file>>str;
        enemy->movey  = atoi(str.c_str());
        file>>str;
        enemy->movex = atoi(str.c_str());
        file>>str;
        enemy->cs = atoi(str.c_str());
        file>>str;
        enemy->dRect->x = atoi(str.c_str());
        file>>str;
        enemy->dRect->y = atoi(str.c_str());

        return file;
    }






#include "Game.h"
#include "cstdlib"
#include "GameScreen.h"
#include "Sprites.h"
#include "Button.h"
#include "GameObjects.h"
#include "../Character.h"
#include "Obstacles.h"
#include "Hero.h"
#include "SoundEffects.h"
#include "Music.h"
#include "SplashScreen.h"
#include "Menu.h"
#include "Enemy.h"
#include "Health.h"
#include "LoadAndSave.h"
#include "Tank.h"
#include "Helicopter.h"
#include "Boss.h"
#include "ctime"
#include "PauseScreen.h"

bool jump = false;
int j_loop = 0;
int movex=0;
int movey=0;
bool jumping = false;


Game::Game(int width,int height,LoadandSave* file):WindowSize(width,height)
{
    counter=0;
    Quit = false;
    File = file;
    if (Initialize_components()==true)///initializing SDL!
    {
        SDL_Rect x;
        screen =x;
        //SDL_GetDisplayBounds(0,&x);
        cout<<x.w<<" , "<<x.h<<endl;
        x.w = 1440;
        x.h = 900;
        gWindow = SDL_CreateWindow("Extinction path",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,x.w,x.h,SDL_WINDOW_SHOWN); ///created window
        gRenederer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_PRESENTVSYNC); ///created renderer
        hero =  new  Hero(gWindow,gRenederer,&ListofObjects,this); ///created hero
        ListofObjects.add(hero);///added hero to the list
        splashScreen = new SplashScreen(&e,gWindow,gRenederer,"data\\SplashScreen\\splash1.png",x.w,x.h);///created Splash Screen
        win = new WinScreen(&e,gWindow,gRenederer,"data\\SplashScreen\\win.png",x.w,x.h);/// created win screen
        lose = new WinScreen(&e,gWindow,gRenederer,"data\\SplashScreen\\lose.png",x.w,x.h);///created lose screen
        menu = new Menu(&e,gWindow,gRenederer,"data\\SplashScreen\\menu.png",x.w,x.h);///created game screen
        gs = new GameScreen(&e,gWindow,gRenederer,"data\\Backgrounds\\main.png",x.w,x.h,(Hero*)hero,&ListofObjects);///created game screen
        pauseScreen= new PauseScreen (&e,gWindow,gRenederer,"data\\SplashScreen\\menu.png",x.w,x.h);///created pause screen
        themeMusic = new Music("theme.mp3");/// created theme music
        splashScreen->setEnabled(true); /// created Splash screen
        themeMusic->Play(); /// playing game music
        while(!Quit)
            {
                ///event loop
                while(SDL_PollEvent(&e) )
                {
                    EventController();
                    if (e.type==SDL_QUIT)
                        Quit=true;
                    if(ListofObjects.getStart()!=NULL && gs->IsEnable())
                        ((Character*)hero)->EventsController(&e);///hero's event controller
                }
                /// clear renderer
                SDL_SetRenderDrawColor(gRenederer,255,255,255,255);
                SDL_RenderClear(gRenederer);
                ///looking for enabled window
                if(win->IsEnable())
                {
                    win->Render();
                }
                else if(lose->IsEnable())
                {
                    lose->Render();
                }
                else if (pauseScreen->IsEnable())
                {
                   pauseScreen->Render();
                }
                else if(menu->IsEnable())
                {
                    menu->Render();
                }
                else if ((gs->IsEnable()))
                {
                    gs->Render();
                    GameLogic();
                    ObjectsManager();
                    counter+= 1;
                    if (counter>=1000)
                        counter = 0;
                }
                else if(splashScreen->IsEnable())
                {
                    splashScreen->Render();
                }
                SDL_RenderPresent(gRenederer);
            }
        /// saving the game if user quits.
        SaveGame();
    }
    else
    {
        cout<<"Game Cannot be started!\n"<<endl;
    }
}


void Game::SaveGame()
{
    LoadAndSave Save(this,gs,gWindow,gRenederer);
    Save.Save(&ListofObjects,"data//files//Saved.txt");
}


void Game::LoadGame()
{
    LoadAndSave file(this,gs,gWindow,gRenederer);
    file.Load(&ListofObjects,"data//files//Saved.txt");
}



ofstream& operator<<(ofstream& file,Game* game)
    {
        file<<"---GAME---"<<endl;
        file<<game->EnemyKillCount<<endl;
        file<<game->OnScreenEnemies<<endl;
        file<<game->TankKilled<<endl;
        file<<game->TankGenerated<<endl;
        file<<game->HelicopterKilled<<endl;
        file<<game->HelicopterGenerated<<endl;
        file<<game->FinalEnemiesGenerated<<endl;
        file<<game->BossGenerated<<endl;
        file<<game->Current_Stage<<endl;
        return file;
    }

ifstream& operator>>(ifstream& file,Game* game)
    {
        string str;
        file>>str;
        game->EnemyKillCount = atoi(str.c_str());
        file>>str;
        game->OnScreenEnemies = atoi(str.c_str());
        file>>str;
        game->TankKilled = atoi(str.c_str());
        file>>str;
        game->TankGenerated= atoi(str.c_str());
        file>>str;
        game->HelicopterKilled= atoi(str.c_str());
        file>>str;
        game->HelicopterGenerated= atoi(str.c_str());
        file>>str;
        game->FinalEnemiesGenerated = atoi(str.c_str());
        file>>str;
        game->BossGenerated = atoi(str.c_str());
        file>>str;
        game->Current_Stage = atoi(str.c_str());
        return file;
    }





void Game::GameLogic()
{


    if (EnemyKillCount <= 12 && Current_Stage == 1000)
    {
        if(OnScreenEnemies<2)
        {
            if(rand()%3==0)
            {
                ListofObjects.add(new Obstacles(gWindow,gRenederer,1,"data\\Obstacles\\armyTruck.png",screen.w*1.111,screen.h*0.555,138,71,screen.w*0.173,screen.h*0.166,this->gs));
                cout<<screen.w*1.111<<" "<<screen.h*0.555<<endl;
            }
            ListofObjects.add(new Enemy(gWindow,gRenederer,1840,&ListofObjects,150));
            ListofObjects.add(new Enemy(gWindow,gRenederer,2040,&ListofObjects,100));
            OnScreenEnemies+=2;
        }
    }
    else if(Current_Stage == 1000)
    {
        free = false;
    }
    else if (!TankGenerated && Current_Stage == 2000)
    {
        ListofObjects.add(new Tank(gWindow,gRenederer,1250,500,&ListofObjects));
        TankGenerated = true;
    }
     else if(TankKilled && Current_Stage == 2000)
    {
        free = false;
    }
    else if (TankKilled && !HelicopterGenerated && Current_Stage == 3000)
    {
       ListofObjects.add(new Helicopter(gWindow,gRenederer,1440,50,&ListofObjects));
       HelicopterGenerated = true;
    }
     else if(HelicopterKilled && Current_Stage == 3000)
    {
        free = false;
    }
    else if (HelicopterKilled && !FinalEnemiesGenerated )
    {
            ListofObjects.add(new Enemy(gWindow,gRenederer,1840,&ListofObjects,200));
            ListofObjects.add(new Enemy(gWindow,gRenederer,2040,&ListofObjects,100));
            ListofObjects.add(new Enemy(gWindow,gRenederer,2300,&ListofObjects,150));
            ListofObjects.add(new Enemy(gWindow,gRenederer,2540,&ListofObjects,100));
            ListofObjects.add(new Enemy(gWindow,gRenederer,2740,&ListofObjects,300));
            ListofObjects.add(new Enemy(gWindow,gRenederer,2840,&ListofObjects,200));
            FinalEnemiesGenerated = true;
    }
    else if(FinalEnemiesGenerated && EnemyKillCount>=18 && !BossGenerated && Current_Stage == 4000)
    {
        ListofObjects.add(new Boss(gWindow,gRenederer,10,10,&ListofObjects));
        BossGenerated = true;
    }
}

void Game::ObjectsManager()
{
    Node<GameObjects*>* temNode = ListofObjects.getStart();
    ListofObjects.HasTank = false;
    while(temNode)
    {
        GameObjects* obj= temNode->value;
        if ((obj)->IsAlive())
        {
            if(obj->getType()=="TANK")
            {
                ListofObjects.HasTank = true;
            }


            Node<GameObjects*>* tNode = ListofObjects.getStart();
            while(tNode)
            {
                (obj)->CollisionImpact(tNode->value);
                tNode = tNode->next;
            }
            (obj)->render(counter);
            temNode= temNode->next;
        }
        else
        {
            if(obj->getType()=="ENEMY")
            {

                EnemyKillCount+=1;
                OnScreenEnemies-=1;

            }
            else if(obj->getType()=="TANK")
            {
                TankKilled = true;
            }
            else if(obj->getType()=="HELICOPTER")
            {
                HelicopterKilled = true;
            }
            else if(obj->getType()=="HELICOPTER")
            {
                HelicopterKilled = true;
            }
            if(obj->getType()=="BOSS")
            {
                EnemyKillCount = 0;
                OnScreenEnemies = 0;
                TankKilled = false;
                TankGenerated = false;
                HelicopterKilled = false;
                HelicopterGenerated = false;
                FinalEnemiesGenerated = false;
                Current_Stage = 1000;
                BossGenerated = false;
                win->setEnabled(true);
                 gs->setEnabled(false);
                ListofObjects.freeMemory();
                temNode = NULL;
            }
            else if(obj->getType()=="HERO")
                {
                    gs->setEnabled(false);
                    lose->setEnabled(true);
                     EnemyKillCount = 0;
                    OnScreenEnemies = 0;
                    TankKilled = false;
                    TankGenerated = false;
                    HelicopterKilled = false;
                    HelicopterGenerated = false;
                    FinalEnemiesGenerated = false;
                    Current_Stage = 1000;
                    BossGenerated = false;
                    lose->setEnabled(true);
                     gs->setEnabled(false);
                    ListofObjects.freeMemory();
                    temNode = NULL;
                }
            else{
             Node<GameObjects*>* toBeDeleted = temNode;

             if(temNode->previous==NULL)
             {
                 temNode= temNode->next;
                 delete ListofObjects.pop(0);
             }
             else if(temNode->next==NULL)
             {
                  temNode= temNode->next;
                  GameObjects* g=ListofObjects.pop();
                 delete g ;
             }
             else
             {
                (temNode->next)->previous = temNode->previous;
                (temNode->previous)->next = temNode->next;
                 delete obj;
                  temNode= temNode->next;
                  delete toBeDeleted;
             }
            }
        }
    }
}


bool Game::EventController()
{
    if (splashScreen->IsEnable())
                    {

                        if(splashScreen->getButtonPresed()==1)
                        {
                            splashScreen->setEnabled(false);
                            menu->setEnabled(true);
                        }

                    }
                    else if(menu->IsEnable())
                    {
                        if(menu->getButtonPresed()==0)
                        {
                            if(win->IsEnable())
                                win->setEnabled(false);
                            if(lose->IsEnable())
                                lose->setEnabled(false);

                            hero->setAlive(true);
                            gs->setEnabled(true);
                            menu->setEnabled(false);

                        }
                        else if(menu->getButtonPresed()==1)
                        {
                            LoadGame();
                            gs->setEnabled(true);
                            menu->setEnabled(false);
                        }
                        else if(menu->getButtonPresed()==2)
                        {
                            Quit=false;
                            SDL_Quit();
                        }

                    }
                    else if(gs->IsEnable())
                    {
                        if(gs->getButtonPresed()==0)
                        {
                            pauseScreen->setEnabled(true);
                            gs->setEnabled(false);
                        }
                    }
                    else if(pauseScreen->IsEnable())
                    {
                        if(pauseScreen->getButtonPresed()==0)
                        {
                            pauseScreen->setEnabled(false);
                            gs->setEnabled(true);
                        }
                        else if(pauseScreen->getButtonPresed()==1)
                        {
                            Quit =true;
                            SDL_Quit();
                        }
                    }
                    else if(win->IsEnable())
                    {
                        if(win->getButtonPresed())
                        {

                            win->setEnabled(false);
                            menu->setEnabled(true);
                        }
                    }
                    else if(lose->IsEnable())
                    {
                        if(lose->getButtonPresed())
                        {
                            lose->setEnabled(false);
                            menu->setEnabled(true);
                        }
                    }
                    return true;

}





Game::~Game()
{

}

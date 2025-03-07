#include "LoadAndSave.h"


LoadAndSave::LoadAndSave(Game* game,GameScreen* gamescreen,SDL_Window* window,SDL_Renderer* renderer)
{
    this->gamescreen = gamescreen;
    this->game = game;
    gRenderer = renderer;
    gWindow = window;
}

bool LoadAndSave::Save(List<GameObjects*>* list, string path)
{

    ofstream file(path.c_str());
    file<<game;
    Node<GameObjects*>* tempNode = list->getStart();
    while(tempNode)
    {
        GameObjects* obj = tempNode->value;
        if(obj->getType()=="HERO")
        {
            file<<((Hero*) obj);
        }
        else if(obj->getType()=="ENEMY")
        {
             file<<((Enemy*) obj);
        }
        else if(obj->getType()=="TANK")
        {
             file<<((Tank*) obj);
        }
        else if(obj->getType()=="HELICOPTER")
        {
             file<<((Helicopter*) obj);
        }
        else if(obj->getType()=="BOSS")
        {
             file<<((Boss*) obj);
        }
        else if(obj->getType()=="OBSTACLE")
        {
             file<<((Obstacles*) obj);
        }

        tempNode= tempNode->next;
    }
    return true;
}

bool LoadAndSave::Load(List<GameObjects*>* list,string path)
{

    string line="";
    ifstream file(path.c_str());
    while(getline(file,line))
    {
        if(line=="---GAME---")
        {
            file>>game;
        }
        else if(line=="---HERO---")
        {
            file>>(Hero*)(list->getStart())->value;
        }
        else if(line=="---ENEMY---")
        {

            GameObjects* enemy = new Enemy(gWindow,gRenderer,1000,list,400);
            file>>((Enemy*) enemy);
            list->add(enemy);
        }
        else if(line=="---TANK---")
        {

            GameObjects* tank = new Tank(gWindow,gRenderer,1250,500,list);
            file>>((Tank*) tank);
            list->add(tank);
        }
        else if(line=="---HELICOPTER---")
        {
            GameObjects* helicopter = new Helicopter(gWindow,gRenderer,100,50,list);
            file>>((Helicopter*) helicopter);
            list->add(helicopter);
        }
        else if(line=="---BOSS---")
        {
            GameObjects* boss = new Boss(gWindow,gRenderer,10,10,list);
            file>>((Boss*) boss);
            list->add(boss);
        }
        else if(line=="---OBSTACLE---")
        {
            GameObjects* obs = new Obstacles(gWindow,gRenderer,1,"data\\Obstacles\\armyTruck.png",1600,500,138,71,250,150,gamescreen);
            file>>((Obstacles*) obs);
            list->add(obs);
        }

    }

return true;

}



LoadAndSave::~LoadAndSave()
{

}

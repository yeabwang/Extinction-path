
#include "Menu.h"

 Menu::Menu(SDL_Event* e,SDL_Window* gWindow,SDL_Renderer* gRenderer,string Path,int width, int height)
{
    this->Background = new Sprites(gWindow,gRenderer,Path,1,0,0,1598,900,width,height,"");
    this->Buttons[0]= new Button(gRenderer,gWindow,"Data\\Buttons\\MainMenu\\start0.png",{500,350},{422,100});//250
    this->Buttons[1]= new Button(gRenderer,gWindow,"Data\\Buttons\\MainMenu\\load0.png",{500,460},{422,100});//360
    this->Buttons[2]= new Button(gRenderer,gWindow,"Data\\Buttons\\MainMenu\\quit0.png",{500,570},{422,100});//470
    this->e = e;
    Enable = false;
}
bool Menu:: IsEnable()
{
    return Enable;

}
void Menu::setEnabled(bool e)
{
    Enable = e;

}
int Menu::getButtonPresed()
{
    int ButtonCount = -1;

    if (Buttons[0]->IsClicked(e))
    {
        ButtonCount = 0;
    }
    else if (Buttons[1]->IsClicked(e))
    {
        ButtonCount = 1;
    }
    else if (Buttons[2]->IsClicked(e))
    {
        ButtonCount = 2;
    }
    return ButtonCount;

}



void Menu::Render()
{

    this->Background->render();
    this->Buttons[0]->Render();
    this->Buttons[1]->Render();
    this->Buttons[2]->Render();


}


Point Menu::getSize()
{
    return Background->get_Size();
}

Menu::~Menu()
{
    delete Background;
    for(int i = 0; i<3; i++)
        delete Buttons[i];

}

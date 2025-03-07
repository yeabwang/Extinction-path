#include "PauseScreen.h"

PauseScreen::PauseScreen(SDL_Event* e,SDL_Window* gWindow,SDL_Renderer* gRenderer,string Path,int width, int height)
{
    this->Background = new Sprites(gWindow,gRenderer,Path,1,0,0,2500,1000,width,height,"");
    this->Buttons[0]= new Button(gRenderer,gWindow,"Data\\Buttons\\Pause\\resume0.png",{500,350},{422,100});
    this->Buttons[1]= new Button(gRenderer,gWindow,"Data\\Buttons\\Pause\\quit0.png",{500,460},{422,100});
    this->e = e;
    Enable = false;
}
bool PauseScreen:: IsEnable()
{
    return Enable;

}
void PauseScreen::setEnabled(bool e)
{
    Enable = e;

}
int PauseScreen::getButtonPresed()
{
    int ButtonCount = -1;

    if (Buttons[0]->IsClicked(e))
    {
        ButtonCount = 0;


    }
    if (Buttons[1]->IsClicked(e))
    {
        ButtonCount = 1;


    }
    return ButtonCount;

}




void PauseScreen::Render()
{

    this->Background->render();
    this->Buttons[0]->Render();
    this->Buttons[1]->Render();
}




Point PauseScreen::getSize()
{
    return Background->get_Size();
}



PauseScreen:: ~PauseScreen()
{
    for(int i=0;i<2;i++)
        delete Buttons[i];
    delete Background;

}

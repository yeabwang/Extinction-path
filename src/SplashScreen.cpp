#include "SplashScreen.h"

SplashScreen::SplashScreen(SDL_Event* e,SDL_Window* gWindow,SDL_Renderer* gRenderer,string Path,int width, int height)
{
    this->Background = new Sprites(gWindow,gRenderer,Path,1,0,0,1440,900,width,height,"");
    this->e = e;
    Enable = false;

}

bool SplashScreen:: IsEnable()
{


    return Enable;
}


void SplashScreen:: setEnabled(bool e)
{
    Enable = e;
}

int SplashScreen::getButtonPresed()
{
    if (e->type == SDL_KEYDOWN && e->key.keysym.sym ==SDLK_RETURN)
    {
        return 1;
    }
    return 0;


}
void SplashScreen::Render()
{
    this->Background->render();
}
Point SplashScreen::getSize()
{
    Background->get_Size();

}
SplashScreen::~SplashScreen()
{

    delete Background;
}

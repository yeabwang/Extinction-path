#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "iostream"
#include "Game.h"
#include "ctime"
#include "time.h"
#include "cstdlib"
using namespace std;

bool Initialize_components();

int main(int argc,char* argv[])
{
    srand(time(NULL));
    Game game(1440,900,NULL);
    return 0;
}

bool Initialize_components()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0)
        return false;
    else{
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                cout<<"SDL_image could not initialize! SDL_image Error:"<< IMG_GetError()<<endl ;
                return false;
            }
            //Initialize SDL_mixer
            if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            {
                cout<< "SDL_mixer could not initialize! SDL_mixer Error: %s\n"<<Mix_GetError()<<endl;
                return false;
            }
            else
                return true;

    }
}

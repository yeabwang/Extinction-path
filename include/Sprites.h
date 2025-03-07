#ifndef SPRITES_H
#define SPRITES_H
#include "SDL.h"
#include "SDL_image.h"
#include "Point.h"



class Sprites
{
    public:

        Sprites(SDL_Window* gWindow,SDL_Renderer* gRenderer,string Path,int NoS,int posX,int posY,int sWidth, int sHeight,int width, int height,string description,bool colorKey=false,int df=0);
        Sprites(SDL_Window* gWindow,SDL_Renderer* gRenderer,string Path,int NoS,int sWidth, int sHeight,SDL_Rect* externalDestination,string description,bool colorKey=false,int df=0);

        /**
        sWidth: source's width.
        sHeight: source's height.
        width: Window's width.
        height: Window's height.
        **/

        void moveDestinationArea(int x=0,int y=0);///Moves Destination rectangle (Moves Image on screen)

        void moveSpriteArea(int x=0); ///Moves current sprite

        void render(int  Frame=0,SDL_RendererFlip flip=SDL_FLIP_NONE); /// renders animated sprite
        Point get_Position();/// returns current position of sprite
        Point get_Size();///returns size of sprite
        int get_NOS();/// returns number of clips
        void set_CS(int n);///returns current selected clip
        virtual ~Sprites();
        Sprites()= delete;///we don't need default constructor
        Sprites(const & Sprites)= delete;///we don't need default constructor
        Sprites& operator=(const& Sprites)= delete;///we don't need default constructor

    protected:
        int cs=0; ///index of currentSprite
        int NOS;  ///Number of Sprites in this texture
        SDL_Texture* Texture; ///Texture of Image
        Point Size;///size of the sprite
        Point position;///position of sprite renderer
        SDL_Window* gWindow;///Main Window
        SDL_Renderer* gRenderer;///Main Renderer
        SDL_Rect** sRect;///Source Rectangle
        SDL_Rect* dRect; ///Destination Rectangle
        string ClassDescription; /// description or name


};

#endif // SPRITES_H

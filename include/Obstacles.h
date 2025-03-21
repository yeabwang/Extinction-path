#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "GameObjects.h"
#include "SoundEffects.h"
#include "Sprites.h"
#include "GameScreen.h"
#include <stdio.h> 

class Obstacles : public GameObjects {
public:
    Obstacles(SDL_Window* gWindow, SDL_Renderer* grenderer, int NOS, const char* path, int posX, int posY, int sWidth, int sHeight, int width, int height, GameScreen* gs);
    const char* getType(); 
    bool IsAlive();
    void render(int frames = 0);
    void setAlive(bool alive);
    Point get_Position();
    Point get_Size();
    int objectId;
    void Move(int x = 0, int y = 0);
    void CollisionImpact(GameObjects* CollidedWith);
    virtual ~Obstacles();
    void setAlive();
    static int ID;

    friend void SaveObstaclesToFile(FILE* file, Obstacles* obstacles);
    friend void LoadObstaclesFromFile(FILE* file, Obstacles* obstacles);

private:
    SoundEffects* sounds[1];
    Sprites* sprite[2];
    int counter;
    bool inFrame;
    int cs;
    GameScreen* gamescreen;
    SDL_Rect* dRect;
};

#endif // OBSTACLES_H
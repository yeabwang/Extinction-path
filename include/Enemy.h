#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Bullet.h"
#include "SoundEffects.h"
#include "List.h"
#include "Hero.h"
#include <cstdio> 

class Enemy : public Character
{
public:
    Enemy(SDL_Window* gWindow, SDL_Renderer* grenderer, int posX, List<GameObjects*>* bullets, int delay);
    void EventsController(SDL_Event* e) {} // No implementation
    Point get_Position();
    void Move(int x = 0, int y = 0);
    void setAlive(bool alive);
    void render(int frame = 0);
    bool fire(int frame);
    virtual ~Enemy();
    const char* getType();
    Point get_Size();
    void CollisionImpact(GameObjects* CollidedWith);
    bool IsAlive();

    Enemy() = delete;
    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;

    friend void SaveEnemyToFile(FILE* file, Enemy* enemy);
    friend void LoadEnemyFromFile(FILE* file, Enemy* enemy);

private:
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Rect screen;
    Hero* hero;
    int delay;
    int count = 0;
    bool fired = false;
    bool alive = true;
    SDL_Window* gWindow;
    SDL_Renderer* grenderer;
    List<GameObjects*>* bullets; // Enemy bullet list
    SDL_Rect* dRect = NULL;
    int movey = 0;
    int movex = 0;
    int cs = 0;
    const char* description = "ENEMY";
    SoundEffects* sound[2];
    Sprites* EnemyStates[2]{ NULL };
    int health = 5;
};

#endif // ENEMY_H
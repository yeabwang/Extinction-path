#ifndef HERO_H
#define HERO_H

#include "Sprites.h"
#include "Bullet.h"
#include "List.h"
#include "Character.h"
#include "SoundEffects.h"
#include "Obstacles.h"
#include <cstdio> 

class Game;

class Hero : public Character
{
    SDL_Rect screen;
    Health health; // Health object
    SDL_RendererFlip flip; // Stores flipping state
    bool moved; // Tracks if the object is moved
    bool Alive;
    bool collided; // For checking top collision
    int count; // For sprite changing purposes
    bool shootUp; // For sprite changing purposes
    bool fire;
    SDL_Window* gWindow; // Main window
    SDL_Renderer* grenderer; // Main renderer
    List<GameObjects*>* bullets; // List of bullets fired by the hero
    bool jump; // True when Up button is pressed
    bool jumping; // True during the entire jump
    int movey;
    int movex;
    bool onground; // True if the object is on the ground
    int ground; // Ground's y-coordinate
    int cs; // Current sprite index
    SoundEffects* sound[2]; // Sound effects
    Sprites* HeroStates[4]; // Hero's sprite states
    bool running;
    int CollidedWithId;
    SDL_Rect* dRect;
    Game* gm_ptr; // Pointer to the game object

    Hero() = delete;
    Hero(const Hero&) = delete;
    Hero& operator=(const Hero&) = delete;

public:
    Hero(SDL_Window* gWindow, SDL_Renderer* grenderer, List<GameObjects*>* lst, Game* gm_ptr);
    bool IsMoved();
    void setAlive(bool alive);
    bool IsAlive();
    void render(int frames);
    void Move(int x = 0, int y = 0);
    void EventsController(SDL_Event* e);
    Point get_Position();
    Point get_Size();
    const char* getType();
    void DecreaseHealth(); // Decreases health by 1
    void CollisionImpact(GameObjects* CollidedWith);
    virtual ~Hero();
    
    // Getter for gm_ptr
    Game* getGamePtr() { return gm_ptr; } // Return gm_ptr

    friend void SaveHeroToFile(FILE* file, Hero* hero);
    friend void LoadHeroFromFile(FILE* file, Hero* hero);

    private:
    int meleeCooldown;
};

#endif // HERO_H
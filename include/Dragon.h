#ifndef DRAGON_H
#define DRAGON_H

#include "Character.h"
#include "List.h"
#include "SoundEffects.h"
#include "Bullet.h"
#include "terrain.h"
#include "Hero.h"
#include <vector>
#include <SDL.h>

enum DragonAttacks { LASER, ROCKETS, NONE };
enum Locations { TL, TL2, OUT };

class DragonTailSegment {
public:
    Sprites* sprite;
    SDL_Rect* rect;
    double angle;
    float velX, velY, aVel;
    float accelX, accelY, aAccel;
    DragonTailSegment* previous;
    DragonTailSegment* next;
    Sprites* connector;

    DragonTailSegment(SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* path, int x, int y);
    ~DragonTailSegment();
    void update(const SDL_Rect& headRect, DragonTailSegment* prev = nullptr);
    void render();
    SDL_Point getMidUpperPoint();
    SDL_Point getMidLowerPoint();
};

class NavPath {
public:
    bool active;
    float relPos;
    float speed;
    float sineAmplitude;
    float sineCurveAmount;
    SDL_Point start, end, bezierControl;
    bool easeIn, easeOut;
    enum Mode { LINEAR, SINE, BEZIER } mode;

    NavPath();
    void initLinear(int startX, int startY, int endX, int endY, float speed, bool easeIn, bool easeOut);
    void initSine(int startX, int startY, int endX, int endY, float amp, float curve, float speed, bool easeIn, bool easeOut);
    void initBezier(int startX, int startY, int endX, int endY, int ctrlX, int ctrlY, float speed, bool easeIn, bool easeOut);
    void traverse();
    SDL_Point update();
    bool isBusy() { return active; }
};

class NavGraph {
public:
    NavPath tlEnter, tlExit, tl2Exit, followPath;
    NavPath* active;
    Locations location;
    Point* target; // For following the hero

    NavGraph(int startX, int startY, Point* heroPos);
    void moveTo(Locations loc);
    void follow(Point heroPos);
    SDL_Point update();
    bool isBusy() { return active->isBusy(); }
};

class Dragon : public Character {
public:
    Dragon(SDL_Window* gWindow, SDL_Renderer* gRenderer, int posX, int posY, List<GameObjects*>* bullets, terrain* ter, Hero* hero);
    virtual ~Dragon() override; // Ensure proper virtual destructor syntax
    const char* getType() override;
    void render(int frame = 0) override;
    bool IsAlive() override;
    void CollisionImpact(GameObjects* CollidedWith) override;
    Point get_Position() override;
    Point get_Size() override;
    void EventsController(SDL_Event* e) override;
    void setAlive(bool alive) override;
    void Move(int x = 0, int y = 0) override;

private:
    void updateLaser(int frame);
    void fireRockets(int frame);
    void updateTail(int frame);
    void launchAttack(DragonAttacks attack);

    Health health;
    bool alive;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    List<GameObjects*>* bullets;
    terrain* ter;
    Hero* hero;
    Point heroPos; // Added for persistent hero position
    // Head
    Sprites* headSprite;
    SDL_Rect* headRect;
    double headAngle;
    float idleAngle;
    float idleOffsetX, idleOffsetY;
    float idleOffsetMulX, idleOffsetMulY;
    // Tail
    std::vector<DragonTailSegment*> tailSegments;
    static const int NUM_TAIL_SEGMENTS = 6;
    float tailWiggleAmplitude;
    float tailWiggleSpeed;
    int tailWiggleTimer;
    // Laser
    bool laserOn;
    int laserCounter;
    int laserStage;
    Sprites* laserSprite;
    SDL_Rect* laserRect;
    Sprites* laserFlare;
    SDL_Rect* laserFlareRect;
    float laserFlareAngle;
    // Rockets
    std::vector<Bullet*> missiles;
    static const int NUM_ROCKETS = 30;
    int rocketCounter;
    bool spawnRocketDrops;
    // Navigation
    NavGraph* navigator;
    Locations currentLocation;
    DragonAttacks currentAttack;
    int attackStage;
    // Sound
    SoundEffects* blastSound;
    SoundEffects* laserSound;
};

#endif
#include "Boss.h"
#include <cstdio> 

Boss::Boss(SDL_Window* gWindow, SDL_Renderer* gRenderer, int posX, int posY, List<GameObjects*>* bullets)
    : health(150, gWindow, gRenderer, posX, posY - 20)
{
    Alive = true;
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    this->bullets = bullets;
    dRect = new SDL_Rect{ posX, posY, 1200, 400 };
    sprite[0] = new Sprites(gWindow, gRenderer, "data\\Boss\\Boss.png", 12, 3264 / 12, 146, dRect, "", true);
    sprite[1] = new Sprites(gWindow, gRenderer, "data\\tanks\\Image\\blast1.png", 7, 945 / 7, 176, dRect, "", true);
    sounds[0] = new SoundEffects("data\\common\\blast.wav");
}

Boss::~Boss()
{
    for (int i = 0; i < 2; i++)
        delete sprite[i];
    for (int i = 0; i < 1; i++)
        delete sounds[i];
}

const char* Boss::getType()
{
    return "BOSS";
}

void Boss::render(int frames)
{
    if (frames % 100 == 0 && moving)
    {
        moveX += 1.99;
    }

    if ((dRect->x) < -100 && moving)
    {
        moving = false;
        moveX = -2;
    }
    else if ((dRect->x) + (dRect->w) > 1500 && !moving)
    {
        moving = true;
        moveX = 0;
        bulletsCount = 0;
    }

    Move(-moveX, 0);
    health.display(dRect->x, dRect->y);

    if (health.get_Health() <= 0)
    {
        Alive = false;
    }

    sprite[cs]->render(frames);
    fire(frames);
}

bool Boss::IsAlive()
{
    return Alive;
}

void Boss::CollisionImpact(GameObjects* CollidedWith)
{
    if (strcmp(CollidedWith->getType(), "HEROBULLET") == 0)
    {
        SDL_Rect collide = { (CollidedWith->get_Position()).get_X(), (CollidedWith->get_Position()).get_Y(), (CollidedWith->get_Size()).get_X(), (CollidedWith->get_Size()).get_Y() };
        SDL_Rect thisRect = { dRect->x, dRect->y, dRect->w, dRect->h - 50 };
        if (SDL_HasIntersection(&collide, &thisRect))
        {
            CollidedWith->setAlive(false);
            health.decrease(1);
        }
    }
}

Point Boss::get_Position()
{
    return sprite[cs]->get_Position();
}

Point Boss::get_Size()
{
    return sprite[cs]->get_Size();
}

void Boss::EventsController(SDL_Event* e)
{
    // Events are not used in this class
}

void Boss::Move(int x, int y)
{
    sprite[cs]->moveDestinationArea(x, y);
}

void Boss::setAlive(bool alive)
{
    this->Alive = alive;
}

void Boss::fire(int frame)
{
    if (frame % 200 == 0)
    {
        if (left)
        {
            bullets->add(new Bomb(gWindow, gRenderer, dRect->x + 100, dRect->y + 250, 0, 5, "BOMB"));
            left = false;
        }
        else
        {
            left = true;
            bullets->add(new Bomb(gWindow, gRenderer, dRect->x + 1000, dRect->y + 250, 0, 5, "BOMB"));
        }

        bullets->add(new Bomb(gWindow, gRenderer, dRect->x + dRect->w / 2, dRect->y + 250, 0, 5, "BOMB"));
    }

    if (frame % 100 == 0)
    {
        bullets->add(new Bullet(gWindow, gRenderer, dRect->x + 390, dRect->y + 22, 0, 5, "ENEMYBULLET"));
        bullets->add(new Bullet(gWindow, gRenderer, dRect->x + 790, dRect->y + 22, 0, 5, "ENEMYBULLET"));
    }
}

void SaveBossToFile(FILE* file, Boss* boss)
{
    fprintf(file, "---BOSS---\n");
    fprintf(file, "%d\n", boss->left ? 1 : 0); 
    fprintf(file, "%d\n", boss->blasted ? 1 : 0); 
    fprintf(file, "%d\n", boss->counter);
    fprintf(file, "%d\n", boss->CounterOfBlast);
    fprintf(file, "%d\n", boss->cs);
    fprintf(file, "%d\n", boss->bulletsCount);
    fprintf(file, "%d\n", boss->moving ? 1 : 0); 
    fprintf(file, "%d\n", boss->moveX);
    fprintf(file, "%d\n", boss->Alive ? 1 : 0); 
    fprintf(file, "%d\n", boss->dRect->x);
    fprintf(file, "%d\n", boss->dRect->y);
    fprintf(file, "%d\n", boss->health.get_Health());
}

void LoadBossFromFile(FILE* file, Boss* boss)
{
    int tempInt; // Temporary variable to read int values
    fscanf(file, "%*s"); 

    fscanf(file, "%d", &tempInt); boss->left = (tempInt != 0); 
    fscanf(file, "%d", &tempInt); boss->blasted = (tempInt != 0); 
    fscanf(file, "%d", &boss->counter);
    fscanf(file, "%d", &boss->CounterOfBlast);
    fscanf(file, "%d", &boss->cs);
    fscanf(file, "%d", &boss->bulletsCount);
    fscanf(file, "%d", &tempInt); boss->moving = (tempInt != 0); 
    fscanf(file, "%d", &boss->moveX);
    fscanf(file, "%d", &tempInt); boss->Alive = (tempInt != 0); 
    fscanf(file, "%d", &boss->dRect->x);
    fscanf(file, "%d", &boss->dRect->y);
    fscanf(file, "%d", &tempInt); boss->health.set_Health(tempInt); // Set health value
}
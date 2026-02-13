#include "Obstacles.h"

int Obstacles::ID = 0;

Obstacles::Obstacles(SDL_Window* gWindow, SDL_Renderer* grenderer, int NOS, const char* path, int posX, int posY, int sWidth, int sHeight, int width, int height, GameScreen* gs) {
    ID += 1;
    objectId = ID;
    sounds[0] = new SoundEffects("data\\common\\blast.wav");
    dRect = new SDL_Rect{ posX, posY, width, height };
    sprite[0] = new Sprites(gWindow, grenderer, path, NOS, sWidth, sHeight, dRect, "obstacle", true);
    sprite[1] = new Sprites(gWindow, grenderer, "data\\tanks\\Image\\blast1.png", 7, 945 / 7, 176, dRect, "", true);
    gamescreen = gs;
    counter = 0;
    inFrame = true;
    cs = 0;
}

const char* Obstacles::getType() {
    return "OBSTACLE"; 
}

bool Obstacles::IsAlive() {
    return inFrame;
}

void Obstacles::render(int frames) {
    if (gamescreen->IsMoved()) {
        Move(-3);
    }

    if (counter > 0) {
        if (counter == 1)
            inFrame = false;
        counter -= 1;
    }

    sprite[cs]->render(frames);
    if (get_Position().get_X() + get_Size().get_X() < 0)
        inFrame = false;
}

void Obstacles::setAlive(bool alive) {
    this->inFrame = alive;
}

Point Obstacles::get_Position() {
    Point p(dRect->x, dRect->y);
    return p;
}

Point Obstacles::get_Size() {
    Point p(dRect->w, dRect->h);
    return p;
}

void Obstacles::Move(int x, int y) {
    sprite[cs]->moveDestinationArea(x, y);
}

void Obstacles::CollisionImpact(GameObjects* CollidedWith) {
    if (strcmp(CollidedWith->getType(), "TANK") == 0) { 
        SDL_Rect collide = { (CollidedWith->get_Position()).get_X(), (CollidedWith->get_Position()).get_Y(), (CollidedWith->get_Size()).get_X(), (CollidedWith->get_Size()).get_Y() };
        SDL_Rect* dRect = new SDL_Rect{ get_Position().get_X(), get_Position().get_Y(), get_Size().get_X(), get_Size().get_Y() };
        if (SDL_HasIntersection(&collide, dRect)) {
            sounds[0]->Play();
            if (counter == 0) {
                counter = 40;
            }
            cs = 1;
        }
        delete dRect;
    }
}

Obstacles::~Obstacles() {
    for (int i = 0; i < 2; i++)
        delete sprite[i];
    delete dRect;
}

void Obstacles::setAlive() {
    inFrame = true;
}

void SaveObstaclesToFile(FILE* file, Obstacles* obstacles) {
    fprintf(file, "---OBSTACLE---\n");
    fprintf(file, "%d\n", obstacles->inFrame ? 1 : 0); 
    fprintf(file, "%d\n", obstacles->cs);
    fprintf(file, "%d\n", obstacles->counter);
    fprintf(file, "%d\n", obstacles->dRect->y);
    fprintf(file, "%d\n", obstacles->dRect->x);
}

void LoadObstaclesFromFile(FILE* file, Obstacles* obstacles) {
    int temp;
    fscanf(file, "%*s"); 
    fscanf(file, "%d", &temp); obstacles->inFrame = (temp != 0); 
    fscanf(file, "%d", &obstacles->cs);
    fscanf(file, "%d", &obstacles->counter);
    fscanf(file, "%d", &obstacles->dRect->y);
    fscanf(file, "%d", &obstacles->dRect->x);
}
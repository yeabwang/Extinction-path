#include "Tank.h"

Tank::Tank(SDL_Window* gWindow, SDL_Renderer* gRenderer, int posX, int posY, List<GameObjects*>* bullets)
    : health(100, gWindow, gRenderer, posX, posY - 20) {
    Alive = true;
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    this->bullets = bullets;
    dRect = new SDL_Rect{ posX, posY, 250, 150 };
    sprite[0] = new Sprites(gWindow, gRenderer, "data\\tanks\\Image\\Tank.png", 20, 1320 / 20, 56, dRect, "", true);
    sprite[1] = new Sprites(gWindow, gRenderer, "data\\tanks\\Image\\blast1.png", 7, 945 / 7, 176, dRect, "", true);
    sounds[0] = new SoundEffects("data\\common\\blast.wav");
    sounds[1] = NULL; // Initialize the second sound effect pointer to NULL
    inframe = false;
    cs = 0;
    counter = 0;
    bulletsCount = 0;
    moving = true;
    moveX = 0;
}

const char* Tank::getType() {
    return "TANK"; 
}

void Tank::render(int frames) {
    static bool start = false;
    if (!inframe) {
        if (dRect->x == 1250) {
            inframe = true;
        } else {
            dRect->x--;
        }
    } else {
        if (start && counter == 0) {
            if (bulletsCount == 3) {
                if (frames % 100 == 0 && moving) {
                    moveX += 1.99;
                }

                if ((dRect->x) < 50 && moving) {
                    moving = false;
                    moveX = -2;
                } else if ((dRect->x) > 1250 && !moving) {
                    moving = true;
                    moveX = 0;
                    bulletsCount = 0;
                }
                Move(-moveX, 0);
            } else {
                if (frames % 100 == 0) {
                    fire();
                    bulletsCount += 1;
                }
            }
        }
    }

    if (counter > 0) {
        if (counter == 1)
            Alive = false;
        counter -= 1;
    }

    health.display(dRect->x, dRect->y);
    sprite[cs]->render(frames, SDL_FLIP_HORIZONTAL);

    start = true;
}

bool Tank::IsAlive() {
    return Alive;
}

void Tank::CollisionImpact(GameObjects* CollidedWith) {
    if (strcmp(CollidedWith->getType(), "HEROBULLET") == 0) { 
        SDL_Rect collide = { (CollidedWith->get_Position()).get_X(), (CollidedWith->get_Position()).get_Y(), (CollidedWith->get_Size()).get_X(), (CollidedWith->get_Size()).get_Y() };
        if (SDL_HasIntersection(&collide, dRect)) {
            CollidedWith->setAlive(false);
            health.decrease(1);
            if (health.get_Health() == 0) {
                sounds[0]->Play();
                if (counter == 0) {
                    counter = 45;
                }
                cs = 1;
            }
        }
    }
}

Point Tank::get_Position() {
    return sprite[cs]->get_Position();
}

Point Tank::get_Size() {
    return sprite[cs]->get_Size();
}

void Tank::EventsController(SDL_Event* e) {
    // None
}

void Tank::Move(int x, int y) {
    sprite[cs]->moveDestinationArea(x, y);
}

void Tank::setAlive(bool alive) {
    this->Alive = alive;
}

Tank::~Tank() {
    for (int i = 0; i < 2; i++)
        delete sprite[i];
    for (int i = 0; i < 1; i++)
        delete sounds[i];
    delete dRect;
}

void Tank::fire() {
    bullets->add(new Bullet(gWindow, gRenderer, dRect->x, dRect->y + 55, -10, 0, "ENEMYBULLET"));
}

void SaveTankToFile(FILE* file, Tank* tank) {
    fprintf(file, "---TANK---\n");
    fprintf(file, "%d\n", tank->inframe ? 1 : 0);  
    fprintf(file, "%d\n", tank->health.get_Health());
    fprintf(file, "%d\n", tank->cs);
    fprintf(file, "%d\n", tank->counter);
    fprintf(file, "%d\n", tank->bulletsCount);
    fprintf(file, "%d\n", tank->moving ? 1 : 0);  
    fprintf(file, "%f\n", tank->moveX);
    fprintf(file, "%d\n", tank->Alive ? 1 : 0);  
    fprintf(file, "%d\n", tank->dRect->x);
    fprintf(file, "%d\n", tank->dRect->y);
}

void LoadTankFromFile(FILE* file, Tank* tank) {
    int temp;
    fscanf(file, "%*s"); 
    fscanf(file, "%d", &temp); tank->inframe = (temp != 0); 
    fscanf(file, "%d", &temp); tank->health.set_Health(temp);
    fscanf(file, "%d", &tank->cs);
    fscanf(file, "%d", &tank->counter);
    fscanf(file, "%d", &tank->bulletsCount);
    fscanf(file, "%d", &temp); tank->moving = (temp != 0); 
    fscanf(file, "%f", &tank->moveX);
    fscanf(file, "%d", &temp); tank->Alive = (temp != 0); 
    fscanf(file, "%d", &tank->dRect->x);
    fscanf(file, "%d", &tank->dRect->y);
}
#include "Helicopter.h"

Helicopter::Helicopter(SDL_Window* gWindow, SDL_Renderer* gRenderer, int posX, int posY, List<GameObjects*>* bullets)
    : health(100, gWindow, gRenderer, posX, posY - 20) {
    Alive = true;
    this->gWindow = gWindow;
    this->gRenderer = gRenderer;
    this->bullets = bullets;
    dRect = new SDL_Rect{ posX, posY, 250, 150 };
    sprite[0] = new Sprites(gWindow, gRenderer, "data\\Aircrafts\\helicopter.png", 16, 2000 / 16, 128, dRect, "", true);
    sprite[1] = new Sprites(gWindow, gRenderer, "data\\tanks\\Image\\blast1.png", 7, 945 / 7, 176, dRect, "", true);
    sounds[0] = new SoundEffects("data\\common\\blast.wav");
    blasted = false;
    counter = 0;
    CounterOfBlast = 0;
    cs = 0;
    bulletsCount = 0;
    moving = true;
    moveX = 0;
}

const char* Helicopter::getType() {
    return "HELICOPTER";  
}

void Helicopter::render(int frames) {
    GameObjects* hero = bullets->getStart()->value;
    int Hx = (hero->get_Position()).get_X();
    int Ex = get_Position().get_X();
    if (Ex - Hx > 0) {
        Move(-2);
    } else {
        Move(2);
    }

    if (CounterOfBlast < 0 && blasted) {
        Alive = false;
    } else if (blasted) {
        CounterOfBlast--;
    }

    fire();
    health.display(dRect->x, dRect->y);
    sprite[cs]->render(frames);
}

bool Helicopter::IsAlive() {
    return Alive;
}

void Helicopter::CollisionImpact(GameObjects* CollidedWith) {
    if (strcmp(CollidedWith->getType(), "HEROBULLET") == 0) {  
        SDL_Rect collide = { (CollidedWith->get_Position()).get_X(), (CollidedWith->get_Position()).get_Y(), (CollidedWith->get_Size()).get_X(), (CollidedWith->get_Size()).get_Y() };
        if (SDL_HasIntersection(&collide, dRect)) {
            CollidedWith->setAlive(false);
            health.decrease(1);
            if (health.get_Health() == 0) {
                if (CounterOfBlast == 0) {
                    sounds[0]->Play();
                    blasted = true;
                    CounterOfBlast = 30;
                    cs = 1;
                }
            }
        }
    }
}

Point Helicopter::get_Position() {
    return sprite[cs]->get_Position();
}

Point Helicopter::get_Size() {
    return sprite[cs]->get_Size();
}

void Helicopter::EventsController(SDL_Event* e) {
    // Events are not used in this class
}

void Helicopter::Move(int x, int y) {
    sprite[cs]->moveDestinationArea(x, y);
}

void Helicopter::setAlive(bool alive) {
    this->Alive = alive;
}

Helicopter::~Helicopter() {
    for (int i = 0; i < 2; i++)
        delete sprite[i];
    for (int i = 0; i < 1; i++)
        delete sounds[i];
    delete dRect;
}

void Helicopter::fire() {
    GameObjects* haro = bullets->getStart()->value;
    SDL_Rect helicopter = { (dRect->x) + (dRect->w / 3), (haro->get_Position()).get_Y(), dRect->w / 3, dRect->h };
    SDL_Rect hero = { (haro->get_Position()).get_X(), (haro->get_Position()).get_Y(), (haro->get_Size()).get_Y(), (haro->get_Size()).get_Y() };
    if (counter == 0) {
        if ((SDL_HasIntersection(&helicopter, &hero))) {
            bullets->add(new Bullet(gWindow, gRenderer, (dRect->x) + (dRect->w / 2), (dRect->y) + (dRect->h), 0, 3, "ENEMYBULLET"));
            counter = 50;
        }
    } else {
        counter--;
    }
}

void SaveHelicopterToFile(FILE* file, Helicopter* helicopter) {
    fprintf(file, "---HELICOPTER---\n");
    fprintf(file, "%d\n", helicopter->blasted ? 1 : 0);  
    fprintf(file, "%d\n", helicopter->counter);
    fprintf(file, "%d\n", helicopter->CounterOfBlast);
    fprintf(file, "%d\n", helicopter->cs);
    fprintf(file, "%d\n", helicopter->bulletsCount);
    fprintf(file, "%d\n", helicopter->moving ? 1 : 0); 
    fprintf(file, "%f\n", helicopter->moveX);
    fprintf(file, "%d\n", helicopter->Alive ? 1 : 0);  
    fprintf(file, "%d\n", helicopter->dRect->x);
    fprintf(file, "%d\n", helicopter->dRect->y);
    fprintf(file, "%d\n", helicopter->health.get_Health());
}

void LoadHelicopterFromFile(FILE* file, Helicopter* helicopter) {
    int temp;
    fscanf(file, "%*s"); // Skip the first line
    fscanf(file, "%d", &temp); helicopter->blasted = (temp != 0); 
    fscanf(file, "%d", &helicopter->counter);
    fscanf(file, "%d", &helicopter->CounterOfBlast);
    fscanf(file, "%d", &helicopter->cs);
    fscanf(file, "%d", &helicopter->bulletsCount);
    fscanf(file, "%d", &temp); helicopter->moving = (temp != 0);  
    fscanf(file, "%f", &helicopter->moveX);
    fscanf(file, "%d", &temp); helicopter->Alive = (temp != 0);  
    fscanf(file, "%d", &helicopter->dRect->x);
    fscanf(file, "%d", &helicopter->dRect->y);
    fscanf(file, "%d", &temp); helicopter->health.set_Health(temp);
}
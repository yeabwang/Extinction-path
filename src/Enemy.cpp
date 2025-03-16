#include "Enemy.h"

Enemy::Enemy(SDL_Window* gWindow, SDL_Renderer* grenderer, int posX, List<GameObjects*>* bullets, int delay, Hero* heroPtr) {
    this->delay = delay;
    this->bullets = bullets;
    this->gWindow = gWindow;
    this->grenderer = grenderer;
    dRect = new SDL_Rect{posX, 550, 150, 100};
    sound[0] = new SoundEffects("data\\Enemy\\fire.wav");
    sound[1] = new SoundEffects("data\\Enemy\\dead.wav");
    EnemyStates[0] = new Sprites(gWindow, grenderer, "data\\Enemy\\Images\\firing1.png", 9, 396 / 9, 40, dRect, "Enemy", true);
    EnemyStates[1] = new Sprites(gWindow, grenderer, "data\\Enemy\\Images\\Running1.png", 12, 396 / 12, 42, dRect, "Enemy", true);
    hero = heroPtr ? heroPtr : (bullets->getStart() ? (Hero*)bullets->getStart()->value : nullptr); // Safer hero assignment
}

Point Enemy::get_Position()
{
    return EnemyStates[cs]->get_Position();
}

void Enemy::Move(int x, int y)
{
    EnemyStates[cs]->moveDestinationArea(x, y);
}

void Enemy::setAlive(bool alive)
{
    this->alive = alive;
}

void Enemy::render(int frame) {
    if (alive) {
        if (!fire(frame)) {
            if (hero) { // Check hero pointer
                int Hx = hero->get_Position().get_X();
                int Ex = get_Position().get_X();
                if (Ex - Hx > 0) {
                    flip = SDL_FLIP_NONE;
                    Move(-3);
                } else {
                    flip = SDL_FLIP_HORIZONTAL;
                    Move(3);
                }
            }
        }
        if (count) {
            cs = 0;
            count--;
        } else {
            cs = 1;
        }
        EnemyStates[cs]->render(frame, flip);
    } else if (!alive && count == -1) { // Play death sound only once
        sound[1]->Play();
        count = -2; // Mark as played
    }
}

Enemy::~Enemy() {
    for (int i = 0; i < 2; i++) {
        delete EnemyStates[i];
        delete sound[i]; // Fix: Delete both sounds
    }
    delete dRect;
}

const char* Enemy::getType()
{
    return description;
}

Point Enemy::get_Size()
{
    return EnemyStates[cs]->get_Size();
}

void Enemy::CollisionImpact(GameObjects* CollidedWith)
{
    if (strcmp(CollidedWith->getType(), "HEROBULLET") == 0)
    {
        SDL_Rect collide = { (CollidedWith->get_Position()).get_X(), (CollidedWith->get_Position()).get_Y(), (CollidedWith->get_Size()).get_X(), (CollidedWith->get_Size()).get_Y() };
        SDL_Rect thisRect = { (this->get_Position()).get_X(), (this->get_Position()).get_Y(), (this->get_Size()).get_X(), (this->get_Size()).get_Y() };

        if (SDL_HasIntersection(&collide, &thisRect))
        {
            CollidedWith->setAlive(false);
            this->health--;
        }
        if (this->health == 0)
        {
            sound[1]->Play();
            alive = false;
        }
    }
}

bool Enemy::IsAlive()
{
    return alive;
}

bool Enemy::fire(int frame)
{
    if (!(frame % delay))
    {
        count = 50;
        fired = true;
        sound[0]->Play();
        int Hx = (hero->get_Position()).get_X();
        int Ex = get_Position().get_X();
        int xDiff = (hero->get_Position().get_X() - (this->get_Position().get_X()));
        if (xDiff)
        {
            float slope = ((hero->get_Position().get_Y()) - (this->get_Position().get_Y())) / (hero->get_Position().get_X() - (this->get_Position().get_X()));
            if (Ex - Hx > 0)
                bullets->add(new Bullet(gWindow, grenderer, (EnemyStates[cs]->get_Position()).get_X(), (EnemyStates[cs]->get_Position()).get_Y() + 25, -13, -slope, "ENEMYBULLET"));
            else
                bullets->add(new Bullet(gWindow, grenderer, (EnemyStates[cs]->get_Position()).get_X() + dRect->w, (EnemyStates[cs]->get_Position()).get_Y() + 25, 13, slope, "ENEMYBULLET"));
            return true;
        }
        else
        {
            hero->setAlive(false);
        }
    }
    if (count == 0)
    {
        fired = false;
    }
    return false;
}

void SaveEnemyToFile(FILE* file, Enemy* enemy)
{
    fprintf(file, "---ENEMY---\n");
    fprintf(file, "%d\n", enemy->flip);
    fprintf(file, "%d\n", enemy->delay);
    fprintf(file, "%d\n", enemy->count);
    fprintf(file, "%d\n", enemy->fired);
    fprintf(file, "%d\n", enemy->alive);
    fprintf(file, "%d\n", enemy->movey);
    fprintf(file, "%d\n", enemy->movex);
    fprintf(file, "%d\n", enemy->cs);
    fprintf(file, "%d\n", enemy->dRect->x);
    fprintf(file, "%d\n", enemy->dRect->y);
}

void LoadEnemyFromFile(FILE* file, Enemy* enemy)
{
    char buffer[256];
    fscanf(file, "%*s");
    fscanf(file, "%d", &enemy->flip);
    fscanf(file, "%d", &enemy->delay);
    fscanf(file, "%d", &enemy->count);
    fscanf(file, "%d", &enemy->fired);
    fscanf(file, "%d", &enemy->alive);
    fscanf(file, "%d", &enemy->movey);
    fscanf(file, "%d", &enemy->movex);
    fscanf(file, "%d", &enemy->cs);
    fscanf(file, "%d", &enemy->dRect->x);
    fscanf(file, "%d", &enemy->dRect->y);
}
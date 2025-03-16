#include "Bullet.h"
#include <cmath>

Bullet::Bullet(SDL_Window* gWindow, SDL_Renderer* grenderer, int posX, int posY, float moveX, float moveY, const char* description, const char* spritePath) {
    Image = new Sprites(gWindow, grenderer, spritePath, 1, posX, posY, 16, 11, 16, 11, "Bullet", true);
    homing = (strcmp(description, "DRAGONMISSILE") == 0);
    target = Point(0, 0);
    this->x = moveX;
    this->y = moveY;
    this->description = description;
    inFrame = true;
}

const char* Bullet::getType() {
    return description;
}

bool Bullet::IsAlive() {
    return inFrame;
}

void Bullet::render(int frames) {
    if (inFrame) {
        Move(); // Update position
        if (homing) {
            float dx = target.get_X() - Image->get_Position().get_X();
            float dy = target.get_Y() - Image->get_Position().get_Y();
            double angle = atan2(dy, dx) * 180.0 / M_PI; // Convert radians to degrees
            Image->render(0, SDL_FLIP_NONE, angle); // Render with rotation
        } else {
            Image->render(0); // Default render without rotation
        }
    }
}

void Bullet::setTarget(Point target) {
    this->target = target;
}

Point Bullet::get_Position() {
    return Image->get_Position();
}

Point Bullet::get_Size() {
    return Image->get_Size();
}

void Bullet::setAlive(bool alive) {
    inFrame = alive;
}

bool Bullet::Inframe() {
    return inFrame;
}

void Bullet::Move(int x, int y) {
    if (inFrame) {
        if (homing) {
            float dx = target.get_X() - Image->get_Position().get_X();
            float dy = target.get_Y() - Image->get_Position().get_Y();
            float dist = sqrt(dx * dx + dy * dy);
            if (dist > 5) {
                this->x = (dx / dist) * 3.0f; // Constant speed of 3
                this->y = (dy / dist) * 3.0f;
            } else {
                this->x = 0;
                this->y = 0;
            }
        } else {
            if (x != 0) this->x = x;
            if (y != 0) this->y = y;
        }

        int newX = Image->get_Position().get_X() + static_cast<int>(this->x);
        int newY = Image->get_Position().get_Y() + static_cast<int>(this->y);
        if (newX > 1440 || newX < 0 || newY > 900 || newY < 0) {
            inFrame = false;
        } else {
            Image->moveDestinationArea(this->x, this->y);
        }
    }
}

void Bullet::CollisionImpact(GameObjects* CollidedWith) {
    // No implementation needed per your design
}

Bullet::~Bullet() {
    delete Image;
}
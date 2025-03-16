#include "Dragon.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

#define BOSS_TAILSEGMENT_ACEL_MULTIPLIER 0.7f
#define BOSS_TAILSEGMENT_AACEL_MULTIPLIER 0.06f
#define BOSS_TAILSEGMENT_VEL_MULTIPLIER 0.1f
#define BOSS_TAILSEGMENT_AVEL_MULTIPLIER 0.4f
#define BOSS_TAILSEGMENT_DISTANCE 50
#define BOSS_TAILSEGMENT_CONNECTOR_HIDE_DISTANCE_UP 10
#define BOSS_TAILSEGMENT_CONNECTOR_HIDE_DISTANCE_DOWN 15
#define BOSS_IDLEANIMATION_SPEED 0.03f
#define BOSS_IDLEANIMATION_RADIUS 10
#define BOSS_DEFAULT_TAIL_ROTATION 200
#define BOSS_TAILWIGGLE_AMPLITUDE 30
#define BOSS_TAILWIGGLE_SPEED 0.005f
#define ROCKET_SPEED 3.0f
#define BOSS_LASER_DURATION 1500
#define EASE_IN_PERC 0.1f
#define EASE_OUT_PERC 0.2f
#define LEVELWIDTH 2000
#define LEVELHEIGHT 1500

// Utility Functions
float Lerp(float start, float end, float t) {
    return start + (end - start) * t;
}

SDL_Point Bezier(SDL_Point start, SDL_Point control, SDL_Point end, float t) {
    float t2 = t * t;
    float mt = 1 - t;
    float mt2 = mt * mt;
    SDL_Point result;
    result.x = mt2 * start.x + 2 * mt * t * control.x + t2 * end.x;
    result.y = mt2 * start.y + 2 * mt * t * control.y + t2 * end.y;
    return result;
}

// DragonTailSegment Implementation
// Working in Gods's name :)
DragonTailSegment::DragonTailSegment(SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* path, int x, int y) {
    sprite = new Sprites(gWindow, gRenderer, path, 1, x, y, 50, 50, 50, 50, "Tail Segment");
    rect = sprite->dRect;
    angle = BOSS_DEFAULT_TAIL_ROTATION;
    velX = velY = aVel = 0;
    accelX = accelY = aAccel = 0;
    previous = nullptr;
    next = nullptr;
    connector = nullptr;
}

DragonTailSegment::~DragonTailSegment() {
    delete sprite;
    delete connector;
    delete next;
}

void DragonTailSegment::update(const SDL_Rect& headRect, DragonTailSegment* prev) {
    if (!prev) {
        SDL_Point headCenter = {headRect.x + headRect.w / 2, headRect.y + headRect.h / 2};
        float dx = headCenter.x + cos(headRect.x * 0.01f) * BOSS_TAILSEGMENT_DISTANCE - rect->x;
        float dy = headCenter.y + sin(headRect.y * 0.01f) * BOSS_TAILSEGMENT_DISTANCE - rect->y;
        accelX = dx * BOSS_TAILSEGMENT_ACEL_MULTIPLIER;
        accelY = dy * BOSS_TAILSEGMENT_ACEL_MULTIPLIER;
        aAccel = (BOSS_DEFAULT_TAIL_ROTATION - angle) * BOSS_TAILSEGMENT_AACEL_MULTIPLIER;
    } else {
        SDL_Point prevLower = prev->getMidLowerPoint();
        accelX = (prevLower.x - rect->x) * BOSS_TAILSEGMENT_ACEL_MULTIPLIER;
        accelY = (prevLower.y - rect->y) * BOSS_TAILSEGMENT_ACEL_MULTIPLIER;
        float targetAngle = atan2(prevLower.y - rect->y, prevLower.x - rect->x) * 180 / M_PI;
        aAccel = (targetAngle - angle) * BOSS_TAILSEGMENT_AACEL_MULTIPLIER;
    }

    velX += accelX;
    velY += accelY;
    aVel += aAccel;
    velX *= BOSS_TAILSEGMENT_VEL_MULTIPLIER;
    velY *= BOSS_TAILSEGMENT_VEL_MULTIPLIER;
    aVel *= BOSS_TAILSEGMENT_AVEL_MULTIPLIER;

    rect->x += static_cast<int>(velX);
    rect->y += static_cast<int>(velY);
    angle += aVel;

    sprite->moveDestinationArea(rect->x - sprite->get_Position().get_X(), rect->y - sprite->get_Position().get_Y());
    if (next) next->update(headRect, this);
    if (connector && next) {
        SDL_Point upper = getMidUpperPoint();
        SDL_Point lower = next->getMidUpperPoint();
        int dx = lower.x - upper.x;
        int dy = lower.y - upper.y;
        connector->moveDestinationArea(upper.x - connector->get_Position().get_X(), upper.y - connector->get_Position().get_Y());
        connector->setAngle(atan2(dy, dx) * 180 / M_PI);
        connector->dRect->h = sqrt(dx * dx + dy * dy);
    }
}

void DragonTailSegment::render() {
    if (sprite->isValid()) sprite->render(0, SDL_FLIP_NONE, angle);
    if (connector && connector->isValid()) connector->render(0);
    if (next) next->render();
}

SDL_Point DragonTailSegment::getMidUpperPoint() {
    SDL_Point center = {rect->x + rect->w / 2, rect->y + rect->h / 2};
    float rad = angle * M_PI / 180;
    return {center.x + static_cast<int>(-sin(rad) * BOSS_TAILSEGMENT_CONNECTOR_HIDE_DISTANCE_UP),
            center.y + static_cast<int>(cos(rad) * BOSS_TAILSEGMENT_CONNECTOR_HIDE_DISTANCE_UP)};
}

SDL_Point DragonTailSegment::getMidLowerPoint() {
    SDL_Point center = {rect->x + rect->w / 2, rect->y + rect->h / 2};
    float rad = angle * M_PI / 180;
    return {center.x + static_cast<int>(sin(rad) * BOSS_TAILSEGMENT_CONNECTOR_HIDE_DISTANCE_DOWN),
            center.y + static_cast<int>(-cos(rad) * BOSS_TAILSEGMENT_CONNECTOR_HIDE_DISTANCE_DOWN)};
}

// NavPath Implementation
NavPath::NavPath() : active(false), relPos(0), speed(0), sineAmplitude(0), sineCurveAmount(0), easeIn(false), easeOut(false), mode(LINEAR) {}

void NavPath::initLinear(int startX, int startY, int endX, int endY, float speed, bool easeIn, bool easeOut) {
    start = {startX, startY};
    end = {endX, endY};
    this->speed = speed;
    this->mode = LINEAR;
    this->easeIn = easeIn;
    this->easeOut = easeOut;
}

void NavPath::initSine(int startX, int startY, int endX, int endY, float amp, float curve, float speed, bool easeIn, bool easeOut) {
    initLinear(startX, startY, endX, endY, speed, easeIn, easeOut);
    sineAmplitude = amp;
    sineCurveAmount = curve;
    mode = SINE;
}

void NavPath::initBezier(int startX, int startY, int endX, int endY, int ctrlX, int ctrlY, float speed, bool easeIn, bool easeOut) {
    initLinear(startX, startY, endX, endY, speed, easeIn, easeOut);
    bezierControl = {ctrlX, ctrlY};
    mode = BEZIER;
}

void NavPath::traverse() {
    relPos = 0;
    active = true;
}

SDL_Point NavPath::update() {
    if (!active) return start;
    if (relPos >= 1) active = false;

    float speedMul = 1;
    if (easeIn && relPos < EASE_IN_PERC) speedMul = Lerp(0.01f, 1, relPos / EASE_IN_PERC);
    if (easeOut && relPos > 1 - EASE_OUT_PERC) speedMul = Lerp(1, 0.01f, (relPos - (1 - EASE_OUT_PERC)) / EASE_OUT_PERC);
    relPos += speed * speedMul;

    switch (mode) {
        case LINEAR:
            return {static_cast<int>(Lerp(start.x, end.x, relPos)), static_cast<int>(Lerp(start.y, end.y, relPos))};
        case SINE: {
            float baseX = Lerp(start.x, end.x, relPos);
            float baseY = Lerp(start.y, end.y, relPos);
            float dx = end.x - start.x;
            float dy = end.y - start.y;
            float len = sqrt(dx * dx + dy * dy);
            float perpX = -dy / len * sineAmplitude * sin(relPos * sineCurveAmount * 2 * M_PI);
            float perpY = dx / len * sineAmplitude * sin(relPos * sineCurveAmount * 2 * M_PI);
            return {static_cast<int>(baseX + perpX), static_cast<int>(baseY + perpY)};
        }
        case BEZIER:
            return Bezier(start, bezierControl, end, relPos);
    }
    return start;
}

// NavGraph Implementation
NavGraph::NavGraph(int startX, int startY, Point* heroPos) {
    tlEnter.initBezier(-500, 1500, 130, 700, 500, 1200, 0.01f, false, true);
    tlExit.initSine(130, 700, 130, -500, 170, 5, 0.005f, true, false);
    tl2Exit.initBezier(130, 700, -500, 800, 0, 500, 0.02f, true, false);
    followPath.initLinear(startX, startY, heroPos->get_X(), heroPos->get_Y(), 0.02f, false, false);
    active = &followPath;
    active->start.x = startX;
    active->start.y = startY;
    location = OUT;
    target = heroPos;
}

void NavGraph::moveTo(Locations loc) {
    switch (loc) {
        case TL: active = &tlEnter; break;
        case TL2: active = &tlEnter; break;
        case OUT:
            if (location == TL) active = &tlExit;
            else if (location == TL2) active = &tl2Exit;
            break;
    }
    active->traverse();
    location = loc;
}

void NavGraph::follow(Point heroPos) {
    followPath.end.x = heroPos.get_X();
    followPath.end.y = heroPos.get_Y();
    if (active != &followPath || !active->isBusy()) {
        active = &followPath;
        active->traverse();
    }
}

SDL_Point NavGraph::update() {
    return active->update();
}

// Dragon Implementation
Dragon::Dragon(SDL_Window* gWindow, SDL_Renderer* gRenderer, int posX, int posY, List<GameObjects*>* bullets, terrain* ter, Hero* hero)
    : health(200, gWindow, gRenderer, posX, posY - 20), 
      alive(true), 
      gWindow(gWindow), 
      gRenderer(gRenderer), 
      bullets(bullets), 
      ter(ter), 
      hero(hero),
      heroPos(hero->get_Position()),
      headAngle(0), 
      idleAngle(0), 
      idleOffsetX(0), 
      idleOffsetY(0), 
      idleOffsetMulX(1), 
      idleOffsetMulY(1),
      laserOn(false), 
      laserCounter(0), 
      laserStage(0), 
      rocketCounter(0), 
      spawnRocketDrops(false),
      tailWiggleAmplitude(1.0f), 
      tailWiggleSpeed(1.0f), 
      tailWiggleTimer(0), 
      attackStage(0), 
      currentAttack(NONE),
      laserFlareAngle(0) {
    headRect = new SDL_Rect{posX, posY, 250, 150};
    headSprite = new Sprites(gWindow, gRenderer, "data/Boss/boss_head.png", 1, posX, posY, 250, 150, 250, 150, "Dragon Head");
    laserRect = new SDL_Rect{posX + 100, posY + 100, 10, 300};
    laserSprite = new Sprites(gWindow, gRenderer, "data/bullets/laser_sprite.png", 1, laserRect->x, laserRect->y, 10, 300, 10, 300, "Dragon Laser");
    laserFlareRect = new SDL_Rect{posX + 100, posY + 400, 50, 50};
    laserFlare = new Sprites(gWindow, gRenderer, "data/Boss/flare_01_0.png", 1, laserFlareRect->x, laserFlareRect->y, 50, 50, 50, 50, "Laser Flare");

    DragonTailSegment* prev = nullptr;
    for (int i = 0; i < NUM_TAIL_SEGMENTS; i++) {
        const char* tailPath = (i == NUM_TAIL_SEGMENTS - 1) ? "data/Aircrafts/boss_tailsegment_end.png" : "data/Boss/boss_tailsegment.png";
        auto* segment = new DragonTailSegment(gWindow, gRenderer, tailPath, posX - (i + 1) * 50, posY + 50);
        if (i > 0) {
            segment->previous = prev;
            prev->next = segment;
            prev->connector = new Sprites(gWindow, gRenderer, "data/Boss/boss_tailsegmentconnector.png", 1, prev->rect->x, prev->rect->y, 10, 50, 10, 50, "Tail Connector");
        }
        tailSegments.push_back(segment);
        prev = segment;
    }

    for (int i = 0; i < NUM_ROCKETS; i++) {
        missiles.push_back(new Bullet(gWindow, gRenderer, 0, 0, ROCKET_SPEED, 0, "DRAGONMISSILE", "data/Aircrafts/missile.png"));
        missiles[i]->setAlive(false);
    }

    navigator = new NavGraph(posX, posY, &heroPos);
    currentLocation = OUT;

    blastSound = new SoundEffects("data/common/blast.wav");
    laserSound = new SoundEffects("data/hero/sounds/fire.wav");

    if (!headSprite->isValid() || !laserSprite->isValid() || !laserFlare->isValid()) {
        printf("Critical failure: Dragon sprites not loaded. Disabling Dragon.\n");
        alive = false;
    }
}

Dragon::~Dragon() {
    delete headSprite;
    delete headRect;
    for (auto segment : tailSegments) delete segment;
    delete laserSprite;
    delete laserRect;
    delete laserFlare;
    delete laserFlareRect;
    for (auto missile : missiles) delete missile;
    delete navigator;
    delete blastSound;
    delete laserSound;
}

const char* Dragon::getType() {
    return "DRAGON";
}

void Dragon::render(int frame) {
    if (!alive) return;

    heroPos = hero->get_Position(); // Update hero position each frame
    if (currentAttack == NONE) {
        navigator->follow(heroPos);
    }
    SDL_Point newPos = navigator->update();
    Move(newPos.x - headRect->x, newPos.y - headRect->y);

    idleAngle += BOSS_IDLEANIMATION_SPEED;
    idleOffsetX = sin(idleAngle) * BOSS_IDLEANIMATION_RADIUS * idleOffsetMulX;
    idleOffsetY = cos(idleAngle) * BOSS_IDLEANIMATION_RADIUS * idleOffsetMulY;
    headSprite->moveDestinationArea(static_cast<int>(idleOffsetX), static_cast<int>(idleOffsetY));

    updateTail(frame);

    switch (currentAttack) {
        case LASER:
            updateLaser(frame);
            break;
        case ROCKETS:
            fireRockets(frame);
            break;
        case NONE:
            if (frame % 300 == 0) { // Randomly alternate attacks
                launchAttack(rand() % 2 == 0 ? LASER : ROCKETS);
            }
            break;
    }

    for (auto missile : missiles) {
        if (missile->IsAlive()) {
            missile->setTarget(hero->get_Position()); // Homing towards hero
            missile->render(frame);
        }
    }

    if (headSprite->isValid()) headSprite->render(0, SDL_FLIP_NONE, headAngle);
    health.display(headRect->x, headRect->y - 20);

    if (laserOn && laserSprite->isValid() && laserFlare->isValid()) {
        laserSprite->render(0);
        laserFlare->render(0);
    }

    if (health.get_Health() <= 0 && blastSound->isValid()) {
        alive = false;
        blastSound->Play();
    }

    for (auto segment : tailSegments) segment->render();
}

bool Dragon::IsAlive() {
    return alive;
}

void Dragon::CollisionImpact(GameObjects* CollidedWith) {
    if (!CollidedWith) return;
    SDL_Rect collide = {CollidedWith->get_Position().get_X(), CollidedWith->get_Position().get_Y(), CollidedWith->get_Size().get_X(), CollidedWith->get_Size().get_Y()};
    if (strcmp(CollidedWith->getType(), "HEROBULLET") == 0 && SDL_HasIntersection(&collide, headRect)) {
        CollidedWith->setAlive(false);
        health.decrease(1);
    }
}

Point Dragon::get_Position() {
    return Point(headRect->x, headRect->y);
}

Point Dragon::get_Size() {
    return Point(headRect->w, headRect->h);
}

void Dragon::EventsController(SDL_Event* e) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_1: launchAttack(LASER); break;
            case SDLK_2: launchAttack(ROCKETS); break;
            case SDLK_3: spawnRocketDrops = !spawnRocketDrops; break;
        }
    }
}

void Dragon::setAlive(bool alive) {
    this->alive = alive;
}

void Dragon::Move(int x, int y) {
    headRect->x += x;
    headRect->y += y;
    if (headSprite->isValid()) headSprite->moveDestinationArea(x, y);
    laserRect->x += x;
    laserRect->y += y;
    if (laserSprite->isValid()) laserSprite->moveDestinationArea(x, y);
    laserFlareRect->x += x;
    laserFlareRect->y += y;
    if (laserFlare->isValid()) laserFlare->moveDestinationArea(x, y);
}

void Dragon::launchAttack(DragonAttacks attack) {
    currentAttack = attack;
    attackStage = 0;
    laserCounter = 0;
    rocketCounter = 0;
}

void Dragon::updateLaser(int frame) {
    laserCounter++;
    switch (attackStage) {
        case 0:
            navigator->moveTo(TL);
            attackStage = 1;
            break;
        case 1:
            if (!navigator->isBusy()) {
                laserCounter = 0;
                attackStage = 2;
            }
            break;
        case 2:
            headAngle = Lerp(0, -20, laserCounter / 200.0f);
            if (laserCounter >= 200) {
                laserOn = true;
                if (laserSound->isValid()) laserSound->Play();
                tailWiggleAmplitude = 1.5f;
                tailWiggleSpeed = 1.2f;
                laserCounter = 0;
                attackStage = 3;
            }
            break;
        case 3: {
            headAngle = Lerp(-20, 60, laserCounter / (float)BOSS_LASER_DURATION);
            float rad = (headAngle + 90) * M_PI / 180;
            Vector2 from(headRect->x + headRect->w / 2, headRect->y + headRect->h);
            Vector2 dir(cos(rad), sin(rad));
            Vector2 hit = ter->raycast(from, dir, 0.1f);
            laserRect->x = from.x - laserRect->w / 2;
            laserRect->y = from.y;
            laserRect->h = sqrt(pow(hit.x - from.x, 2) + pow(hit.y - from.y, 2));
            laserSprite->setAngle(headAngle + 90);
            laserFlareRect->x = hit.x - laserFlareRect->w / 2;
            laserFlareRect->y = hit.y - laserFlareRect->h / 2;
            laserFlareAngle += 50;
            laserFlare->setAngle(laserFlareAngle);
            if (laserCounter >= BOSS_LASER_DURATION) {
                laserCounter = 0;
                attackStage = 4;
            }
            break;
        }
        case 4: {
            headAngle = Lerp(60, -20, laserCounter / (float)BOSS_LASER_DURATION);
            float rad = (headAngle + 90) * M_PI / 180;
            Vector2 from(headRect->x + headRect->w / 2, headRect->y + headRect->h);
            Vector2 dir(cos(rad), sin(rad));
            Vector2 hit = ter->raycast(from, dir, 0.1f);
            laserRect->x = from.x - laserRect->w / 2;
            laserRect->y = from.y;
            laserRect->h = sqrt(pow(hit.x - from.x, 2) + pow(hit.y - from.y, 2));
            laserSprite->setAngle(headAngle + 90);
            laserFlareRect->x = hit.x - laserFlareRect->w / 2;
            laserFlareRect->y = hit.y - laserFlareRect->h / 2;
            laserFlareAngle += 50;
            laserFlare->setAngle(laserFlareAngle);
            if (laserCounter >= BOSS_LASER_DURATION) {
                laserOn = false;
                laserCounter = 0;
                tailWiggleAmplitude = 1.0f;
                tailWiggleSpeed = 1.0f;
                navigator->moveTo(OUT);
                attackStage = 5;
            }
            break;
        }
        case 5:
            headAngle = Lerp(-20, 0, laserCounter / 500.0f);
            if (!navigator->isBusy()) attackStage = 6;
            break;
        case 6:
            currentAttack = NONE;
            break;
    }
}

void Dragon::fireRockets(int frame) {
    rocketCounter++;
    if (spawnRocketDrops && rocketCounter % 30 == 0) {
        int dropX = rand() % (LEVELWIDTH - 300) + 300;
        bullets->add(new Bullet(gWindow, gRenderer, dropX, 100, 0, ROCKET_SPEED * 3, "ENEMYBULLET", "data/Aircrafts/missile_drop.png"));
    }

    switch (attackStage) {
        case 0:
            navigator->moveTo(TL2);
            attackStage = 1;
            break;
        case 1:
            if (!navigator->isBusy()) {
                tailWiggleAmplitude = 2.0f;
                tailWiggleSpeed = 1.0f;
                idleOffsetMulX = 5.0f;
                idleOffsetMulY = 2.0f;
                int spawnX = -530, spawnY = 700;
                for (int i = 0; i < NUM_ROCKETS / 3; i++) {
                    delete missiles[i];
                    missiles[i] = new Bullet(gWindow, gRenderer, spawnX, spawnY, ROCKET_SPEED, 0, "DRAGONMISSILE", "data/Aircrafts/missile.png");
                    missiles[i]->setAlive(true);
                    spawnY += 80;
                }
                spawnX = -930; spawnY = 200;
                for (int i = NUM_ROCKETS / 3; i < 2 * NUM_ROCKETS / 3; i++) {
                    delete missiles[i];
                    missiles[i] = new Bullet(gWindow, gRenderer, spawnX, spawnY, ROCKET_SPEED, 0, "DRAGONMISSILE", "data/Aircrafts/missile.png");
                    missiles[i]->setAlive(true);
                    spawnY += 80;
                }
                spawnX = -1330; spawnY = 700;
                for (int i = 2 * NUM_ROCKETS / 3; i < NUM_ROCKETS; i++) {
                    delete missiles[i];
                    missiles[i] = new Bullet(gWindow, gRenderer, spawnX, spawnY, ROCKET_SPEED, 0, "DRAGONMISSILE", "data/Aircrafts/missile.png");
                    missiles[i]->setAlive(true);
                    spawnY += 80;
                }
                rocketCounter = 0;
                attackStage = 2;
            }
            break;
        case 2:
            if (rocketCounter > 5000 / 16.67) { // Assuming 60 FPS
                tailWiggleAmplitude = 1.0f;
                tailWiggleSpeed = 1.0f;
                idleOffsetMulX = 1.0f;
                idleOffsetMulY = 1.0f;
                navigator->moveTo(OUT);
                attackStage = 5;
                rocketCounter = 0;
            }
            break;
        case 5:
            headAngle = Lerp(0, -120, rocketCounter / 500.0f);
            if (!navigator->isBusy()) attackStage = 6;
            break;
        case 6:
            headAngle = 0;
            currentAttack = NONE;
            break;
    }
}

void Dragon::updateTail(int frame) {
    tailWiggleTimer++;
    float baseAngle = BOSS_DEFAULT_TAIL_ROTATION + tailWiggleAmplitude * BOSS_TAILWIGGLE_AMPLITUDE * sin(tailWiggleTimer * BOSS_TAILWIGGLE_SPEED * tailWiggleSpeed);
    tailSegments[0]->angle = baseAngle;
    tailSegments[0]->update(*headRect);
}
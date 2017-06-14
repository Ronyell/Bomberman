#include "bomb.hpp"

Bomb::Bomb(std::string objectName, double positionX, double positionY,
           int width, int height) : GameObject(objectName,
                                               positionX,
                                               positionY,
                                               width, height){


        animator = new Animation(objectName, 1, 9, 0.5);
        explosion = new Explosion("assets/sprites/explosion.png",positionX, positionY, 40, 40);

        animator->addAction("planted",0,2);
        animator->addAction("explode",3,8);
        startTime = SDL_GetTicks();
        stepTime = startTime;
        activeBomb = false;
        range = 3;
}

Bomb::~Bomb(){
}

void Bomb::update(double timeElapsed){
        // To Do: Use Time Elapsed in inc.
        timeElapsed = timeElapsed;
        specialAction();

        timeElapsedActive = (SDL_GetTicks() - stepTime) / 1000.0f;

        if(timeElapsedActive >= 2.0 && timeElapsedActive < 2.5){
            animator->setInterval("explode");
            explosion->setPositionX(getPositionX());
            explosion->setPositionY(getPositionY());
            explosion->setRange(range);
            explosion->setActiveExplosion(true);

        }else if(timeElapsedActive >= 2.5){
            activeBomb = false;
        }

        animator->update();
        explosion->update(timeElapsed);
}

void Bomb::specialAction(){
        if(!activeBomb) {
                animator->setInterval("planted");
                stepTime = startTime;
                activeBomb = true;
        }
}

void Bomb::draw(){
        INFO("Bomb DRAW");
        animator->draw(getPositionX(), getPositionY());
        explosion->draw();
}

Animation * Bomb::getAnimation(){
        return animator;
}

bool Bomb::getActiveBomb(){
    return activeBomb;
}

void Bomb::setActiveBomb(bool isActive){
    activeBomb = isActive;
}

int Bomb::getRange(){
    return range;
}
void Bomb::setRange(int rangeBomb){
    range = rangeBomb;
}

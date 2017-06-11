#include "bomb.hpp"

Bomb::Bomb(std::string objectName, double positionX, double positionY,
           int width, int height) : GameObject(objectName,
                                               positionX,
                                               positionY,
                                               width, height){


        animator = new Animation(objectName, 1, 9, 0.5);

        animator->addAction("planted",0,2);
        animator->addAction("explode",3,8);
        startTime = SDL_GetTicks();
        stepTime = startTime;
        activeBomb = false;
        range = 2;
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
        }else if(timeElapsedActive >= 2.5){
            activeBomb = false;
        }

        animator->update();
}

void Bomb::specialAction(){
        if(InputManager::instance.isKeyPressed(InputManager::KEY_PRESS_SPACE) && !activeBomb) {
                animator->setInterval("planted");
                stepTime = startTime;
                activeBomb = true;
        }
}

void Bomb::draw(){
        INFO("Bomb DRAW");
        animator->draw(getPositionX(), getPositionY());
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

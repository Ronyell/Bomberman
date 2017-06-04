#include "bomb.hpp"

Bomb::Bomb(std::string objectName, double positionX, double positionY,
           int width, int height) : GameObject(objectName,
                                               positionX,
                                               positionY,
                                               width, height){


        animator = new Animation(objectName, 1, 9, 2.0);

        animator->addAction("explode",0,8);
        startTime = SDL_GetTicks();
        stepTime = startTime;
        activeBomb = false;
}

Bomb::~Bomb(){
}

void Bomb::update(double timeElapsed){
        // To Do: Use Time Elapsed in inc.
        timeElapsed = timeElapsed;
        specialAction();

        timeElapsedActive = (SDL_GetTicks() - stepTime) / 1000.0f;

        if(timeElapsedActive >= 1.5){
            activeBomb = false;
        }

        animator->update();
}

void Bomb::specialAction(){
        if(InputManager::instance.isKeyPressed(InputManager::KEY_PRESS_SPACE) && !activeBomb) {
                animator->setInterval("explode");
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

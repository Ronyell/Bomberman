#include "block_destroyable.hpp"
#include "log.h"

BlockDestroyable::BlockDestroyable(std::string objectName, double positionX, double positionY,
                                     int width, int height) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                         width, height){
animation = new Animation(objectName, 1, 6, 0.4);
animation->addAction("idle",0,0);

animation->addAction("explode",1,5);

animation->setInterval("idle");

    startTime = SDL_GetTicks();
    stepTime = startTime;
    isDestroyed = false;
}

BlockDestroyable::~BlockDestroyable(){}
void BlockDestroyable::update(double timeElapsed){
    timeElapsed = timeElapsed;
    animation->update();

    specialAction();
}

void BlockDestroyable::draw(){
    animation->draw(getPositionX(), getPositionY());
}

void BlockDestroyable::specialAction(){
        if(!isEnabled() && animation->getInterval().first!="explode") {
                animation->setInterval("explode");
                stepTime = SDL_GetTicks();
        }else {
            timeElapsedActive = (SDL_GetTicks() - stepTime) / 1000.0f;

            if(!isEnabled() && timeElapsedActive > 0.4){
                isDestroyed = true;
            }
        }
}

bool BlockDestroyable::getIsDestroyed(){
    return isDestroyed;
}

void BlockDestroyable::setIsDestroyed(bool destroyed){
    isDestroyed = destroyed;
}

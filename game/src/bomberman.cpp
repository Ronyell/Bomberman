#include "bomberman.hpp"

Bomberman::Bomberman(std::string objectName, double positionX, double positionY,
                     int width, int height) : GameObject(objectName,
                                                         positionX,
                                                         positionY,
                                                         width, height){

        animator = new Animation(objectName, 6, 5, 0.4);

        animator->addAction("right",0,4);
        animator->addAction("left",25,29);
        animator->addAction("up",10,14);
        animator->addAction("down",5,9);
        animator->addAction("idle_right",1,1);
        animator->addAction("idle_left",28,28);
        animator->addAction("idle_up",11,11);
        animator->addAction("idle_down",7,7);
        animator->addAction("idle",20,24);
        animator->addAction("win",15,19);



        animator->setTotalTime(1.2);
        animator->setInterval("idle_down");

        idleAnimationNumber = 5;
        blockMovement = false;
        stepTime = 0;
}

Bomberman::~Bomberman(){
}

bool Bomberman::specialAction(){
        if(InputManager::instance.isKeyTriggered(InputManager::KEY_PRESS_SPACE)) {
                return true;
        }

        return false;
}

void Bomberman::draw(){
        INFO("Bomberman DRAW");
        animator->draw(getPositionX(), getPositionY());
}

Animation * Bomberman::getAnimation(){
        return animator;
}

void Bomberman::setQuantityBomb(int numBomb){
    quantityBomb = numBomb;
}

int Bomberman::getQuantityBomb(){
    return quantityBomb;
}

void Bomberman::setUnusedBomb(int numBomb){
    unusedBomb = numBomb;
}

int Bomberman::getUnusedBomb(){
    return unusedBomb;
}

void Bomberman::setWinOrLose(bool isWin){
    animator->setTotalTime(0.8);
    
    if(isWin){
        animator->setInterval("win");
    }
    else{
        animator->setInterval("idle");
    }
    setEnabled(false);
}

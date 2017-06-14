#include "bomberman.hpp"
#include "bomb.hpp"

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


        animator->setTotalTime(1.2);
        animator->setInterval("idle_down");

        idleAnimationNumber = 5;
        blockMovement = false;
        stepTime = 0;
}

Bomberman::~Bomberman(){
}

void Bomberman::update(double timeElapsed){
        // To Do: Use Time Elapsed in inc.
        auto incY = 0.10*timeElapsed;
        auto incX = 0.10*timeElapsed;

        if(!blockMovement) {
                walkInX(incX);
                walkInY(incY, incX);
        }

        if(incX == 0 && incY == 0) {
                stepTime += timeElapsed;
                if(animator->getInterval().first == "right") {
                        animator->setInterval("idle_right");
                }else if (animator->getInterval().first == "left") {
                        animator->setInterval("idle_left");
                }else if (animator->getInterval().first == "up") {
                        animator->setInterval("idle_up");
                }else if (animator->getInterval().first == "down") {
                        animator->setInterval("idle_down");
                }
                if(stepTime > 2000){
                    animator->setTotalTime(1.0);
                    animator->setInterval("idle");
                }
        }else{
            stepTime = 0;
        }
        if(animator->getInterval().first != "idle"){
            animator->setTotalTime(0.3);
        }
        specialAction();
        animator->update();
}

void Bomberman::walkInX(double & incX){

        if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_RIGHT)) {
                incX = incX;
                idleAnimationNumber = 5;
                animator->setInterval("right");
        }
        else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_LEFT)) {
                incX = incX * (-1);
                idleAnimationNumber = 0;
                animator->setInterval("left");
        }
        else {
                incX = 0;
        }
        setPositionX(getPositionX()+incX);
        if(CollisionManager::instance.verifyCollisionWithBlocks(this,0,30)) {
                setPositionX(getPositionX()+(incX*(0-1)));
        }
}

void Bomberman::walkInY(double & incY, double incX){

        if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_UP)) {
                incY = incY * (0-1);
                idleAnimationNumber = 5;
                if(incX == 0) {
                        animator->setInterval("up");
                }
        }
        else if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::KEY_PRESS_DOWN)) {
                incY = incY;
                idleAnimationNumber = 0;
                if(incX == 0) {
                        animator->setInterval("down");
                }
        }
        else {
                incY = 0;
        }
        setPositionY(getPositionY()+incY);
        if(CollisionManager::instance.verifyCollisionWithBlocks(this, 0, 30)) {
                setPositionY(getPositionY()+(incY*(0-1)));
        }
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

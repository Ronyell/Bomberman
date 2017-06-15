#include "first_bomberman.hpp"

FirstBomberman::FirstBomberman(std::string objectName, double positionX, double positionY,
                     int width, int height) : Bomberman(objectName,
                                                         positionX,
                                                         positionY,
                                                         width, height){}

FirstBomberman::~FirstBomberman(){
}

void FirstBomberman::update(double timeElapsed){
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

void FirstBomberman::walkInX(double & incX){

        if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_D)) {
                incX = incX;
                idleAnimationNumber = 5;
                animator->setInterval("right");
        }
        else if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_A)) {
                incX = incX * (-1);
                idleAnimationNumber = 0;
                animator->setInterval("left");
        }
        else {
                incX = 0;
        }
        setPositionX(getPositionX()+incX);
        if(CollisionManager::instance.verifyCollisionWithBlocks(this, 0, 30)) {
                setPositionX(getPositionX()+(incX*(0-1)));
        }
}

void FirstBomberman::walkInY(double & incY, double incX){

        if(InputManager::instance.isKeyPressed(InputManager::KeyPress::KEY_PRESS_W)) {
                incY = incY * (0-1);
                idleAnimationNumber = 5;
                if(incX == 0) {
                        animator->setInterval("up");
                }
        }
        else if(engine::InputManager::instance.isKeyPressed(engine::InputManager::KeyPress::KEY_PRESS_S)) {
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

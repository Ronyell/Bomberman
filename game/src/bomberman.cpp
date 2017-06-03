#include "bomberman.hpp"

Bomberman::Bomberman(std::string objectName, double positionX, double positionY,
                     int width, int height) : GameObject(objectName,
                                                         positionX,
                                                         positionY,
                                                         width, height){

        animator = new Animation(objectName, 6, 5, 0.5);

        animator->addAction("right",0,5);
        animator->addAction("left",25,29);
        animator->addAction("up",10,14);
        animator->addAction("down",5,9);
        animator->addAction("idle_right",1,1);
        animator->addAction("idle_left",28,28);
        animator->addAction("idle_up",11,11);
        animator->addAction("idle_down",7,7);

        idleAnimationNumber = 5;
        blockMovement = false;
}

Bomberman::~Bomberman(){
}

void Bomberman::update(double timeElapsed){
        // To Do: Use Time Elapsed in inc.
        animator->setTotalTime(0.4);
        auto incY = 0.10*timeElapsed;
        auto incX = 0.10*timeElapsed;

        if(!blockMovement) {
                walkInX(incX);
                walkInY(incY, incX);
        }

        if(incX == 0 && incY == 0) {
                if(animator->getInterval().first == "right") {
                        animator->setInterval("idle_right");
                }else if (animator->getInterval().first == "left") {
                        animator->setInterval("idle_left");
                }else if (animator->getInterval().first == "up") {
                        animator->setInterval("idle_up");
                }else if (animator->getInterval().first == "down") {
                        animator->setInterval("idle_down");
                }
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

void Bomberman::specialAction(){
        if(InputManager::instance.isKeyPressed(InputManager::KEY_PRESS_SPACE)) {
                if(idleAnimationNumber == 5) {
                        animator->setInterval("special_right");
                }else{
                        animator->setInterval("special_left");
                }
        }
}

void Bomberman::draw(){
        INFO("Bomberman DRAW");
        animator->draw(getPositionX(), getPositionY());
}

Animation * Bomberman::getAnimation(){
        return animator;
}

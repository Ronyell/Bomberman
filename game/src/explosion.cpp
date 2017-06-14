#include "explosion.hpp"

Explosion::Explosion(std::string objectName, double positionX, double positionY,
                     int width, int height) : GameObject(objectName,
                                                         positionX,
                                                         positionY,
                                                         width, height){


        animatorCenter = new Animation(objectName, 7, 4, 0.5);

        animatorLeft = new Animation(objectName, 7, 4, 0.5);
        animatorRight = new Animation(objectName, 7, 4, 0.5);
        animatorUp = new Animation(objectName, 7, 4, 0.5);
        animatorDown = new Animation(objectName, 7, 4, 0.5);

        animatorLeftMiddle = new Animation(objectName, 7, 4, 0.5);
        animatorRightMiddle = new Animation(objectName, 7, 4, 0.5);
        animatorUpMiddle = new Animation(objectName, 7, 4, 0.5);
        animatorDownMiddle = new Animation(objectName, 7, 4, 0.5);


        animatorCenter->addAction("explode",0,3);
        animatorLeft->addAction("explode",12,15);
        animatorRight->addAction("explode",16,19);
        animatorUp->addAction("explode",24,27);
        animatorDown->addAction("explode",20,23);

        // animatorLeftMiddle->addAction("explode",4,7);
        // animatorRightMiddle->addAction("explode",4,7);
        // animatorUpMiddle->addAction("explode",8,11);
        // animatorDownMiddle->addAction("explode",8,11);
        //
        // animatorLeftMiddle->setInterval("explode");
        // animatorRightMiddle->setInterval("explode");
        // animatorUpMiddle->setInterval("explode");
        // animatorDownMiddle->setInterval("explode");

        animatorCenter->setInterval("explode");
        animatorLeft->setInterval("explode");
        animatorRight->setInterval("explode");
        animatorUp->setInterval("explode");
        animatorDown->setInterval("explode");


        activeExplosion = false;
}

Explosion::~Explosion(){
}

void Explosion::update(double timeElapsed){
        timeElapsed = timeElapsed;
        specialAction();
        if(activeExplosion) {
                animatorCenter->update();
                // animatorLeftMiddle->update();
                // animatorRightMiddle->update();
                // animatorUpMiddle->update();
                // animatorDownMiddle->update();
                animatorLeft->update();
                animatorRight->update();
                animatorUp->update();
                animatorDown->update();
        }
}

void Explosion::specialAction(){

}

void Explosion::draw(){
        INFO("Explosion DRAW");
        if(activeExplosion) {
                animatorCenter->draw(getPositionX(), getPositionY());
                bool up = false, down = false, left = false, right = false;

                for(int i = 1; i <= range; i++) {
                        if(!left && !CollisionManager::instance.verifyCollisionWithBlocks(new GameObject("", getPositionX() - getWidth()*i,  getPositionY(), getWidth(),getHeight()))) {
                                animatorLeft->draw(getPositionX() - getWidth()*i, getPositionY());
                        }else{
                                left = true;
                        }
                        if(!right && !CollisionManager::instance.verifyCollisionWithBlocks(new GameObject("", getPositionX() + getWidth()*i,  getPositionY(), getWidth(),getHeight()))) {
                                animatorRight->draw(getPositionX() + getWidth()*i, getPositionY());
                        }else{
                                right = true;
                        }
                        if(!up && !CollisionManager::instance.verifyCollisionWithBlocks(new GameObject("", getPositionX(),  getPositionY()- getHeight()*i, getWidth(),getHeight()))) {
                                animatorUp->draw(getPositionX(), getPositionY() - getHeight()*i);
                        }else{
                                up = true;
                        }
                        if(!down && !CollisionManager::instance.verifyCollisionWithBlocks(new GameObject("", getPositionX(),  getPositionY()+ getHeight()*i, getWidth(),getHeight()))) {
                                animatorDown->draw(getPositionX(), getPositionY() + getHeight()*i);
                        }else{
                                down = true;
                        }

                }
        }
}

Animation * Explosion::getAnimation(){
        return animatorUp;
}

bool Explosion::getActiveExplosion(){
        return activeExplosion;
}

void Explosion::setActiveExplosion(bool isActive){
        activeExplosion = isActive;
}

int Explosion::getRange(){
        return range;
}
void Explosion::setRange(int rangeExplosion){
        range = rangeExplosion;
}

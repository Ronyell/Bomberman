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

        animatorLeftMiddle->addAction("explode",4,7);
        animatorRightMiddle->addAction("explode",4,7);
        animatorUpMiddle->addAction("explode",8,11);
        animatorDownMiddle->addAction("explode",8,11);

        animatorLeftMiddle->setInterval("explode");
        animatorRightMiddle->setInterval("explode");
        animatorUpMiddle->setInterval("explode");
        animatorDownMiddle->setInterval("explode");

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
                animatorLeftMiddle->update();
                animatorRightMiddle->update();
                animatorUpMiddle->update();
                animatorDownMiddle->update();
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
                bool up = false, down = false, left = false, right = false;

                for(int i = 1; i <= (range + 1); i++) {
                        if( i != (range + 1) && !left && !CollisionManager::instance.verifyCollisionWithBlocks(new GameObject("", getPositionX() - getWidth()*i,  getPositionY(), getWidth(),getHeight()))) {
                                animatorLeftMiddle->draw(getPositionX() - getWidth()*(i - 1), getPositionY());
                        }else{
                                if(!left) {
                                        animatorLeft->draw(getPositionX() - getWidth()*(i - 1), getPositionY());
                                }
                                left = true;
                        }
                        if(i != (range + 1) && !right && !CollisionManager::instance.verifyCollisionWithBlocks(new GameObject("", getPositionX() + getWidth()*i,  getPositionY(), getWidth(),getHeight()))) {
                                animatorRightMiddle->draw(getPositionX() + getWidth()*(i - 1), getPositionY());
                        }else{
                                if(!right) {
                                        animatorRight->draw(getPositionX() + getWidth()*(i - 1), getPositionY());
                                }
                                right = true;
                        }
                        if(i != (range + 1) && !up && !CollisionManager::instance.verifyCollisionWithBlocks(new GameObject("", getPositionX(),  getPositionY()- getHeight()*i, getWidth(),getHeight()))) {
                                animatorUpMiddle->draw(getPositionX(), getPositionY() - getHeight()*(i - 1));
                        }else{
                                if(!up) {
                                        animatorUp->draw(getPositionX(), getPositionY() - getHeight()*(i - 1));
                                }
                                up = true;
                        }
                        if(i != (range + 1) && !down && !CollisionManager::instance.verifyCollisionWithBlocks(new GameObject("", getPositionX(),  getPositionY()+ getHeight()*i, getWidth(),getHeight()))) {
                                animatorDownMiddle->draw(getPositionX(), getPositionY() + getHeight()*(i - 1));
                        }else{
                                if(!down) {
                                        animatorDown->draw(getPositionX(), getPositionY() + getHeight()*(i - 1));
                                }
                                down = true;
                        }

                }
                animatorCenter->draw(getPositionX(), getPositionY());
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

#include "block_undestroyable.hpp"
#include "log.h"

BlockUndestroyable::BlockUndestroyable(std::string objectName, double positionX, double positionY,
                                     int width, int height) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                         width, height){
sprite = new Sprite(objectName);
}

BlockUndestroyable::~BlockUndestroyable(){}
void BlockUndestroyable::update(double timeElapsed){
    timeElapsed = timeElapsed;
    //sprite->update();
}

void BlockUndestroyable::draw(){
    sprite->draw(getPositionX(), getPositionY());
}

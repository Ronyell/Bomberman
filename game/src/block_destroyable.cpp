#include "block_destroyable.hpp"
#include "log.h"

BlockDestroyable::BlockDestroyable(std::string objectName, double positionX, double positionY,
                                     int width, int height) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                         width, height){
sprite = new Sprite(objectName);
}

BlockDestroyable::~BlockDestroyable(){}
void BlockDestroyable::update(double timeElapsed){
    timeElapsed = timeElapsed;
    //sprite->update();
}

void BlockDestroyable::draw(){
    sprite->draw(getPositionX(), getPositionY());
}

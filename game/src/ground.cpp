#include "ground.hpp"
#include "log.h"

Ground::Ground(std::string objectName, double positionX, double positionY,
                                     int width, int height) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                         width, height){
sprite = new Sprite(objectName);
}

Ground::~Ground(){}
void Ground::update(double timeElapsed){
    timeElapsed = timeElapsed;
}

void Ground::draw(){
    sprite->draw(getPositionX(), getPositionY());
}

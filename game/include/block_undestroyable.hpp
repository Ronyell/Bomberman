#ifndef BLOCK_UNDESTROYABLE_HPP
#define BLOCK_UNDESTROYABLE_HPP

#include "engine.hpp"
#include "sprite.hpp"
#include "game_object.hpp"

using namespace engine;

class BlockUndestroyable: public GameObject{
public:
    BlockUndestroyable(std::string objectName, double positionX, double positionY, int width, int height);
    ~BlockUndestroyable();
    void update(double timeElapsed);
    void draw();
    void init();
    Sprite * getSprite();
private:
    Sprite* sprite;
};
#endif

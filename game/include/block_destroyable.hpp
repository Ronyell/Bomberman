#ifndef BLOCK_DESTROYABLE_HPP
#define BLOCK_DESTROYABLE_HPP

#include "engine.hpp"
#include "sprite.hpp"
#include "game_object.hpp"

using namespace engine;

class BlockDestroyable: public GameObject{
public:
    BlockDestroyable(std::string objectName, double positionX, double positionY, int width, int height);
    ~BlockDestroyable();
    void update(double timeElapsed);
    void draw();
    void init();
    Sprite * getSprite();
private:
    Sprite* sprite;
};
#endif

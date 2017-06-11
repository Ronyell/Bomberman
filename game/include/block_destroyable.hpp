#ifndef BLOCK_DESTROYABLE_HPP
#define BLOCK_DESTROYABLE_HPP

#include "engine.hpp"
#include "animation.hpp"
#include "game_object.hpp"

using namespace engine;

class BlockDestroyable: public GameObject{
public:
    BlockDestroyable(std::string objectName, double positionX, double positionY, int width, int height);
    ~BlockDestroyable();
    void update(double timeElapsed);
    void draw();
    void init();
    void specialAction();
    bool getIsDestroyed();
    void setIsDestroyed(bool destroyed);
    Animation * getAnimation();
private:
    Animation* animation;
    bool isDestroyed;
    double startTime;
    double timeElapsedActive;
    double stepTime;
};
#endif

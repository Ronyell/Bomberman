#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "collision_manager.hpp"

using namespace engine;

class Explosion: public GameObject{
public:
    Explosion(std::string objectName, double positionX, double positionY, int width, int height);
    ~Explosion();
    void update(double timeElapsed);
    void draw();
    void init();
    Animation * getAnimation();
    bool getActiveExplosion();
    void setActiveExplosion(bool isActive);
    int getRange();
    void setRange(int rangeBomb);
protected:
    void specialAction();
    Animation *animatorRight, *animatorLeft, *animatorUp, *animatorDown, *animatorCenter;
    bool activeExplosion;
    int range;
};

#endif

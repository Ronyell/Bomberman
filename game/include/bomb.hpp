#ifndef BOMB_HPP
#define BOMB_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "collision_manager.hpp"
#include "explosion.hpp"


using namespace engine;

class Bomb: public GameObject{
public:
    Bomb(std::string objectName, double positionX, double positionY, int width, int height);
    ~Bomb();
    void update(double timeElapsed);
    void draw();
    void init();
    Animation * getAnimation();
    bool getActiveBomb();
    void setActiveBomb(bool isActive);
    int getRange();
    void setRange(int rangeBomb);
protected:
    void specialAction();
    Animation* animator;
    Explosion* explosion;
    bool activeBomb;
    double startTime;
    double timeElapsedActive;
    double stepTime;
    int range;
};

#endif

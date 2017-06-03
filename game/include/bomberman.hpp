#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "collision_manager.hpp"

using namespace engine;

class Bomberman: public GameObject{
public:
    Bomberman(std::string objectName, double positionX, double positionY, int width, int height);
    ~Bomberman();
    void update(double timeElapsed);
    void draw();
    void init();
    Animation * getAnimation();
protected:
    void walkInX(double & incX);
    void walkInY(double & incY, double incX);
    void specialAction();
    Animation* animator;
    int idleAnimationNumber;
    std::string alienName;
    bool blockMovement;
};

#endif
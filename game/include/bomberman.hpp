#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "collision_manager.hpp"
#include "bomb.hpp"

using namespace engine;

class Bomberman: public GameObject{
public:
    Bomberman(std::string objectName, double positionX, double positionY, int width, int height);
    virtual ~Bomberman();
    virtual void update(double timeElapsed) = 0;
    void draw();
    void init();
    bool specialAction();
    void setQuantityBomb(int numBomb);
    int getQuantityBomb();
    void setUnusedBomb(int numBomb);
    void setWinOrLose(bool isWin);
    int getUnusedBomb();
    Animation * getAnimation();
protected:
    virtual void walkInX(double & incX) = 0;
    virtual void walkInY(double & incY, double incX) = 0;
    Animation* animator;
    int idleAnimationNumber;
    std::string alienName;
    bool blockMovement;
    int quantityBomb;
    int unusedBomb;
    double stepTime;
};

#endif

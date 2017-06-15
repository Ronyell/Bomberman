#ifndef SECOND_BOMBERMAN_HPP
#define SECOND_BOMBERMAN_HPP

#include "engine.hpp"
#include "input_manager.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "collision_manager.hpp"
#include "bomb.hpp"
#include "bomberman.hpp"

using namespace engine;

class SecondBomberman: public Bomberman{
public:
    SecondBomberman(std::string objectName, double positionX, double positionY, int width, int height);
    ~SecondBomberman();
    void update(double timeElapsed);
protected:
    void walkInX(double & incX);
    void walkInY(double & incY, double incX);
};

#endif

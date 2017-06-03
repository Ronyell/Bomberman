#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "input_manager.hpp"
#include "bomberman.hpp"
#include "engine.hpp"

using namespace engine;

class Player: public GameObject{
public:
    Player(std::pair<int, int> player1position, std::pair<int, int> player2position);
    ~Player();
    void update(double timeElapsed);
    void draw();
    // bool isDead();

private:
    Bomberman * bomberman1, * bomberman2;
    // int selectedAlien;
    // void idleAnimation(Bomberman * bomberman);
    // void waitAnimation(int beforeAlien);
};
#endif

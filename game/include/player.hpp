#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "input_manager.hpp"
#include "bomberman.hpp"
#include "engine.hpp"
#include "block_destroyable.hpp"

using namespace engine;

class Player: public GameObject{
public:
    Player(std::pair<int, int> player1position, std::pair<int, int> player2position);
    ~Player();
    void update(double timeElapsed);
    void draw();
    void verifyBlocksDestroyable(std::unordered_map<std::string, GameObject*> * blockDestroyableList);
    bool firstIsDead();
    bool secondIsDead();

private:
    Bomberman * bomberman1, * bomberman2;
    int keyBomb;
    bool firstDead;
    bool secondDead;
    std::unordered_map<std::string, Bomb*> bombList;
};
#endif

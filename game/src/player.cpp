#include "log.h"
#include "player.hpp"
using namespace engine;

Player::Player(std::pair<int, int> player1position, std::pair<int, int> player2position){
    bomberman1 = new Bomberman("assets/sprites/bomberman1.png", player1position.first, player1position.second, 32, 48);
    bomberman2 = new Bomberman("assets/sprites/bomberman1.png", player2position.first, player2position.second, 32, 48);

    bomberman1->update(0);
    bomberman2->update(0);
}

Player::~Player(){}

void Player::update(double timeElapsed){
    bomberman1->update(timeElapsed);
    bomberman2->update(timeElapsed);
}

void Player::draw(){
    INFO("PLAYER DRAW");
    bomberman1->draw();
    bomberman2->draw();
}

#include "log.h"
#include "player.hpp"
using namespace engine;

Player::Player(std::pair<int, int> player1position, std::pair<int, int> player2position){
        bomberman1 = new Bomberman("assets/sprites/bomberman1.png", player2position.first, player2position.second, 31, 48);
        bomberman2 = new Bomberman("assets/sprites/bomberman1.png", player1position.first, player1position.second, 31, 48);

        bomberman1->update(0);
        bomberman2->update(0);
        bomb1 = NULL;
}

Player::~Player(){
}

void Player::update(double timeElapsed){
        if(InputManager::instance.isKeyPressed(InputManager::KEY_PRESS_SPACE)) {
                if (bomb1 == NULL) {
                        int xBomb = (((int)bomberman1->getPositionX() % 40) <= 20) ? bomberman1->getPositionX() - (int)bomberman1->getPositionX() % 40 : bomberman1->getPositionX() + 40 -(int)bomberman1->getPositionX() % 40;
                        int yBomb = (((int)bomberman1->getPositionY() % 40) <= 8) ? bomberman1->getPositionY() - (int)bomberman1->getPositionY() % 40 : bomberman1->getPositionY() + 40 -(int)bomberman1->getPositionY() % 40;

                        bomb1 = new Bomb("assets/sprites/bomb2.png",xBomb,yBomb,32,32);

                }
        }

        if (bomb1 != NULL) {
                bomb1->update(timeElapsed);

                CollisionManager::instance.addBomb("Bomb1",bomb1);

                if(CollisionManager::instance.verifyCollision(bomberman1, bomb1)) {
                        CollisionManager::instance.removeBomb("Bomb1");
                }

                if(!bomb1->getActiveBomb()) {
                        //delete(bomb1);
                        CollisionManager::instance.removeBomb("Bomb1");
                        bomb1 = NULL;
                }
        }

        bomberman1->update(timeElapsed);
        bomberman2->update(timeElapsed);

}

void Player::draw(){
        INFO("PLAYER DRAW");
        if(bomb1 != NULL) {
                bomb1->draw();
        }
        bomberman1->draw();
        bomberman2->draw();
}

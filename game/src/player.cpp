#include "log.h"
#include "player.hpp"
using namespace engine;

Player::Player(std::pair<int, int> player1position, std::pair<int, int> player2position){
        bomberman1 = new Bomberman("assets/sprites/bomberman1.png", player2position.first, player2position.second, 31, 48);
        bomberman2 = new Bomberman("assets/sprites/bomberman1.png", player1position.first, player1position.second, 31, 48);

        bomberman1->update(0);
        bomberman2->update(0);
        bomberman1->setQuantityBomb(3);
        bomberman1->setUnusedBomb(3);
        keyBomb = 0;
}

Player::~Player(){
}

void Player::update(double timeElapsed){
        if(InputManager::instance.isKeyReleased(InputManager::KEY_PRESS_SPACE)) {
                if(bomberman1->getUnusedBomb()){
                    int xBomb = (((int)bomberman1->getPositionX() % 40) <= 20) ? bomberman1->getPositionX() - (int)bomberman1->getPositionX() % 40 : bomberman1->getPositionX() + 40 -(int)bomberman1->getPositionX() % 40;
                    int yBomb = (((int)bomberman1->getPositionY() % 40) <= 8) ? bomberman1->getPositionY() - (int)bomberman1->getPositionY() % 40 : bomberman1->getPositionY() + 40 -(int)bomberman1->getPositionY() % 40;

                    Bomb * bomb = new Bomb("assets/sprites/bomb2.png",xBomb,yBomb,40,40);
                    bombList["Bomb1 "+std::to_string(keyBomb)] = bomb;
                    keyBomb++;
                    bomberman1->setUnusedBomb(bomberman1->getUnusedBomb() - 1);
                    WARN(bomberman1->getUnusedBomb())
                }
        }
        for(std::pair<std::string, Bomb *> bomb: bombList){
                bomb.second->update(timeElapsed);

                CollisionManager::instance.addBomb(bomb.first,bomb.second);

                if(CollisionManager::instance.verifyCollision(bomberman1, bomb.second)) {
                        CollisionManager::instance.removeBomb(bomb.first);
                }
        }

        bomberman1->update(timeElapsed);
        bomberman2->update(timeElapsed);
}

void Player::draw(){
        INFO("PLAYER DRAW");
        for(std::pair<std::string, Bomb *> bomb: bombList) {
                bomb.second->draw();
        }
        bomberman1->draw();
        bomberman2->draw();
}

void Player::verifyBlocksDestroyable(std::unordered_map<std::string, GameObject*> * blockDestroyableList){
        std::vector<std::string> names;
        for(std::pair<std::string, Bomb *> bomb: bombList){
                if(!bomb.second->getActiveBomb()) {
                        CollisionManager::instance.verifyBlocksDestroyable(bomb.second, blockDestroyableList, bomb.second->getRange());
                        CollisionManager::instance.removeBomb(bomb.first);
                        names.push_back(bomb.first);
                }
        }

        for(std::string keyName : names) {
            bombList.erase(keyName);
            int key = keyName.find("Bomb1");

            if(key >= 0){
                bomberman1->setUnusedBomb(bomberman1->getUnusedBomb() + 1);
                WARN("SAIU" << bomberman1->getUnusedBomb())
            }
        }
}

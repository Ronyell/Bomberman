#include "log.h"
#include "player.hpp"
using namespace engine;

Player::Player(std::pair<int, int> player1position, std::pair<int, int> player2position){
        bomberman1 = new FirstBomberman("assets/sprites/bomberman1.png", player2position.first, player2position.second, 30, 22);
        bomberman2 = new SecondBomberman("assets/sprites/bomberman1.png", player1position.first, player1position.second, 30, 22);

        bomberman1->update(0);
        bomberman1->setQuantityBomb(3);
        bomberman1->setUnusedBomb(3);

        bomberman2->update(0);
        bomberman2->setQuantityBomb(3);
        bomberman2->setUnusedBomb(3);

        keyBomb = 0;
        firstDead = false;
        secondDead = false;
}

Player::~Player(){
}

void Player::update(double timeElapsed){
        if(InputManager::instance.isKeyTriggered(InputManager::KEY_PRESS_SPACE)) {
                if(bomberman1->getUnusedBomb()){
                    int xBomb = (((int)bomberman1->getPositionX() % 40) <= 20) ? bomberman1->getPositionX() - (int)bomberman1->getPositionX() % 40 : bomberman1->getPositionX() + 40 -(int)bomberman1->getPositionX() % 40;
                    int yBomb = (((int)bomberman1->getPositionY() % 40) <= 8) ? bomberman1->getPositionY() - (int)bomberman1->getPositionY() % 40 : bomberman1->getPositionY() + 40 -(int)bomberman1->getPositionY() % 40;

                    Bomb * bomb = new Bomb("assets/sprites/bomb2.png",xBomb,yBomb,40,40);
                    bombList1["Bomb1 "+std::to_string(keyBomb)] = bomb;
                    keyBomb++;
                    bomberman1->setUnusedBomb(bomberman1->getUnusedBomb() - 1);
                }
        }

        if(InputManager::instance.isKeyTriggered(InputManager::KEY_PRESS_P)) {
                if(bomberman1->getUnusedBomb()){
                    int xBomb = (((int)bomberman2->getPositionX() % 40) <= 20) ? bomberman2->getPositionX() - (int)bomberman2->getPositionX() % 40 : bomberman2->getPositionX() + 40 -(int)bomberman2->getPositionX() % 40;
                    int yBomb = (((int)bomberman2->getPositionY() % 40) <= 8) ? bomberman2->getPositionY() - (int)bomberman2->getPositionY() % 40 : bomberman2->getPositionY() + 40 -(int)bomberman2->getPositionY() % 40;

                    Bomb * bomb = new Bomb("assets/sprites/bomb2.png",xBomb,yBomb,40,40);
                    bombList2["Bomb2 "+std::to_string(keyBomb)] = bomb;
                    keyBomb++;
                    bomberman2->setUnusedBomb(bomberman2->getUnusedBomb() - 1);
                }
        }


        for(std::pair<std::string, Bomb *> bomb: bombList1){
                bomb.second->update(timeElapsed);

                CollisionManager::instance.addBomb(bomb.first,bomb.second);

                if(CollisionManager::instance.verifyCollision(bomb.second, bomberman1, 0, 30)) {
                        CollisionManager::instance.removeBomb(bomb.first);
                }
        }

        for(std::pair<std::string, Bomb *> bomb: bombList2){
                bomb.second->update(timeElapsed);

                CollisionManager::instance.addBomb(bomb.first,bomb.second);

                if(CollisionManager::instance.verifyCollision(bomb.second, bomberman2, 0, 30)) {
                        CollisionManager::instance.removeBomb(bomb.first);
                }
        }

        bomberman1->update(timeElapsed);
        bomberman2->update(timeElapsed);
}

void Player::draw(){
        INFO("PLAYER DRAW");
        for(std::pair<std::string, Bomb *> bomb: bombList1) {
                bomb.second->draw();
        }
        for(std::pair<std::string, Bomb *> bomb: bombList2) {
                bomb.second->draw();
        }
        bomberman1->draw();
        bomberman2->draw();
}

void Player::verifyBlocksDestroyable(std::unordered_map<std::string, GameObject*> * blockDestroyableList){
        std::vector<std::string> names;
        for(std::pair<std::string, Bomb *> bomb: bombList1){
                if(!bomb.second->getActiveBomb()) {
                        firstDead = firstDead || CollisionManager::instance.verifyCollisionWithPlayer(bomberman1, bomb.second, bomb.second->getRange());
                        secondDead = secondDead || CollisionManager::instance.verifyCollisionWithPlayer(bomberman2, bomb.second, bomb.second->getRange());
                        CollisionManager::instance.verifyBlocksDestroyable(bomb.second, blockDestroyableList, bomb.second->getRange());
                        CollisionManager::instance.removeBomb(bomb.first);
                        names.push_back(bomb.first);
                }
        }

        for(std::string keyName : names) {
            bombList1.erase(keyName);
            int key = keyName.find("Bomb1");

            if(key >= 0){
                bomberman1->setUnusedBomb(bomberman1->getUnusedBomb() + 1);
            }
        }
        names.clear();
        for(std::pair<std::string, Bomb *> bomb: bombList2){
                if(!bomb.second->getActiveBomb()) {
                        firstDead = firstDead || CollisionManager::instance.verifyCollisionWithPlayer(bomberman1, bomb.second, bomb.second->getRange());
                        secondDead = secondDead || CollisionManager::instance.verifyCollisionWithPlayer(bomberman2, bomb.second, bomb.second->getRange());
                        CollisionManager::instance.verifyBlocksDestroyable(bomb.second, blockDestroyableList, bomb.second->getRange());
                        CollisionManager::instance.removeBomb(bomb.first);
                        names.push_back(bomb.first);
                }
        }

        for(std::string keyName : names) {
            bombList2.erase(keyName);
            int key = keyName.find("Bomb2");

            if(key >= 0){
                bomberman2->setUnusedBomb(bomberman1->getUnusedBomb() + 1);
            }
        }

}

bool Player::firstIsDead(){
    return firstDead;
}

bool Player::secondIsDead(){
    return secondDead;
}

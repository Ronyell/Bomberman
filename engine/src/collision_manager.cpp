#include "collision_manager.hpp"
#include "log.h"

using namespace engine;

CollisionManager CollisionManager::instance;

void CollisionManager::addBlockDestroyable(std::string blockName, GameObject* g){
    blockDestroyableList[blockName] = g;
}

void CollisionManager::removeBlockDestroyable(std::string blockName){
    blockDestroyableList.erase(blockName);
}

void CollisionManager::addBlockUndestroyable(std::string blockName, GameObject* g){
    blockUndestroyableList[blockName] = g;
}

void CollisionManager::addBomb(std::string bombName, GameObject* g){
    bombList[bombName] = g;
}

void CollisionManager::verifyBlocksDestroyable(GameObject* g1){
    std::vector<std::string> names;
    for(std::pair<std::string, GameObject *>  destroyable : blockDestroyableList) {
        if(verifyCollision(destroyable.second, g1)){
            names.push_back(destroyable.first);
        }
    }

    for(std::string name: names){
        blockDestroyableList.erase(name);
    }

}

void CollisionManager::verifyBlocksDestroyable(GameObject* g1, std::unordered_map<std::string, GameObject*> * blocksDestroyableList){
    std::vector<std::string> names;
    for(std::pair<std::string, GameObject *>  destroyable : *blocksDestroyableList) {
        if(verifyCollision(destroyable.second, g1)){
            destroyable.second->setEnabled(false);
            names.push_back(destroyable.first);
        }
    }

    for(std::string name: names){
        blockDestroyableList.erase(name);
    }
}

void CollisionManager::removeBomb(std::string bombName){
    bombList.erase(bombName);
}
    bool CollisionManager::verifyCollisionWithBlocks(GameObject* g1){
        for(std::pair<std::string, GameObject *>  destroyable : blockDestroyableList) {
            if(verifyCollision(destroyable.second, g1)){
                return true;
            }
        }
        for(std::pair<std::string, GameObject *> undestroyable: blockUndestroyableList){
            if(verifyCollision(undestroyable.second, g1)){
                return true;
            }
        }
        for(std::pair<std::string, GameObject *> bomb: bombList){
            if(verifyCollision(bomb.second, g1)){
                return true;
            }
        }
        return false;
    }

    bool CollisionManager::verifyCollisionWithBlocks(GameObject* g1, int x, int y){

        for(std::pair<std::string, GameObject *> destroyable : blockDestroyableList) {
            if(verifyCollision(destroyable.second, g1, x, y)){
                return true;
            }
        }
        for(std::pair<std::string, GameObject *> undestroyable: blockUndestroyableList){
            if(verifyCollision(undestroyable.second, g1, x, y)){
                return true;
            }
        }

        for(std::pair<std::string, GameObject *> bomb: bombList){
            if(verifyCollision(bomb.second, g1)){
                return true;
            }
        }
        return false;
    }

    void CollisionManager::resetLists(){
        blockUndestroyableList.clear();
        blockDestroyableList.clear();
    }

    bool CollisionManager::verifyCollision( GameObject* g1, GameObject* g2){
        //The sides of the rectangles
        int leftA, rightA, topA, bottomA;
        int leftB, rightB, topB, bottomB;

        //Calculate the sides of rect A
        leftA = g1->getPositionX();
        rightA = leftA + g1->getWidth();
        topA = g1->getPositionY();
        bottomA = topA + g1->getHeight();

        //Calculate the sides of rect B
        leftB = g2->getPositionX();
        rightB = leftB + g2->getWidth();
        topB = g2->getPositionY();
        bottomB = topB + g2->getHeight();

        //If any of the sides from A are outside of B
        if( bottomA <= topB ){ return false;}
        if( topA >= bottomB ){ return false;}
        if( rightA <= leftB ){ return false;}
        if( leftA >= rightB ){ return false;}
        //If none of the sides from A are outside B
        return true;
    }

    bool CollisionManager::verifyCollision( GameObject* g1, GameObject* g2 ,int x, int y){
        //The sides of the rectangles
        int leftA, rightA, topA, bottomA;
        int leftB, rightB, topB, bottomB;

        //Calculate the sides of rect A
        leftA = g1->getPositionX();
        rightA = leftA + g1->getWidth();
        topA = g1->getPositionY();
        bottomA = topA + g1->getHeight();

        //Calculate the sides of rect B
        leftB = g2->getPositionX() + x;
        rightB = leftB + g2->getWidth() - x;
        topB = g2->getPositionY() + y;
        bottomB = topB + g2->getHeight() - y;

        //If any of the sides from A are outside of B
        if( bottomA <= topB ){ return false;}
        if( topA >= bottomB ){ return false;}
        if( rightA <= leftB ){ return false;}
        if( leftA >= rightB ){ return false;}
        //If none of the sides from A are outside B
        return true;
    }

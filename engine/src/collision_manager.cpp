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

bool CollisionManager::verifyWay(GameObject* g1, GameObject* g2){
        bool isWay = false;
        std::unordered_map<std::string, GameObject*>::iterator search;
        //g1 is block  and g2 is bomb
        if((int)g1->getPositionY() == (int)g2->getPositionY()){
            if((int)g1->getPositionX() >= (int)g2->getPositionX()){
                for(int i = g1->getPositionX(); i >= g2->getPositionX() ; i -= g1->getWidth()){
                    search = blockUndestroyableList.find("block_undestroyable" + std::to_string(i) + " " + std::to_string((int)g1->getPositionY()));
                    if(search != blockUndestroyableList.end()){
                        isWay = true;
                        break;
                    }
                }
            }else{
                for(int i = g1->getPositionX(); i <= g2->getPositionX() ; i += g1->getWidth()){
                    search = blockUndestroyableList.find("block_undestroyable" + std::to_string(i) + " " + std::to_string((int)g1->getPositionY()));
                    if(search != blockUndestroyableList.end()){
                        isWay = true;
                        break;
                    }
                }
            }
        }else{
            if(g1->getPositionY() >= g2->getPositionY()){
                for(int i = g1->getPositionY(); i >= g2->getPositionY() ; i -= g1->getHeight()){
                    search = blockUndestroyableList.find("block_undestroyable" + std::to_string((int)g1->getPositionX()) + " " + std::to_string(i));
                    if(search != blockUndestroyableList.end()){
                        isWay = true;
                        break;
                    }
                }
            }else{
                for(int i = g1->getPositionY(); i <= g2->getPositionY() ; i += g1->getHeight()){
                    search = blockUndestroyableList.find("block_undestroyable" + std::to_string((int)g1->getPositionX()) + " " + std::to_string(i));
                    if(search != blockUndestroyableList.end()){
                        isWay = true;
                        break;
                    }
                }
            }
        }
        return !isWay;
}


void CollisionManager::verifyBlocksDestroyable(GameObject* g1, std::unordered_map<std::string, GameObject*> * listBlocks, int range){
        std::string nameUp, nameDown, nameRight, nameLeft;
        int initialX = g1->getPositionX(), initialY = g1->getPositionY();
        bool xUp = false, xDown = false, xRight = false, xLeft = false;
        int distanceMinUp = 0, distanceMinDown = 0, distanceMinRight = 0, distanceMinLeft = 0;

        g1->setPositionX(initialX - g1->getWidth() * range);

        for(int i = 1; i <= range * 2 + 1; i++) {
                for(std::pair<std::string, GameObject *>  destroyable : *listBlocks) {
                        if(verifyCollision(destroyable.second, g1)) {
                            if(i <= range){
                                if (!xUp){
                                    distanceMinUp = abs(initialX - destroyable.second->getPositionX());
                                    nameUp = destroyable.first;
                                    xUp = true;
                                }else{
                                    if(distanceMinUp > abs(initialX - destroyable.second->getPositionX())){
                                        distanceMinUp = abs(initialX - destroyable.second->getPositionX());
                                        nameUp = destroyable.first;
                                    }
                                }
                            }else{
                                if (!xDown){
                                    distanceMinDown = abs(initialX - destroyable.second->getPositionX());
                                    nameDown = destroyable.first;
                                    xDown = true;
                                }else{
                                    if(distanceMinDown > abs(initialX - destroyable.second->getPositionX())){
                                        distanceMinDown = abs(initialX - destroyable.second->getPositionX());
                                        nameDown = destroyable.first;
                                    }
                                }
                            }
                        }
                }
                g1->setPositionX(g1->getPositionX() + g1->getWidth());
        }
        g1->setPositionX(initialX);

        g1->setPositionY(initialY - g1->getHeight() * range);

        for(int i = 1; i <= range * 2 + 1; i++) {
                for(std::pair<std::string, GameObject *>  destroyable : *listBlocks) {
                        if(verifyCollision(destroyable.second, g1)) {
                            if(i <= range){
                                if (!xLeft){
                                    distanceMinLeft = abs(initialY - destroyable.second->getPositionY());
                                    nameLeft = destroyable.first;
                                    xLeft = true;
                                }else{
                                    if(distanceMinLeft > abs(initialY - destroyable.second->getPositionY())){
                                        distanceMinLeft = abs(initialY - destroyable.second->getPositionY());
                                        nameLeft = destroyable.first;
                                    }
                                }
                            }else{
                                if (!xRight){
                                    distanceMinRight = abs(initialY - destroyable.second->getPositionY());
                                    nameRight = destroyable.first;
                                    xRight = true;
                                }else{
                                    if(distanceMinRight > abs(initialY - destroyable.second->getPositionY())){
                                        distanceMinRight = abs(initialY - destroyable.second->getPositionY());
                                        nameRight = destroyable.first;
                                    }
                                }
                            }
                        }
                }
                g1->setPositionY(g1->getPositionY() + g1->getHeight());
        }

        g1->setPositionY(initialY);

        if(xUp) {
                if(verifyWay((*listBlocks)[nameUp], g1)){
                    (*listBlocks)[nameUp]->setEnabled(false);
                    blockDestroyableList.erase(nameUp);
                }
        }
        if(xDown) {
            if(verifyWay((*listBlocks)[nameDown], g1)){
                (*listBlocks)[nameDown]->setEnabled(false);
                blockDestroyableList.erase(nameDown);
            }
        }
        if(xRight) {
            if(verifyWay((*listBlocks)[nameRight], g1)){
                (*listBlocks)[nameRight]->setEnabled(false);
                blockDestroyableList.erase(nameRight);
            }
        }
        if(xLeft) {
            if(verifyWay((*listBlocks)[nameLeft], g1)){
                (*listBlocks)[nameLeft]->setEnabled(false);
                blockDestroyableList.erase(nameLeft);
            }
        }
}

void CollisionManager::removeBomb(std::string bombName){
        bombList.erase(bombName);
}
bool CollisionManager::verifyCollisionWithBlocks(GameObject* g1){
        for(std::pair<std::string, GameObject *>  destroyable : blockDestroyableList) {
                if(verifyCollision(destroyable.second, g1)) {
                        return true;
                }
        }
        for(std::pair<std::string, GameObject *> undestroyable : blockUndestroyableList) {
                if(verifyCollision(undestroyable.second, g1)) {
                        return true;
                }
        }
        for(std::pair<std::string, GameObject *> bomb : bombList) {
                if(verifyCollision(bomb.second, g1)) {
                        return true;
                }
        }
        return false;
}

bool CollisionManager::verifyCollisionWithBlocks(GameObject* g1, int x, int y){

        for(std::pair<std::string, GameObject *> destroyable : blockDestroyableList) {
                if(verifyCollision(destroyable.second, g1, x, y)) {
                        return true;
                }
        }
        for(std::pair<std::string, GameObject *> undestroyable : blockUndestroyableList) {
                if(verifyCollision(undestroyable.second, g1, x, y)) {
                        return true;
                }
        }

        for(std::pair<std::string, GameObject *> bomb : bombList) {
                if(verifyCollision(bomb.second, g1)) {
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
        if( bottomA <= topB ) { return false; }
        if( topA >= bottomB ) { return false; }
        if( rightA <= leftB ) { return false; }
        if( leftA >= rightB ) { return false; }
        //If none of the sides from A are outside B
        return true;
}

bool CollisionManager::verifyCollision( GameObject* g1, GameObject* g2,int x, int y){
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
        if( bottomA <= topB ) { return false; }
        if( topA >= bottomB ) { return false; }
        if( rightA <= leftB ) { return false; }
        if( leftA >= rightB ) { return false; }
        //If none of the sides from A are outside B
        return true;
}

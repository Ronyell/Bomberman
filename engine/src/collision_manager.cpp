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


        if ((int)g1->getPositionY() == (int)g2->getPositionY()){
            if((int)g1->getPositionX() > (int)g2->getPositionX()){
                for(int i = g2->getPositionX(); i <= g1-> getPositionX(); i += g1->getWidth()){
                    std::unordered_map<std::string, GameObject *>::iterator search;
                    search = blockUndestroyableList.find("block_undestroyable" + std::to_string(i) + " " + std::to_string((int)g1->getPositionY()));
                    if(search != blockUndestroyableList.end()){
                        isWay = verifyCollision(search->second, g2);
                        WARN(isWay);
                    }
                }
            }else{
                for(int i = g2->getPositionX() + g1->getWidth(); i >= g1-> getPositionX(); i -= g1->getWidth()){
                    std::unordered_map<std::string, GameObject *>::iterator search;
                    search = blockUndestroyableList.find("block_undestroyable" + std::to_string(i) + " " + std::to_string((int)g1->getPositionY()));
                    if(search != blockUndestroyableList.end()){
                        isWay = verifyCollision(search->second, g2);
                    }
                }
            }
        }else{
            if((int)g1->getPositionY() > (int)g2->getPositionY()){

            }else{

            }
        }
        return isWay;
}


// void CollisionManager::verifyBlocksDestroyable(GameObject* g1){
//         std::vector<std::string> names;
//         bool isWay = false;
//
//         for(std::pair<std::string, GameObject *>  destroyable : blockDestroyableList) {
//                 if(verifyCollision(destroyable.second, g1)) {
//                     isWay = false;
//                     for(std::pair<std::string, GameObject *>  undestroyable : blockUndestroyableList)
//                         if(undestroyable->getPositionX() == destroyable->getPositionX()){
//                             int mUndestroyable = abs(undestroyable->getPositionY() - g1->getPositionY());
//                             int mDestroyable = abs(destroyable->getPositionY() - g1->getPositionY());
//
//                             if(mUndestroyable < mDestroyable){
//
//                             }
//                         }else if(undestroyable->getPositionY() == destroyable->getPositionY()){
//                             int mUndestroyable = abs(undestroyable->getPositionX() - g1->getPositionX());
//                             int mDestroyable = abs(destroyable->getPositionX() - g1->getPositionX());
//
//                         }
//                 }
//                 if(isWay){
//                     names.push_back(destroyable.first);
//                 }
//         }
//
//         for(std::string name : names) {
//                 blockDestroyableList.erase(name);
//         }
//
// }

void CollisionManager::verifyBlocksDestroyable(GameObject* g1, std::unordered_map<std::string, GameObject*> * listBlocks, int xPlus, int yPlus){
        std::string name;
        bool collided = false;
        bool isWay = false;
        int x = 0, y = 0;

        for(std::pair<std::string, GameObject *>  destroyable : *listBlocks) {
                if(verifyCollision(destroyable.second, g1)) {
                        if(!collided) {
                                name = destroyable.first;
                                x = destroyable.second->getPositionX();
                                y = destroyable.second->getPositionY();
                                collided = true;
                        }else{
                                int yActualDestroyable = abs(y - g1->getPositionY() - yPlus);
                                int yCandidateDestroyable = abs(destroyable.second->getPositionY() - g1->getPositionY() - yPlus);

                                int xActualDestroyable = abs(x - g1->getPositionX() - xPlus);
                                int xCandidateDestroyable = abs(destroyable.second->getPositionX() - g1->getPositionX() - xPlus);

                                int xDistance = abs(xActualDestroyable - xCandidateDestroyable);
                                int yDistance = abs(yActualDestroyable - yCandidateDestroyable);
                                if(yDistance > xDistance) {
                                        if(yActualDestroyable > yCandidateDestroyable) {
                                                name = destroyable.first;
                                        }

                                }else{
                                        if(xActualDestroyable > xCandidateDestroyable) {
                                                name = destroyable.first;
                                        }
                                }
                        }
                }
        }

        if(collided){
            isWay = verifyWay((*listBlocks)[name], g1);
        }

        if(collided && !isWay) {
                (*listBlocks)[name]->setEnabled(false);
                blockDestroyableList.erase(name);
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

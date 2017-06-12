#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include <vector>
#include "engine.hpp"
#include "game_object.hpp"

using namespace engine;

class CollisionManager{
public:
    bool verifyCollisionWithBlocks(GameObject* g);
    bool verifyCollisionWithBlocks(GameObject* g1, int x, int y);
    bool verifyCollision(GameObject* g1, GameObject* g2);
    bool verifyCollision( GameObject* g1, GameObject* g2 ,int x, int y);
    bool verifyWay(GameObject* g1, GameObject* g2);
    void addBlockDestroyable(std::string blockName, GameObject* g);
    void removeBlockDestroyable(std::string blockName);
    void addBlockUndestroyable(std::string blockName, GameObject* g);
    void addBomb(std::string bombName, GameObject* g);
    void removeBomb(std::string bombName);
    void verifyBlocksDestroyable(GameObject* g1);
    void verifyBlocksDestroyable(GameObject* g1, std::unordered_map<std::string, GameObject*> * listBlocks, int range);
    void resetLists();
    static CollisionManager instance;
private:
    std::unordered_map<std::string, GameObject*> blockDestroyableList;
    std::unordered_map<std::string, GameObject*> blockUndestroyableList;
    std::unordered_map<std::string, GameObject*> bombList;
    // std::unordered_map<std::string, GameObject*> explosionList;

};

#endif

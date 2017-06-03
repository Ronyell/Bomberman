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
    void addBlockDestroyable(GameObject* g);
    void addBlockUndestroyable(GameObject* g);
    void resetLists();
    static CollisionManager instance;
private:
    std::vector<GameObject*> blockDestroyableList;
    std::vector<GameObject*> blockUndestroyableList;
};

#endif

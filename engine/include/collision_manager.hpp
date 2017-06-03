#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include <vector>
#include "engine.hpp"
#include "game_object.hpp"

using namespace engine;

class CollisionManager{
public:
    bool verifyCollisionWithWalls(GameObject* g);
    bool verifyCollisionWithEnemies(GameObject* g);
    GameObject* verifyCollisionWithPapers(GameObject* g);
    GameObject* verifyCollisionWithSwitches(GameObject* g);
    bool verifyCollision(GameObject* g1, GameObject* g2);
    void addBlockDestroyable(GameObject* g);
    void addBlockUndestroyable(GameObject* g);
    void resetLists();
    static CollisionManager instance;
private:
    std::vector<GameObject*> blockDestroyableList;
    std::vector<GameObject*> blockUndestroyableList;
};

#endif

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "wall.hpp"
#include "game_object.hpp"
#include "guard.hpp"
#include "block_undestroyable.hpp"
#include "block_destroyable.hpp"

#include <vector>

using namespace engine;

class GameScene: public Scene{
public:
    GameScene(int id);
    ~GameScene();
    void load();
    void draw();
    void update(double timeElapsed);
    void unload();
    void loadLevelDesign();
    void excludeBlockDestroyable();
private:
    std::unordered_map<std::string, GameObject*> blockUndestroyableList;
    std::unordered_map<std::string, GameObject*> blockDestroyableList;
    // std::unordered_map<std::string, GameObject*> gameObjectsList;
    Player * player;

};

#endif

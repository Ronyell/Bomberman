#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "button.hpp"
#include "game_object.hpp"
#include "block_undestroyable.hpp"
#include "block_destroyable.hpp"
#include "ground.hpp"
#include "color.hpp"
#include "audio.hpp"


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
    void selectAction();
private:
    std::unordered_map<std::string, GameObject*> blockUndestroyableList;
    std::unordered_map<std::string, GameObject*> blockDestroyableList;
    std::vector<std::pair<int, GameObject*>> texts;
    std::vector<std::pair<int, GameObject*>> menuList;
    std::vector<GameObject*> groundList;
    std::vector<GameObject*> treeList;
    Audio * background_music;
    Color * select;
    Color * notSelect;
    int selectButton;
    Player * player;

};

#endif

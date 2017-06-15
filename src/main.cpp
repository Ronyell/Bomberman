#include <iostream>

#include "engine.hpp"
#include "game_scene.hpp"

using namespace engine;


int main(int, char**){
    loadEngine();
    GameScene* gameScene = new GameScene(0);

    getSceneManager()->addScene(gameScene);

    getSceneManager()->loadScene(0);

    run();
    return 0;
}

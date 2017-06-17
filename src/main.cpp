#include <iostream>

#include "engine.hpp"
#include "game_scene.hpp"
#include "menu_scene.hpp"


using namespace engine;


int main(int, char**){
    loadEngine();
    MenuScene* menuScene = new MenuScene(0);
    GameScene* gameScene = new GameScene(1);

    getSceneManager()->addScene(menuScene);
    getSceneManager()->addScene(gameScene);

    getSceneManager()->loadScene(0);

    run();
    return 0;
}

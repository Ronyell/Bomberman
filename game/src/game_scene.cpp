#include "game_scene.hpp"
#include "player.hpp"
#include "scene.hpp"
#include "engine.hpp"
#include "ground.hpp"
#include "collision_manager.hpp"
#include "audio.hpp"
#include "block_undestroyable.hpp"
#include "block_destroyable.hpp"

#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace engine;

GameScene::GameScene(int id) : Scene(id){
    select = new Color(150, 10, 10, 0);
    notSelect = new Color(100, 100, 100, 0);
    selectButton = 1;
}

GameScene::~GameScene(){
}

void GameScene::draw(){

        for(GameObject * ground : groundList){
            (*ground).draw();
        }


        for(GameObject * gameObject: treeList){
                (*gameObject).draw();
        }

        std::vector<std::pair<std::string, GameObject*>> listBlocksUndestroyable(blockUndestroyableList.begin(), blockUndestroyableList.end());
        std::sort(listBlocksUndestroyable.begin(), listBlocksUndestroyable.end(),[](std::pair<std::string, GameObject*> const lhs, std::pair<std::string, GameObject*> const rhs){ return lhs.second->getPositionY() < rhs.second->getPositionY(); });

        for(std::pair<std::string, GameObject *> gameObject : listBlocksUndestroyable) {
                (*gameObject.second).draw();
        }

        for(std::pair<std::string, GameObject *> gameObject : blockDestroyableList) {
                (*gameObject.second).draw();
        }
        player->draw();
        for(std::pair<int, GameObject *> text : texts) {
                if(player->firstIsDead() && player->secondIsDead()) {
                    if(text.first == 3){
                        text.second->draw();
                    }
                }else if(player->firstIsDead()) {
                    if(text.first == 2){
                        text.second->draw();
                    }
                }else if(player->secondIsDead()) {
                    if(text.first == 1){
                        text.second->draw();
                    }
                }
        }

        if(player->firstIsDead() || player->secondIsDead()){
            for(auto gameObject : menuList) {
                (gameObject.second)->draw();
            }
        }
}

void GameScene::update(double timeElapsed){
        for(std::pair<std::string, GameObject *> gameObject : blockUndestroyableList) {
                (*gameObject.second).update(timeElapsed);
        }

        for(std::pair<std::string, GameObject *> gameObject : blockDestroyableList) {
                (*gameObject.second).update(timeElapsed);
        }
        player->update(timeElapsed);
        excludeBlockDestroyable();

        if(player->firstIsDead() || player->secondIsDead()){
            selectAction();

            for(auto gameObject : menuList) {
                    if(typeid(*gameObject.second) == typeid(Button)) {
                            if(gameObject.first == selectButton) {
                                    ((Button *)(gameObject.second))->setTextColor(select);
                            }else{
                                    ((Button *)(gameObject.second))->setTextColor(notSelect);
                            }
                    }

                    (*gameObject.second).update(timeElapsed);
            }
        }
}

void GameScene::load(){
        loadLevelDesign();

        texts.push_back(std::pair<int, GameObject*>(1,new Button("assets/fonts/font.ttf", 300, 10, 500, 500, "Player 1 Win", 50)));
        texts.push_back(std::pair<int, GameObject*>(2,new Button("assets/fonts/font.ttf", 300, 10, 500, 500, "Player 2 Win", 50)));
        texts.push_back(std::pair<int, GameObject*>(3,new Button("assets/fonts/font.ttf", 300, 10, 500, 500, "Draw Game", 50)));

        menuList.push_back(std::pair<int, GameObject*>(1, new Button("assets/fonts/font.ttf", 10, 10, 500, 500, "Menu", 30)));
        menuList.push_back(std::pair<int, GameObject*>(2,new Button("assets/fonts/font.ttf", 860, 10, 500, 500, "Exit", 30)));

        background_music = new Audio("assets/sounds/stage_one_music.wav", "MUSIC");
        background_music->play(0);

        std::pair <int, int> player1position (840, 510);
        std::pair <int, int> player2position (40, 120);

        player = (new Player(player1position, player2position));

        for(int y = 0; y < 600; y+=128){
            for(int x = 0; x < 900; x+=128){
                groundList.push_back(new Ground("assets/sprites/cenary/grass.png", x, y, 128, 128));
            }
        }

        for(int x = -50; x <= 900; x+=50){
            int y = 0;
            if(x % 100 == 0){
                y = -30;
            }else{
                y = -60;
            }
            treeList.push_back(new Ground("assets/sprites/cenary/treetop.png", x, y, 128, 128));
        }

        for(std::pair<std::string, GameObject *>  destroyable : blockDestroyableList) {
                CollisionManager::instance.addBlockDestroyable(destroyable.first, destroyable.second);
        }

        for(std::pair<std::string, GameObject *>  undestroyable : blockUndestroyableList) {
                CollisionManager::instance.addBlockUndestroyable(undestroyable.first, undestroyable.second);
        }

}

void GameScene::excludeBlockDestroyable(){
        player->verifyBlocksDestroyable( &blockDestroyableList);
        std::vector<std::string> names;

        for(std::pair<std::string, GameObject *> gameObject : blockDestroyableList) {
                if(((BlockDestroyable*)(gameObject.second))->getIsDestroyed()) {
                        names.push_back(gameObject.first);
                }
        }
        for(std::string name : names) {
                blockDestroyableList.erase(name);
        }
}

void GameScene::unload(){
        //CollisionManager::instance.resetLists();
        //gameObjectsList.clear();
}

void GameScene::loadLevelDesign(){
        int x = 0, y = 0;

        std::fstream levelDesign("assets/sprites/cenary/map");
        if(not levelDesign.is_open()) {
                printf("Level design of stage can't be opened\n");
                exit(-1);
        }
        std::string line;
        int indexObject;
        while(std::getline(levelDesign, line)) {
                std::stringstream numberObject(line);

                while(numberObject >> indexObject) {
                        if(indexObject == 1) {
                                blockUndestroyableList["block_undestroyable" + std::to_string(x) + " " + std::to_string(y)] = (new BlockUndestroyable("assets/sprites/cenary/barrel.png",x,y,40,40));
                        }else if(indexObject == 2) {
                                blockDestroyableList["block_destroyable" + std::to_string(x) + " " + std::to_string(y)] = (new BlockDestroyable("assets/sprites/cenary/block_destroyable.png",x,y,40,40));
                        }
                        numberObject.ignore(1, ',');

                        x+=40;
                }

                y+=40;
                x=0;
        }

        levelDesign.close();
}


void GameScene::selectAction(){
    if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_LEFT) || InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_A)) {
            selectButton--;
            if(selectButton <= 0) {
                    selectButton = 2;
            }
    }
    else if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_RIGHT) || InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_D)) {
            selectButton++;
            if(selectButton > 2) {
                    selectButton = 1;
            }
    }

    if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_ENTER) || InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_SPACE) || InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_P)) {
            switch(selectButton) {
            case 1:
                    background_music->pause();
                    getSceneManager()->loadScene(0);
                    break;
            case 2:
                    InputManager::instance.setQuitRequest(true);
                    break;
            default:
                    break;
            }

    }
}

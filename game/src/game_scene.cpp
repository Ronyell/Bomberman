#include "game_scene.hpp"
#include "player.hpp"
#include "scene.hpp"
#include "engine.hpp"
#include "wall.hpp"
#include "ground.hpp"
#include "collision_manager.hpp"
#include "guard.hpp"
#include "paper.hpp"
#include "door_system.hpp"
#include "audio.hpp"
#include "block_undestroyable.hpp"
#include "block_destroyable.hpp"

#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace engine;

GameScene::GameScene(int id) : Scene(id){
}

GameScene::~GameScene(){}

void GameScene::draw(){
    for(std::pair<std::string, GameObject *> gameObject: blockUndestroyableList) {
        (*gameObject.second).draw();
    }
    for(std::pair<std::string, GameObject *> gameObject: blockDestroyableList) {
        (*gameObject.second).draw();
    }
    player->draw();
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
}

void GameScene::load(){
    loadLevelDesign();

    Audio background_music = Audio("assets/sounds/stage_one_music.wav", "MUSIC");
    background_music.play(0);

    std::pair <int, int> player1position (840, 510);
    std::pair <int, int> player2position (40, 120);

    player = (new Player(player1position, player2position));
    for(std::pair<std::string, GameObject *>  destroyable : blockDestroyableList) {
        CollisionManager::instance.addBlockDestroyable(destroyable.first, destroyable.second);
    }

    for(std::pair<std::string, GameObject *>  undestroyable : blockUndestroyableList) {
        CollisionManager::instance.addBlockUndestroyable(undestroyable.first, undestroyable.second);
    }
    // for(std::pair<std::string, GameObject *> gameObject: gameObjectsList){
    //     if(typeid(*gameObject.second) == typeid(BlockUndestroyable)){
    //         CollisionManager::instance.addBlockUndestroyable(gameObject.first, gameObject.second);
    //     }else if(typeid(*gameObject.second) == typeid(BlockDestroyable)){
    //         CollisionManager::instance.addBlockDestroyable(gameObject.first, gameObject.second);
    //     }//else if(typeid(*gameObject) == typeid(Paper)){
    //     //     CollisionManager::instance.addPaper(gameObject);
    //     // }else if(typeid(*gameObject) == typeid(DoorSystem)){
    //     //     CollisionManager::instance.addDoor(((DoorSystem*)(gameObject))->getDoor());
    //     //     CollisionManager::instance.addSwitch(((DoorSystem*)(gameObject))->getSwitch());
    //     // }
    // }

}

void GameScene::excludeBlockDestroyable(){
    player->verifyBlocksDestroyable( &blockDestroyableList);
    std::vector<std::string> names;

    for(std::pair<std::string, GameObject *> gameObject : blockDestroyableList) {
        if(!gameObject.second->isEnabled()){
            names.push_back(gameObject.first);
        }
    }
    for(std::string name:names){
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
	if(not levelDesign.is_open()){
		printf("Level design of stage can't be opened\n");
		exit(-1);
	}
	std::string line;
    int indexObject;
	while(std::getline(levelDesign, line)){
        std::stringstream numberObject(line);

        // WARN(numberObject.str());

        while(numberObject >> indexObject){
                if(indexObject == 1){
                    blockUndestroyableList["block_undestroyable" + std::to_string(x) + " " + std::to_string(y)] = (new BlockUndestroyable("assets/sprites/cenary/block_undestroyable.png",x ,y ,40,40));
                }else if(indexObject == 2){
                    blockDestroyableList["block_destroyable" + std::to_string(x) + " " + std::to_string(y)] = (new BlockDestroyable("assets/sprites/cenary/block_destroyable.png",x ,y ,40,40));
                }
			    numberObject.ignore(1, ',');

                x+=40;
		}

        y+=40;
        x=0;
 	}

	levelDesign.close();
}

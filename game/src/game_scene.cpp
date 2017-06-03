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


#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace engine;

GameScene::GameScene(int id) : Scene(id){

}

GameScene::~GameScene(){}

void GameScene::draw(){
    for(auto gameObject : gameObjectsList) {
        (*gameObject).draw();
    }
}

void GameScene::update(double timeElapsed){
    for(auto gameObject : gameObjectsList) {
        (*gameObject).update(timeElapsed);
    }
    // verifyWinOrLose();
}

void GameScene::load(){
    loadLevelDesign();
    Audio background_music = Audio("assets/sounds/stage_one_music.wav", "MUSIC");
    background_music.play(0);

    std::pair <int, int> player1position (10, 500);
    std::pair <int, int> player2position (30, 510);

    gameObjectsList.push_back(new Player(player1position, player2position));



    // for(auto gameObject: gameObjectsList){
    //     if(typeid(*gameObject) == typeid(Wall)){
    //         CollisionManager::instance.addWall(gameObject);
    //     }else if(typeid(*gameObject) == typeid(Guard)){
    //         CollisionManager::instance.addEnemy(gameObject);
    //     }else if(typeid(*gameObject) == typeid(Paper)){
    //         CollisionManager::instance.addPaper(gameObject);
    //     }else if(typeid(*gameObject) == typeid(DoorSystem)){
    //         CollisionManager::instance.addDoor(((DoorSystem*)(gameObject))->getDoor());
    //         CollisionManager::instance.addSwitch(((DoorSystem*)(gameObject))->getSwitch());
    //     }
    // }

}
void GameScene::unload(){
    CollisionManager::instance.resetLists();
    gameObjectsList.clear();
}

void GameScene::loadLevelDesign(){
	// double x, y, width, height;

	std::fstream levelDesign("assets/sprites/cenary/map");
	if(not levelDesign.is_open()){
		printf("Level design of stage can't be opened\n");
		exit(-1);
	}
	std::string line;
    int indexObject;
	while(std::getline(levelDesign, line)){
        std::stringstream numberObject(line);
        numberObject.ignore(1, ',');

        // WARN(numberObject.str());

        while(numberObject >> indexObject){
                if(indexObject == 1){

                }else if(indexObject == 2){

                }
			    numberObject.ignore(1, ',');
		}

 	}

	levelDesign.close();
}

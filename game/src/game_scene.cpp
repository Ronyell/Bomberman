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
    Audio background_music = Audio("assets/sounds/stage_one_music.wav", "MUSIC");
    background_music.play(0);
    for(int i=0; i<=960; i+=20){
        for(int j=0; j<=600; j+=20){
            gameObjectsList.push_back(new Ground("assets/sprites/cenary/chao.png", i, j, 20, 20));
        }
    }
    for(int i=0; i<=960; i+=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", i, 0, 5, 5));
    }
    for(int i=0; i<=960; i+=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", i, 595, 5, 5));
    }
    for(int j=0; j<=600; j+=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 955, j, 5, 5));
    }


    std::pair <int, int> player1position (10, 500);
    std::pair <int, int> player2position (30, 510);

    gameObjectsList.push_back(new Player(player1position, player2position));

    gameObjectsList.push_back(new Guard("assets/sprites/seguranca_sheet.png", 900, 10, 40, 40, "down"));
    gameObjectsList.push_back(new Guard("assets/sprites/seguranca_sheet.png", 220, 100, 40, 40, "right"));

    gameObjectsList.push_back(new Paper("assets/sprites/papeis(19X21).png", 100,300, 19, 21));
    gameObjectsList.push_back(new Paper("assets/sprites/papeis(19X21).png", 800,300, 19, 21));

    for(int i=0; i<=400; i+=20){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede2.png", i, 400, 20, 65));
    }
    for(int j=400; j>=320; j-=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 415, j, 5, 5));
    }

    for(int j=260; j>=180; j-=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 415, j, 5, 5));
    }

    for(int i=395; i>=0; i-=20){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede2.png", i, 180, 20, 65));
    }
    gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede2.png", 0, 180, 20, 65));

    for(int j=400; j>=180; j-=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 0, j, 5, 5));
    }

    for(int j=180; j>=120; j-=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 200, j, 5, 5));
    }

    for(int j=60; j>=0; j-=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 200, j, 5, 5));
    }
    for(int i=180; i>=0; i-=20){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede2.png", i, 0, 20, 65));
    }
    for(int j=180; j>=0; j-=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 0, j, 5, 5));
    }
    for(int i=835; i>=535; i-=20){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede2.png", i, 200, 20, 65));
    }
    for(int i=835; i>=535; i-=20){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede2.png", i, 0, 20, 65));
    }
    for(int j=0; j<=395; j+=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 535, j, 5, 5));
    }
    for(int i=535; i<=635; i+=20){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede2.png", i, 400, 20, 65));
    }
    gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede2.png", 640, 400, 20, 65));
    for(int i=720; i<=855; i+=20){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede2.png", i, 400, 20, 65));
    }
    for(int j=400; j>=140; j-=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 855, j, 5, 5));
    }
    for(int j=75; j>=0; j-=5){
        gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_cima1.png", 855, j, 5, 5));
    }

    //Door edge 1
    gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_door.png", 200, 5, 5, 65));

    //Door edge 2
    gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_door.png", 415, 200, 5, 65));

    //Door edge 3
    gameObjectsList.push_back(new Wall("assets/sprites/cenary/parede_door.png", 855, 20, 5, 65));

    std::pair<int,int> doorOnePosition (360, 270);
    std::pair<int,int> switchOnePosition (150, 150);

    std::pair<int,int> doorTwoPosition (660, 460);
    std::pair<int,int> switchTwoPosition (600, 150);

    gameObjectsList.push_back(new DoorSystem(doorOnePosition,switchOnePosition));
    gameObjectsList.push_back(new DoorSystem(doorTwoPosition,switchTwoPosition));


    for(auto gameObject: gameObjectsList){
        if(typeid(*gameObject) == typeid(Wall)){
            CollisionManager::instance.addWall(gameObject);
        }else if(typeid(*gameObject) == typeid(Guard)){
            CollisionManager::instance.addEnemy(gameObject);
        }else if(typeid(*gameObject) == typeid(Paper)){
            CollisionManager::instance.addPaper(gameObject);
        }else if(typeid(*gameObject) == typeid(DoorSystem)){
            CollisionManager::instance.addDoor(((DoorSystem*)(gameObject))->getDoor());
            CollisionManager::instance.addSwitch(((DoorSystem*)(gameObject))->getSwitch());
        }
    }

}
void GameScene::unload(){
    CollisionManager::instance.resetLists();
    gameObjectsList.clear();
}

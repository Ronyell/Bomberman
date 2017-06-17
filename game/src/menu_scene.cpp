#include "menu_scene.hpp"
#include "button.hpp"

#include <typeinfo>
#include <iostream>

using namespace engine;

MenuScene::MenuScene(int id) : Scene(id){
        selectButton = 1;
        select = new Color(100, 10, 10, 0);
        notSelect = new Color(0, 0, 0, 0);
        background = new Sprite("assets/sprites/background.png");
}

MenuScene::~MenuScene(){
}

void MenuScene::draw(){
        background->draw(0,0);

        for(auto gameObject : gameObjectsList) {
                (*gameObject.second).draw();
        }
}

void MenuScene::update(double timeElapsed){
        selectAction();

        for(auto gameObject : gameObjectsList) {
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

void MenuScene::selectAction(){
        if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_UP)) {
                selectButton--;
                if(selectButton <= 0) {
                        selectButton = 2;
                }
        }
        else if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_DOWN)) {
                selectButton++;
                if(selectButton > 2) {
                        selectButton = 1;
                }
        }

        if(InputManager::instance.isKeyTriggered(InputManager::KeyPress::KEY_PRESS_ENTER)) {
                switch(selectButton) {
                case 1:
                        getSceneManager()->loadScene(1);
                        break;
                case 2:
                        InputManager::instance.setQuitRequest(true);
                        break;
                default:
                        break;
                }

        }
}

void MenuScene::load(){
        gameObjectsList.push_back(std::pair<int, GameObject*>(1, new Button("assets/fonts/font.ttf", 390, 400, 500, 500, "Start", 50)));
        gameObjectsList.push_back(std::pair<int, GameObject*>(2,new Button("assets/fonts/font.ttf", 400, 500, 500, 500, "Exit", 50)));
}

void MenuScene::unload(){
}

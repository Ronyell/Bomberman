#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "sdl2includes.hpp"
#include <unordered_map>

namespace engine{

    class InputManager{

    public:
        enum KeyPress{
            KEY_PRESS_UP = SDLK_UP,
            KEY_PRESS_DOWN = SDLK_DOWN,
            KEY_PRESS_RIGHT = SDLK_RIGHT,
            KEY_PRESS_LEFT = SDLK_LEFT,
            KEY_PRESS_SPACE = SDLK_SPACE,
            KEY_PRESS_W = SDLK_w,
            KEY_PRESS_A = SDLK_a,
            KEY_PRESS_S = SDLK_s,
            KEY_PRESS_D = SDLK_d,
            KEY_PRESS_P = SDLK_p
        };

        static InputManager instance;
        void update(SDL_Event event);
        bool getQuitRequest();
        void Update(void);

        bool isKeyTriggered(int iKeyCode);
        bool isKeyPressed(int iKeyCode);
        bool isKeyReleased(int iKeyCode);
        bool isSpace();

    private:
        InputManager(): quitRequest(false){}
        bool quitRequest;
        std::unordered_map<int, bool> keyActive;
        std::unordered_map<int, bool> keyPrevious;
    };
}
#endif

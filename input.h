#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_gamepad.h>


//listen if controller plugged in, maybe use SwitchToInput() for easier transition between controller and kb+m

class InputManager{
    public:
        enum class InputMode{KEYBOARD_MOUSE, GAMEPAD};
        void handleInput(const SDL_Event *event);

        bool moveUp = false;
        bool moveDown = false;
        bool moveRight = false;
        bool moveLeft = false;
        bool isGamepadConnected() const;
    
    private:
        SDL_Gamepad *gamepad = nullptr;
        InputMode currentMode = InputMode::KEYBOARD_MOUSE;
};


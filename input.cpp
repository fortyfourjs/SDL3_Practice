#include "input.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_gamepad.h>

void InputManager::handleInput(const SDL_Event *event){
    if(!event) return;
    if(event->type == SDL_EVENT_KEY_DOWN){
        currentMode = InputMode::KEYBOARD_MOUSE;
        switch(event->key.key){
            case SDLK_UP:
                moveUp = true;
                break;
            case SDLK_DOWN:
                moveDown = true;
                break;
            case SDLK_LEFT:
                moveLeft = true;
                break;
            case SDLK_RIGHT:
                moveRight = true;
                break;
        }
    }
    if(event->type == SDL_EVENT_KEY_UP){
        currentMode = InputMode::KEYBOARD_MOUSE;
        switch(event->key.key){
            case SDLK_UP:
                moveUp = false;
                break;
            case SDLK_DOWN:
                moveDown = false;
                break;
            case SDLK_LEFT:
                moveLeft = false;
                break;
            case SDLK_RIGHT:
                moveRight = false;
                break;
        }
    }
    if(event->type == SDL_EVENT_GAMEPAD_ADDED){
        gamepad = SDL_OpenGamepad(event->gdevice.which);
        currentMode = InputMode::GAMEPAD;
        SDL_Log("Controller running");
    }
    if(event->type == SDL_EVENT_GAMEPAD_REMOVED){
        if (gamepad && event->gdevice.which == SDL_GetGamepadID(gamepad)){ //checks if disconnected device is the actual controller.
            SDL_CloseGamepad(gamepad);
            gamepad = nullptr;
            SDL_Log("Controller disconnected");
            currentMode = InputMode::KEYBOARD_MOUSE;
        }
    }
    if(event->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN){
        currentMode = InputMode::GAMEPAD;
        switch(event->gbutton.button){
            case SDL_GAMEPAD_BUTTON_DPAD_UP:
                moveUp = true;
                break;
            case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
                moveDown = true;
                break;
            case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
                moveLeft = true;
                break;
            case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
                moveRight = true;
                break;
        }
    }
    if(event->type == SDL_EVENT_GAMEPAD_BUTTON_UP){
        currentMode = InputMode::GAMEPAD;
        switch(event->gbutton.button){
            case SDL_GAMEPAD_BUTTON_DPAD_UP:
                moveUp = false;
                break;
            case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
                moveDown = false;
                break;
            case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
                moveLeft = false;
                break;
            case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
                moveRight = false;
                break;
        }
    }
}

bool InputManager::isGamepadConnected() const{
    return gamepad != nullptr;
}
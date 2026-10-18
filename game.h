#pragma once
#include <SDL3/SDL.h>
#include "board.h"
#include "input.h"


class Game{
    public:
        Game() = default;
        ~Game() = default;

        bool init(const char* title, int width, int height);
        void handleEvent(const SDL_Event* event);
        void update(float deltaTime);
        void render();
        void cleanup();

        SDL_Renderer* getRenderer() const{
            return renderer;
        }
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
		SDL_Texture* spriteTexture = nullptr;
        Board board;
        InputManager inputManager;

        float groundHeight = 50.0f;
        
        int WIN_HEIGHT = 800;
        int WIN_WIDTH = 600;
    };

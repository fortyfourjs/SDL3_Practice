#pragma once
#include <SDL3/SDL.h>
#include "input.h"

class Board{
    public:
        static constexpr int WIDTH = 10;
        static constexpr int HEIGHT = 20;
        static constexpr int CELL_SIZE = 90;
       
        float x{10.0f};
        float y{10.0f};
        float velocityX{0.0f};
        float velocityY{0.0f};
        float groundY;

        void update(float deltaTime, const InputManager& input);
        void render(SDL_Renderer* renderer, SDL_Texture* texture);
        
        
};
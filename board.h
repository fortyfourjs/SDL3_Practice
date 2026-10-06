#pragma once
#include <SDL3/SDL.h>

class Board{
    public:
        static constexpr int WIDTH = 10;
        static constexpr int HEIGHT = 20;
        static constexpr int CELL_SIZE = 30;
        
        bool moveUp = false;
        bool moveDown = false;
        bool moveRight = false;
        bool moveLeft = false;

        float x{100.0f};
        float y{100.0f};
        float velocityX{0.0f};
        float velocityY{0.0f};

        void update(float deltaTime);
        void handleInput(const SDL_Event *event);
        void render(SDL_Renderer* renderer);
        
        
};
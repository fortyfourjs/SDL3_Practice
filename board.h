#include <SDL3/SDL.h>

class Board{
    public:
        static constexpr int WIDTH = 10;
        static constexpr int HEIGHT = 20;
        static constexpr int CELL_SIZE = 30;

        void render(SDL_Renderer* renderer);
};
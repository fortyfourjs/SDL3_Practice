#include <SDL3/SDL.h>
#include "board.h"

void Board::render(SDL_Renderer* renderer){
    //seteaza bg 
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

    //dreptunghi
    SDL_FRect dreptunghi = { 100.0f, 100.0f, (float)Board::CELL_SIZE, (float)Board::CELL_SIZE};

    //deseneaza dreptunghiul
    SDL_RenderFillRect(renderer, &dreptunghi);

}


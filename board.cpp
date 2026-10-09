#include <SDL3/SDL.h>
#include "board.h"
#include "input.h"

void Board::update(float deltaTime, const InputManager& input){
    if(input.moveUp == true){
        velocityY = -200.0f;
    }else if(input.moveDown == true){
        velocityY = 200.0f;
    }else{
        velocityY = 0.0f;
    }

    if(input.moveLeft == true){
        velocityX = -200.0f;
    }else if(input.moveRight == true){
        velocityX = 200.0f;
    }else{
        velocityX = 0.0f;
    }
    x += velocityX * deltaTime;
    y += velocityY * deltaTime; 
}

void Board::render(SDL_Renderer* renderer){
    //seteaza bg 
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

    //dreptunghi
    SDL_FRect dreptunghi = { x, y, (float)CELL_SIZE, (float)CELL_SIZE};

    //deseneaza dreptunghiul
    SDL_RenderFillRect(renderer, &dreptunghi);

}


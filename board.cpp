#include <SDL3/SDL.h>
#include "board.h"

void Board::update(float deltaTime){
    if(moveUp == true){
        velocityY = -200.0f;
    }else if(moveDown == true){
        velocityY = 200.0f;
    }else{
        velocityY = 0.0f;
    }

    if(moveLeft == true){
        velocityX = -200.0f;
    }else if(moveRight == true){
        velocityX = 200.0f;
    }else{
        velocityX = 0.0f;
    }
    x += velocityX * deltaTime;
    y += velocityY * deltaTime; 
}
void Board::handleInput(const SDL_Event *event){
    if(!event) return;
    
    if(event->type == SDL_EVENT_KEY_DOWN){
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
}
void Board::render(SDL_Renderer* renderer){
    //seteaza bg 
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

    //dreptunghi
    SDL_FRect dreptunghi = { x, y, (float)CELL_SIZE, (float)CELL_SIZE};

    //deseneaza dreptunghiul
    SDL_RenderFillRect(renderer, &dreptunghi);

}


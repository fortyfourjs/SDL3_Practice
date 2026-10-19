#include <SDL3/SDL.h>
#include "board.h"
#include "input.h"

void Board::init(int windowWidth, int windowHeight) {
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

    m_groundY = (float)m_windowHeight - m_groundMargin - CHARACTER_SIZE;
    m_playerY = m_groundY;

	m_playerX = ((float)m_windowWidth - CHARACTER_SIZE) / 2.0f;
}

void Board::update(float deltaTime, const InputManager& input){
    if(input.moveUp == true){
        m_playerVelocityY = -200.0f;
    }else if(input.moveDown == true){
        m_playerVelocityY = 200.0f;
    }else{
        m_playerVelocityY = 0.0f;
    }

    if(input.moveLeft == true){
        m_playerVelocityX = -200.0f;
    }else if(input.moveRight == true){
        m_playerVelocityX = 200.0f;
    }else{
        m_playerVelocityX = 0.0f;
    }
    m_playerX += m_playerVelocityX * deltaTime;
    m_playerY += m_playerVelocityY * deltaTime; 
}

void Board::render(SDL_Renderer* renderer, SDL_Texture* characterTexture){
    //dreptunghi
    SDL_FRect playerRect = { m_playerX, m_playerY, (float)CHARACTER_SIZE, (float)CHARACTER_SIZE};
    //if sprite doesnt load, draw rectangle.
    if(characterTexture == nullptr){
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &playerRect);
    }else{
        SDL_RenderTexture(renderer, characterTexture, nullptr, &playerRect);
    }
    float groundLineY = m_groundY + CHARACTER_SIZE;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderLine(renderer, 0.0f, groundLineY, (float)m_windowWidth, groundLineY);

}


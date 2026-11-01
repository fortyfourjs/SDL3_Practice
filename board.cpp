#include <SDL3/SDL.h>
#include "board.h"
#include "input.h"

void Board::init(int windowWidth, int windowHeight) {
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

    m_groundY = (float)m_windowHeight - m_groundMargin - CHARACTER_SIZE;
    m_playerY = m_groundY;

	m_playerX = ((float)m_windowWidth - CHARACTER_SIZE) / 2.0f;

    SDL_FRect platform1 = {200.0f, 400.0f, 150.0f, 20.0f};
    SDL_FRect platform2 = {300.0f, 200.0f, 100.0f, 20.0f};
    m_platforms.push_back(platform1);
    m_platforms.push_back(platform2);
}

void Board::update(float deltaTime, const InputManager& input){
    if(input.moveUp && m_isGrounded){
        m_playerVelocityY = m_jumpStrength;
        m_isGrounded = false;
    }
    m_playerVelocityY += m_gravity * deltaTime;
    m_playerY += m_playerVelocityY * deltaTime;

    if(input.moveLeft == true){
        m_playerVelocityX = -200.0f;
    }else if(input.moveRight == true){
        m_playerVelocityX = 200.0f;
    }else{
        m_playerVelocityX = 0.0f;
    }
    m_playerX += m_playerVelocityX * deltaTime;

    if(m_playerX < 0.0f){
        m_playerX = 0.0f;
    }else if(m_playerX + CHARACTER_SIZE > (float)m_windowWidth){
        m_playerX = (float)m_windowWidth - CHARACTER_SIZE;
    }

    if(m_playerY > m_groundY){
        m_playerY = m_groundY;
        m_playerVelocityY = 0.0f;
        m_isGrounded = true;
    }else{
        m_isGrounded = false;
    }
    if(m_playerY < 0.0f){
        m_playerY = 0.0f;
        m_playerVelocityY = 0.0f;
    }

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

    renderPlatform(renderer);

}

void Board::renderPlatform(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for(const auto& platform : m_platforms){
        SDL_RenderFillRect(renderer, &platform);
    }
}


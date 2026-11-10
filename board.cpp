#include <SDL3/SDL.h>
#include "board.h"
#include "input.h"

void Board::init(int windowWidth, int windowHeight) {
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

    m_groundY = (float)m_windowHeight - m_groundMargin - CHARACTER_SIZE;
    m_playerY = m_groundY;

	m_playerX = ((float)m_windowWidth - CHARACTER_SIZE) / 2.0f;
    m_maxJumps = 2;
    m_jumpsCount = 0;

    //populate platforms
    m_platforms.clear();
    MovingPlatform platform1;
    platform1.rect = {200.0f, 400.0f, 150.0f, 20.0f};
    platform1.startX = 100.0f;
    platform1.endX = 700.0f;
    platform1.speed = 100.0f;
    platform1.dirX = 1.0f;
    platform1.dirY = 0.0f;
    MovingPlatform platform2;
    platform2.rect = {300.0f, 200.0f, 100.0f, 20.0f};
    platform2.startX = 200.0f;
    platform2.endX = 1000.0f;
    platform2.speed = 150.0f;
    platform2.dirX = -1.0f;
    platform2.dirY = 0.0f;
    MovingPlatform platform3;
    platform3.rect = {200.0f, 100.0f, 120.0f, 20.0f};
    platform3.startX = 200.0f;
    platform3.endX = 200.0f;
    platform3.startY = 300.0f;
    platform3.endY = 1000.0f;
    platform3.speed = 150.0f;
    platform3.dirX = 0.0f;
    platform3.dirY = -1.0f;

    m_platforms.push_back(platform1);
    m_platforms.push_back(platform2);
    m_platforms.push_back(platform3);
}

void Board::update(float deltaTime, InputManager& input){
    for(auto& platform : m_platforms){ //updpate platform positions
        updatePlatform(&platform, deltaTime);
    }
    
    if((input.moveUp && m_isGrounded) || (input.isJumpPressed() && m_jumpsCount < m_maxJumps)){ //jump input and gravity
        m_playerVelocityY = m_jumpStrength;
        m_jumpsCount++;
        m_isGrounded = false;
        input.consumeJump();
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

    if(m_playerX < 0.0f){ //horizontal border
        m_playerX = 0.0f;
    }else if(m_playerX + CHARACTER_SIZE > (float)m_windowWidth){
        m_playerX = (float)m_windowWidth - CHARACTER_SIZE;
    }
    m_isGrounded = false;

    //platform collision
    SDL_FRect playerRect = { m_playerX, m_playerY, (float)CHARACTER_SIZE, (float)CHARACTER_SIZE};
    for(const auto& platform : m_platforms){
        if(SDL_HasRectIntersectionFloat(&playerRect, &platform.rect)){
            //landing on top
            if(m_playerVelocityY >= 0.0f){
                float prevFeetY = (m_playerY + CHARACTER_SIZE) - (m_playerVelocityY * deltaTime);
                if(prevFeetY <= platform.rect.y + 15.0f){
                    m_playerY = platform.rect.y - CHARACTER_SIZE;
                    m_playerVelocityY = 0.0f;
                    m_isGrounded = true;
                    m_jumpsCount = 0;

                    //player moves with the platform
                    m_playerX += platform.speed * platform.dirX * deltaTime;
                }
            }
            //moving up, head bonk
            else if(m_playerVelocityY < 0.0f){
                float prevHeadY = m_playerY - (m_playerVelocityY * deltaTime);
                if(prevHeadY >= platform.rect.y + platform.rect.h -15.0f){
                    m_playerY = platform.rect.y + platform.rect.h;
                    m_playerVelocityY = 0.0f;
                }
            }
        }
    }

    if(m_playerY >= m_groundY){ //ground collision
        m_playerY = m_groundY;
        m_playerVelocityY = 0.0f;
        m_isGrounded = true;
        m_jumpsCount = 0;
    }
    //top screen limit
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
void Board::updatePlatform(MovingPlatform *m_platforms, float deltaTime){
    m_platforms->rect.x += m_platforms->speed * m_platforms->dirX * deltaTime;
    m_platforms->rect.y += m_platforms->speed * m_platforms->dirY * deltaTime;

    if(m_platforms->dirX != 0.0f){
        if(m_platforms->rect.x >= m_platforms->endX){
            m_platforms->rect.x = m_platforms->endX;
            m_platforms->dirX = -1.0f;
        }else if(m_platforms->rect.x <= m_platforms->startX){
            m_platforms->rect.x = m_platforms->startX;
            m_platforms->dirX= 1.0f;
        }
    }
    if(m_platforms->dirY != 0.0f){
        if(m_platforms->rect.y >= m_platforms->endY){
            m_platforms->rect.y = m_platforms->endY;
            m_platforms->dirY = -1.0f;
        }else if(m_platforms->rect.y <= m_platforms->startY){
            m_platforms->rect.y = m_platforms->startY;
            m_platforms->dirY = 1.0f;
        }
    }
}
void Board::renderPlatform(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for(const auto& platform : m_platforms){
        SDL_RenderFillRect(renderer, &platform.rect);
    }
}


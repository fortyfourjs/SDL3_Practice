#pragma once
#include <SDL3/SDL.h>
#include "input.h"

class Board{
    public:
        static constexpr int GRID_COLS = 10;
        static constexpr int GRID_ROWS = 20;
        static constexpr int CHARACTER_SIZE = 90;

        /*player state*/
        float m_playerX{0.0f};
        float m_playerY{0.0f};
        float m_playerVelocityX{0.0f};
        float m_playerVelocityY{0.0f};
        bool  m_isGrounded = true;

        /*ground state*/
        float m_groundY{0.0f};
		float m_groundMargin{ 20.0f };
        float m_gravity{1000.0f};
        float m_jumpStrength{-300.0f};

        /*screen dimensions*/
        int m_windowWidth{0};
        int m_windowHeight{0};

		void init(int windowWidth, int windowHeight);
        void update(float deltaTime, const InputManager& input);
        void render(SDL_Renderer* renderer, SDL_Texture* characterTexture);
        
        
};
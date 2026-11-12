#pragma once
#include <SDL3/SDL.h>
#include "input.h"
#include <vector>
#include <memory>

class Entity {
    public:
        virtual ~Entity() = default;

        virtual void update(float deltaTime) = 0;
        virtual void render(SDL_Renderer* renderer) = 0;
        
        const SDL_FRect& getRect() const { return m_rect; }

        protected:
            SDL_FRect m_rect{0.0f, 0.0f, 0.0f, 0.0f};
            bool m_isDead{false};
};

class Board{
    private:
        SDL_FlipMode m_flipMode { SDL_FLIP_NONE };
        
    public:
        static constexpr int CHARACTER_SIZE = 90;
        static constexpr int MAX_JUMPS = 2;
        static constexpr float MOVE_SPEED = 200.0f;
        static constexpr float COLLISION_TOLERANCE = 15.0f;

        /*player state*/
        float m_playerX{0.0f};
        float m_playerY{0.0f};
        float m_playerVelocityX{0.0f};
        float m_playerVelocityY{0.0f};
        int   m_jumpsCount;
        bool  m_isGrounded = true;

        /*ground state*/
        float m_groundY{0.0f};
		float m_groundMargin{ 10.0f };
        float m_gravity{980.0f};
        float m_jumpStrength{-450.0f};

        /*screen dimensions*/
        int m_windowWidth{0};
        int m_windowHeight{0};

        typedef struct{
            SDL_FRect rect;
            float startX, startY;
            float endX, endY;
            float speed;
            float dirX, dirY;
        } MovingPlatform;

        std::vector<MovingPlatform> m_platforms;
        void renderPlatform(SDL_Renderer* renderer);
		void init(int windowWidth, int windowHeight);
        void update(float deltaTime, InputManager& input);
        void updatePlatform(MovingPlatform *m_platforms, float deltaTime);
        void render(SDL_Renderer* renderer, SDL_Texture* characterTexture);
        
        
};
#pragma once
#include <SDL3/SDL.h>
#include "board.h"
#include "input.h"


class Game{
    public:
        Game() = default;
        ~Game() = default;

        bool init(const char* title, int width, int height);
        void handleEvent(const SDL_Event* event);
        void update(float deltaTime);
        void render();
        void cleanup();

        SDL_Renderer* getRenderer() const{
            return m_renderer;
        }
    private:
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;
		SDL_Texture* m_characterTexture = nullptr;

        Board m_board;
        InputManager m_inputManager;

        int m_windowHeight = 800;
        int m_windowWidth = 600;
    };

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "game.h"

bool Game::init(const char* title, int width, int height) {
	m_windowWidth = width;
	m_windowHeight = height;
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	if (!SDL_CreateWindowAndRenderer(title, m_windowWidth, m_windowHeight, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer)) {
		SDL_Log("Couldn't create window: %s", SDL_GetError());
		return false;
	}
	SDL_SetRenderLogicalPresentation(m_renderer, m_windowWidth, m_windowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	m_board.init(m_windowWidth, m_windowHeight);

	m_characterTexture = IMG_LoadTexture(m_renderer, "assets/charmeleon.png");
	if (!m_characterTexture) {
		SDL_Log("Error loading texture: %s", SDL_GetError());
	}
	return true;
}
void Game::handleEvent(const SDL_Event* event) {
	m_inputManager.handleInput(event);
}
void Game::update(float deltaTime) {
	m_board.update(deltaTime, m_inputManager);
}
void Game::render() {
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	m_board.render(m_renderer, m_characterTexture);
	SDL_RenderPresent(m_renderer);
}

void Game::cleanup() {
	if (m_characterTexture) {
		SDL_DestroyTexture(m_characterTexture);
		m_characterTexture = nullptr;
	}
	if (m_renderer) {
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
	if (m_window) {
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
	SDL_Quit();
}
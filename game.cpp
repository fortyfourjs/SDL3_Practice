#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "game.h"

bool Game::init(const char* title, int width, int height) {
	WIN_WIDTH = width;
	WIN_HEIGHT = height;
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	if (!SDL_CreateWindowAndRenderer(title, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		SDL_Log("Couldn't create window: %s", SDL_GetError());
		return false;
	}
	SDL_SetRenderLogicalPresentation(renderer, WIN_WIDTH, WIN_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	spriteTexture = IMG_LoadTexture(renderer, "assets/charmeleon.png");
	if (!spriteTexture) {
		SDL_Log("Error loading texture: %s", SDL_GetError());
	}
	return true;
}
void Game::handleEvent(const SDL_Event* event) {
	inputManager.handleInput(event);
}
void Game::update(float deltaTime) {
	board.update(deltaTime, inputManager);
}
void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	board.render(renderer, spriteTexture);

	float groundY = (float)WIN_HEIGHT - groundHeight;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderLine(renderer, 0.0f, groundY, (float)WIN_WIDTH, groundY);

	SDL_RenderPresent(renderer);
}

void Game::cleanup() {
	if (spriteTexture) {
		SDL_DestroyTexture(spriteTexture);
		spriteTexture = nullptr;
	}
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	SDL_Quit();
}
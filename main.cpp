#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "game.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

static Game game;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	SDL_SetAppMetadata("SDL3 TEst", "1.0", "com.example.sdl3test");
	if (!game.init("SDL3 Test", SCREEN_WIDTH, SCREEN_HEIGHT)) {
		return SDL_APP_FAILURE;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
	game.handleEvent(event);
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	static double lastTime = 0.0;
	const double now = ((double)SDL_GetTicks()) / 1000.0;
	float deltaTime = (float)(now - lastTime);
	lastTime = now;

	game.update(deltaTime);
	game.render();

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	game.cleanup();
}
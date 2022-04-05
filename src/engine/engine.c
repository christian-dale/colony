#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include "../engine/config.h"
#include "../options.h"
#include "../engine/audio.h"
#include "../engine/engine.h"
#include "../engine/sprite.h"
#include "../ecs/entity.h"
#include "../world.h"

Engine engine;

int Engine_Init() {
	Config_Load();

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer) < 0) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}

	engine.options.gameState = GameState_Main;

	srand(time(NULL));
	Audio_Init();
	Sprite_Init();
	Entity_Init();
	World_Init();

	Audio_AddSound("PickupCoin", "assets/PickupCoin.wav", SoundType_WAV);
	Audio_AddSound("Ambience01", "assets/ambience01.mp3", SoundType_OGG);

	return 0;
}

void Engine_SetTitle(const char* title) {
	SDL_SetWindowTitle(window, title);
}

void Engine_Quit() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}
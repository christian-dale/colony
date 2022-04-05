#ifndef ENGINE_H_
#define ENGINE_H_

#include <SDL2/SDL.h>
#include "../engine/config.h"
#include "../options.h"

typedef struct Engine {
	Config config;
	Options options;
	char* title;
	SDL_Window* window;
	SDL_Renderer* renderer;
} Engine;

extern Engine engine;

int Engine_Init();

void Engine_SetTitle(const char* title);

void Engine_Quit();

#endif
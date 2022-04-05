#include <SDL2/SDL.h>
#include "time.h"

uint32_t currentTime;
uint32_t deltaTime;

float Time_GetDelta() {
	deltaTime = (SDL_GetTicks() - currentTime) * (60.0 * 1000.0);

	if (deltaTime > 1.5) {
		deltaTime = 1.5;
	}

	currentTime = SDL_GetTicks();

	return deltaTime;
}
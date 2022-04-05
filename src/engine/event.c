#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../engine/vector.h"
#include "config.h"
#include "../ecs/entity.h"
#include "../engine/render.h"
#include "../ui/hud.h"
#include "../engine/event.h"

void Event_Update() {
	const uint8_t* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_D]) {
		offset.x -= 10;
	}

	if (state[SDL_SCANCODE_A]) {
		offset.x += 10;
	}

	if (state[SDL_SCANCODE_W]) {
		offset.y += 10;
	}

	if (state[SDL_SCANCODE_S]) {
		offset.y -= 10;
	}

	while (SDL_PollEvent(&config.event)) {
		switch (config.event.type) {
		case SDL_QUIT:
			config.quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (config.event.button.button == SDL_BUTTON_LEFT) {
				config.mouseState = true;
				int x, y;
				SDL_GetMouseState(&x, &y);
				config.mouseInit.x = config.mouseX;
				config.mouseInit.y = config.mouseY;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (config.event.button.button == SDL_BUTTON_LEFT) {
				config.mouseState = false;
			}
			break;
		case SDL_MOUSEMOTION:
			if (config.event.button.button == SDL_BUTTON_MIDDLE) {
				offset.x += config.event.motion.xrel;
				offset.y += config.event.motion.yrel;
				config.event.motion.xrel = 0;
				config.event.motion.yrel = 0;
			}
			break;
		case SDL_MOUSEWHEEL:
			zoom += config.event.wheel.y * 0.1;
			config.event.wheel.y = 0;
			break;
		case SDL_KEYDOWN:
			switch (config.event.key.keysym.sym) {
			case SDLK_UP:
				offset.y += 10;
				break;
			case SDLK_DOWN:
				offset.y -= 10;
				break;
			case SDLK_LEFT:
				offset.x += 10;
				break;
			case SDLK_RIGHT:
				offset.x -= 10;
				break;
			case SDLK_PLUS:
				zoom += 0.1;
				break;
			case SDLK_MINUS:
				zoom -= 0.1;
				break;
			case SDLK_q:
				if (toggleUnitSelect) {
					toggleUnitSelect = false;
					PlaceUnit(entityComponents.units);
				}
				break;
			case SDLK_t:
				// UnitToggle(worldUnits, 20 * 20);
				break;
			}
			break;
		}
	}
}
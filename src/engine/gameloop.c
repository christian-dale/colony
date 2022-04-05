#include <SDL2/SDL.h>
#include "../engine/gameloop.h"
#include "../engine/engine.h"
#include "../engine/event.h"
#include "../engine/config.h"
#include "../options.h"
#include "../engine/time.h"
#include "../ui/hud.h"
#include "../ui/menu.h"
#include "../world.h"

void GameLoop() {
	Event_Update();

	SDL_Rect rectViewport = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	config.viewport = rectViewport;

	SDL_GetMouseState(&config.mouseX, &config.mouseY);
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
	SDL_RenderClear(renderer);

	switch (engine.options.gameState) {
		case GameState_Main:
			MenuDraw();
			break;
		case GameState_Game:
			if (config.mouseState) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				//SDL_Rect rect = { config.mouseInit.x, config.mouseInit.y, config.mouseX, config.mouseY };
				// SDL_RenderDrawRect(renderer, &rect);
			}

			World_Update();
			DrawHUD();
			break;
	}

	SDL_RenderPresent(renderer);
	SDL_Delay(1000 / 60);
	config.deltaTime = Time_GetDelta();
}
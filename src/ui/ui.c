#include <string.h>
#include <SDL2/SDL.h>
#include "../engine/render.h"
#include "../ui/hud.h"
#include "../engine/config.h"
#include "../misc.h"
#include "../engine/sprite.h"

void DrawButton(const char* title, int x, int y, int width, void cb()) {
	SDL_Rect rect1 = { x, y, 100, 25 };
	SDL_Rect rect2 = { config.mouseX, config.mouseY, 1, 1 };

	Color btn = { 20, 20, 20, 255 };
	int btnWidth = width ? width : strlen(title) * 8 * 2;
	RenderRect(x, y, btnWidth, 25, btn);

	DrawTextHUD(title, x + (btnWidth * 0.5) - strlen(title) * 4, y + 8);

	if (CheckBounds(rect1, rect2) && config.event.button.type == SDL_MOUSEBUTTONUP && config.event.button.button == SDL_BUTTON_LEFT) {
		config.event.button.button = 0;
		cb();
	}
}
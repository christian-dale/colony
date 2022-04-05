#include <math.h>
#include <SDL2/SDL.h>
#include "../engine/render.h"
#include "../engine/vector.h"
#include "../engine/color.h"
#include "../engine/config.h"
#include "../options.h"
#include "../misc.h"

Vec2 offset = { 0, 0 };
float zoom = 1;

Vec2 Render_ToLocal(int x, int y) {
	Vec2 relative = { x * zoom + offset.x, y * zoom + offset.y };

	return relative;
}

void RenderTexture(SDL_Texture* texture, SDL_Rect rect1, SDL_Rect rect2, int rotation, Color* color) {
	if (color != NULL) {
		SDL_SetTextureColorMod(texture, color->r, color->g, color->b);
	}

	if (CheckBounds(config.viewport, rect2)) {
		SDL_RenderCopyEx(renderer, texture, &rect1, &rect2, rotation, NULL, SDL_FLIP_NONE);
	}

	SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void RenderRect(int x, int y, int width, int height, Color color) {
	SDL_Rect rect = { x, y, width, height };

	if (CheckBounds(config.viewport, rect)) {
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

		SDL_Rect rect = { x, y, width, height };
		SDL_RenderFillRect(renderer, &rect);
	}
}

void RenderCircle(int ox, int oy, int radius, Color color) {
	SDL_Rect rect = { ox, oy, radius, radius };

	if (CheckBounds(config.viewport, rect)) {
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

		for (int y = -radius; y < radius; y++) {
			int w = sqrt(radius * radius - y * y);
			for (int x = -w; x < w; x++) {
				SDL_RenderDrawPoint(renderer, ox + x, oy + y);
			}
		}
	}
}

void RenderCircleLight(int ox, int oy, int radius, Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	for (int y = -radius; y < radius; y++) {
		int w = sqrt(radius * radius - y * y);
		for (int x = -w; x < w; x++) {
			if ((x > w - 4 && x < w) || (x < -w + 4 && x > -w)) {
				SDL_RenderDrawPoint(renderer, ox + x, oy + y);
			}
		}
	}
}
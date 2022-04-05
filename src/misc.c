#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "options.h"
#include "engine/vector.h"

long double G = 6.67e-11;
long double AU = 149.6e9;
long double SCALE = 120 / 149.6e9;
long double timestep = 24 * 3600 / 4;

int CalculateLevel(int health, int defence, int damage) {
	return (health + defence + damage) / 100;
}

double Distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y2, 2));
}

Vec2 ConvertCoords(double x, double y) {
	Vec2 coords = { 0.5 * SCREEN_WIDTH + x, 0.5 * SCREEN_HEIGHT + y };
	return coords;
}

Vec2 TranslateCoords(double x, double y) {
	Vec2 coords = { 0.5 * SCREEN_WIDTH + x * SCALE, 0.5 * SCREEN_HEIGHT + y * SCALE };
	return coords;
}

int RoundGrid(int gridSize, int n) {
	return round(n / gridSize) * gridSize;
}

bool CheckBoundsCircle(Vec2 pos1, int r1, Vec2 pos2, int r2) {
	const int distance = sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos2.x, 2));
	return (bool)distance < r1 + r2;
}

bool CheckBounds(SDL_Rect rect1, SDL_Rect rect2) {
	if (rect1.x + rect1.w >= rect2.x &&
		rect1.x <= rect2.x + rect2.w &&
		rect1.y + rect1.h >= rect2.y &&
		rect1.y <= rect2.y + rect2.h) {
		return true;
	}

	return false;
}
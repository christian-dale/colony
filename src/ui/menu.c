#include <stdlib.h>
#include <stdbool.h>
#include "../engine/engine.h"
#include "../engine/render.h"
#include "../engine/sprite.h"
#include "../ui/ui.h"
#include "../ui/hud.h"

bool showMenu = true;

void OnQuit() {
	exit(0);
}

void OnStart() {
	showMenu = false;
}

bool MenuDraw() {
	if (!showMenu) {
		engine.options.gameState = GameState_Game;
		return false;
	}

	Color color = { 10, 10, 10, 255 };
	RenderRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);

	DrawTextHUD("COLONY", 100, 75);

	DrawTextHUD("ALPHA", 100, SCREEN_HEIGHT - 75);

	DrawButton("PLAY", 100, 125, 0, OnStart);
	DrawButton("QUIT", 100, 175, 0, OnQuit);

	DrawSpriteHUD(spriteMoon01, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 200, 32, 32);

	return true;
}
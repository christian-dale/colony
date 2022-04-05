#include <stdio.h>
#include "../engine/audio.h"
#include "../ecs/entity.h"
#include "../ecs/ecs.h"
#include "../engine/config.h"
#include "../options.h"
#include "../engine/render.h"
#include "../engine/vector.h"
#include "../engine/sprite.h"
#include "../misc.h"
#include "../obj/unit.h"
#include "../ui/menu.h"

bool toggleUnitSelect = false;
UnitUI selectedUnit;

void PlaceUnit(Unit* worldUnits) {
	Component_Transform transform = { 0 };
	transform.x = RoundGrid(64, config.mouseX - offset.x);
	transform.y = RoundGrid(64, config.mouseY - offset.y);
	transform.w = 64;
	transform.h = 64;

	Unit unit = { 0 };
	unit.id = selectedUnit.id;
	unit.sprite = selectedUnit.sprite;
	unit.maxHealth = 400;
	unit.health = 400;

	Vec2 pos = { transform.x, transform.y };

	if (UnitAdjacent(pos, UnitOwner_Player)) {
		AudioPlay("PickupCoin", -1);
		Entity entity = Entity_AtPos(transform.x, transform.y);
		Entity_SetComponentTransform(entity, transform);
		Entity_SetComponentUnit(entity, unit);
	} else {
		printf("Can't place a unit here!\n");
	}
}

void SelectHUDItem(UnitUI unit) {
	int mouseX = RoundGrid(64, config.mouseX - offset.x);
	int mouseY = RoundGrid(64, config.mouseY - offset.y);
	selectedUnit = unit;
	DrawSpriteHUD(unit.sprite, mouseX * zoom + offset.x, mouseY * zoom + offset.y, 64 * zoom, 64 * zoom);
}

void DrawHUDUnit(UnitUI unit, int index) {
	if (index == 0) {
		Color color = { 40, 40, 40, 255 };
		RenderRect(SCREEN_WIDTH - 64, 0, 64, SCREEN_HEIGHT, color);
	}

	SDL_Rect rect1 = { SCREEN_WIDTH - 48, 8 + index * 48, 32, 32 };
	SDL_Rect rect2 = { config.mouseX, config.mouseY, 1, 1 };

	if ((CheckBounds(rect1, rect2) && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) || 
		(toggleUnitSelect && unit.id == selectedUnit.id)) {
		toggleUnitSelect = true;
		SelectHUDItem(unit);
	}

	DrawSpriteHUD(unit.sprite, SCREEN_WIDTH - 48, 8 + index * 48, 32, 32);
}

void DrawHUDUnits(UnitUI* units, int c) {
	Color color = { 40, 40, 40, 255 };
	RenderRect(SCREEN_WIDTH - 64, 0, 64, SCREEN_HEIGHT, color);

	for (int i = 0; i < c; i++) {
		SDL_Rect rect1 = { SCREEN_WIDTH - 48, 8 + i * 48, 32, 32 };
		SDL_Rect rect2 = { config.mouseX, config.mouseY, 1, 1 };

		if (CheckBounds(rect1, rect2) || (toggleUnitSelect && units[i].id == selectedUnit.id)) {
			toggleUnitSelect = true;
			SelectHUDItem(units[i]);
		}

		DrawSpriteHUD(units[i].sprite, SCREEN_WIDTH - 48, 8 + i * 48, 32, 32);
	}
}

void DrawHUDStats(int playerCurrency, int energyStorage) {
	int x = 0.5 * SCREEN_WIDTH;
	int y = SCREEN_HEIGHT - 75;
	Color color = { 20, 20, 20, 255 };

	char strWater[32];
	char strMinerals[32];

	sprintf(strWater, "PLAYER CURRENCY: %d", playerCurrency);
	sprintf(strMinerals, "ENERGY STORAGE: %d", energyStorage);
	RenderRect(x, y, 0.5 * SCREEN_WIDTH, 75, color);
	DrawTextHUD(strWater, x + 16, y + 16);
	DrawTextHUD(strMinerals, x + 16, y + 32);
}

void DrawHUDTooltip(int x, int y) {
	Color color = { 0, 100, 100, 100 };

	for (int i = 0; i < 8; i++) {
		RenderCircle(x + 16 * i, y, 4, color);
	}
}

void DrawHUDMessage(char* title, char* str) {
	Color color = { 20, 20, 20, 255 };
	RenderRect(8, SCREEN_HEIGHT - 32 * 3 - 8, 32 * 8, 32 * 3, color);
	DrawSpriteHUD(spriteOxygen01, 32 * 8 - 16, SCREEN_HEIGHT - 32, 16, 16);
	DrawTextHUD(title, 16, SCREEN_HEIGHT - 32 * 3);
	DrawTextHUD(str, 16, SCREEN_HEIGHT - 64);
}

void DrawHUDInfo(int x, int y, int parent, int level) {
	char* playerTypes[] = { "PLAYER", "AI 1", "AI 2", "AI 3" };

	char strShip[32];
	sprintf(strShip, "%s SHIP", playerTypes[parent]);

	char strLevel[32];
	sprintf(strLevel, "LEVEL %d", level);

	DrawText(strLevel, x, y - 64);
	DrawText(strShip, x, y - 48);
}

void DrawHUDHealth(int x, int y, int maxHealth, int health) {
	Color color = { 20, 20, 20, 255 };
	Color color2 = { 100, 0, 0, 255 };

	Vec2 local = Render_ToLocal(x, y - 32);

	RenderRect(local.x, local.y, 100, 4, color);
	int healthPercent = ((float) health / (float) maxHealth) * 100.0;
	RenderRect(local.x, local.y, healthPercent, 4, color2);
}

void DrawHUD() {
	if (toggleUnitOptions) {
		DrawUnitOptions();
	}

	/*
	for (int i = 0; i < 8; i++) {
		DrawSpriteHUD(spriteHeart01, 16 + i * 16, SCREEN_HEIGHT - 32, 16, 16);
		DrawSpriteHUD(spriteOxygen01, 16 + i * 16, SCREEN_HEIGHT - 48, 16, 16);
	}
	*/
}
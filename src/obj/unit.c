#include <stdio.h>
#include "unit.h"
#include "../engine/config.h"
#include "../options.h"
#include "../engine/render.h"
#include "../misc.h"
#include "../ui/ui.h"
#include "../ui/hud.h"
#include "../ecs/ecs.h"
#include "../ecs/entity.h"
#include "../engine/sprite.h"
#include "../player.h"

bool toggleUnitOptions = false;
Unit unitSelectedOptions;

bool UnitAdjacent(Vec2 pos, int owner) {
	for (int i = 0; i < entityCount; i++) {
		Component_Transform transform = Entity_GetComponentTransform(entityComponents.units[i].entity);

		SDL_Rect rect1 = { transform.x, transform.y, 64, 64 };
		SDL_Rect rect2 = { pos.x - 32, pos.y - 32, 64 + 96, 64 + 96 };

		if (CheckBounds(rect1, rect2) && entityComponents.units[i].id != 0 && entityComponents.units[i].owner == owner) {
			return true;
		}
	}

	return false;
}

Component_Transform* UnitsAdjacent(Component_Transform unit) {
	Component_Transform* units = calloc(sizeof(Component_Transform), 8);
	return units;
}

void UnitUpgrade(Unit unit) {
	unit.health = unit.health * 2;
}

void PlaceGrid(Component_Transform* unit, int x, int y) {
	unit->x = x * 64.0;
	unit->y = y * 64.0;
}

void UnitToggle(Unit* worldUnits, int c) {
	for (int i = 0; i < c; i++) {
		worldUnits[i].toggle = !worldUnits[i].toggle;
	}
}

void CreateColony(int enemy, Unit* units, int c) {
	Component_Transform transform = { .x = (rand() % 20) * 64, .y = (rand() % 20) * 64, .w = 64, .h = 64 };

	Units unitsHangar;
	UnitHangar hangar = { 0 };
	unitsHangar.unitHangar = hangar;
	//ECS_Entity ship = Ship_Create(enemy, transform.x + 10, transform.y, 100, 100, 10);
	Unit unit = units[0];
	unit.unit = unitsHangar;
	unit.owner = enemy;
	ECS_Entity entity = ECS_Create();
	transform.x += 64;
	ECS_SetComponent(entity, "Unit", &unit);
	ECS_SetComponent(entity, "Transform", &transform);
}

void OnOptionsClose() {
	toggleUnitOptions = false;
}

void OnOptionsUpgradeUnit() {
	if (playerCurrency >= unitSelectedOptions.cost) {
		unitSelectedOptions.upgrade++;
		playerCurrency -= unitSelectedOptions.cost;
	}
}

void OnOptionsCreateShip() {
	if (playerCurrency < 4000) {
		return;
	}

	//Component_Transform transformSelectedUnit = Entity_GetComponentTransform(unitSelectedOptions.entity);
	//Entity entity = Ship_Create(unitSelectedOptions.entity, transformSelectedUnit.x + 64, transformSelectedUnit.y, 100, 100, 10);
	playerCurrency -= 4000;
}

void DrawUnitOptions() {
	Color color = { 40, 40, 40, 255 };
	Color color2 = { 100, 100, 100, 255 };

	RenderRect(0, 0, 160, SCREEN_HEIGHT, color);

	DrawButton("X", 0, 0, 0, OnOptionsClose);

	int offset = 16;
	int padding = 8;
	DrawTextHUD(unitSelectedOptions.name, offset, 32);

	offset += 48;
	DrawButton("UPGRADE", padding, offset, 135, OnOptionsUpgradeUnit);

	offset += 32;
	RenderRect(0, offset, 160, 4, color2);

	offset += 32;
	DrawTextHUD("STATS", padding, offset);

	char buffer[32];
	int level = CalculateLevel(unitSelectedOptions.maxHealth, unitSelectedOptions.defence, unitSelectedOptions.damage);
	sprintf(buffer, "LEVEL: %d", level);
	offset += 16;
	DrawTextHUD(buffer, padding, offset);

	sprintf(buffer, "O2: %d", unitSelectedOptions.oxygen);
	offset += 16;
	DrawTextHUD(buffer, padding, offset);

	sprintf(buffer, "HEALTH: %d %d", unitSelectedOptions.health, unitSelectedOptions.maxHealth);
	offset += 16;
	DrawTextHUD(buffer, padding, offset);

	sprintf(buffer, "DEFENCE: %d", unitSelectedOptions.defence);
	offset += 16;
	DrawTextHUD(buffer, padding, offset);

	switch (unitSelectedOptions.id) {
	case Unit_Lab:
		offset += 32;
		DrawButton("NEW SHIP", padding, offset, 135, OnOptionsCreateShip);
		break;
	case Unit_Hangar:

		break;
	case Unit_Area:

		break;
	case Unit_Gardens:

		break;
	}
}

void UpdateUnit(Unit* unit, Component_Transform* transform) {
	SDL_Rect rectMouse = { config.mouseX, config.mouseY, 1, 1 };
	SDL_Rect rectUnit = { transform->x * zoom + offset.x, transform->y * zoom + offset.y, transform->w * zoom, transform->h * zoom };

	if (CheckBounds(rectUnit, rectMouse) && unit->id != 0 && unit->owner == UnitOwner_Player) {
		toggleUnitOptions = true;
		unitSelectedOptions = *unit;
	}

	if (unit->health <= 0) {
		unit->entity = 0;
	}

	SDL_Rect rect1 = { transform->x * zoom + offset.x, transform->y * zoom + offset.y, transform->w * zoom, transform->h * zoom };
	SDL_Rect rect2 = { config.mouseX, config.mouseY, 1, 1 };

	for (int i = 0; i < entityCount; i++) {
		if (entityComponents.ships[i].entity != 0 && entityComponents.ships[i].parent != UnitOwner_Player) {
			Vec2 point = { transform->x, transform->y };
			entityComponents.ships[i].attackPoint = point;
		}
	}

	if (CheckBounds(rect1, rect2) && unit->id != Unit_Empty && unit->owner != UnitOwner_Player) {
		DrawSprite(spriteAttack, transform->x - transform->w * 0.5, transform->y - transform->h * 0.5, 32, 32, 0, NULL);

		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			for (int i = 0; i < entityCount; i++) {
				if (entityComponents.ships[i].entity != 0 && entityComponents.ships[i].selected == true) {
					Vec2 point = { transform->x, transform->y };
					entityComponents.ships[i].attackPoint = point;
				}
			}
		}
	}
}

Color UnitColorFromOwner(int owner) {
	Color color = { 0 };

	switch (owner) {
		default:
		case 0:
			color.r = 255;
			color.g = 255;
			color.b = 255;
			break;
		case 1:
			color.r = 100;
			color.g = 255;
			color.b = 100;
			break;
		case 2:
			color.r = 100;
			color.g = 100;
			color.b = 255;
			break;
		case 3:
			color.r = 255;
			color.g = 100;
			color.b = 100;
			break;
	}

	return color;
}

void UnitDrawShield(Vec2 pos, Color color) {
	RenderCircleLight((pos.x + 32) * zoom + offset.x, (pos.y + 32) * zoom + offset.y, 92 * zoom, color);
}

void DrawUnitTerritory(Unit* units, Component_Transform* transforms) {
	Color color = { 100, 100, 100, 255 };

	for (int i = 0; i < entityCount; i++) {
		if (units[i].entity != 0 && units[i].id != Unit_Empty) {
			int width = transforms[i].x - transforms[i].w;
			int height = transforms[i].y - transforms[i].h;
			RenderRect(width * zoom + offset.x, height * zoom + offset.y, transforms[i].w * 3, transforms[i].h * 3, color);
		}
	}
}

void DrawUnit(Unit* unit, Component_Transform* transform) {
	Vec2 coords = { transform->x, transform->y };

	Color color = UnitColorFromOwner(unit->owner);
	DrawSprite(unit->sprite, coords.x, coords.y, transform->w, transform->h, 0, &color);

	SDL_Rect rect1 = { coords.x * zoom + offset.x, coords.y * zoom + offset.y, transform->w * zoom, transform->h * zoom };
	SDL_Rect rect2 = { config.mouseX, config.mouseY, 1, 1 };

	if (CheckBounds(rect1, rect2) && unit->id != Unit_Empty) {
		DrawHUDHealth(transform->x, transform->y, unit->maxHealth, unit->health);
		DrawHUDInfo(coords.x, coords.y, unit->owner, CalculateLevel(unit->maxHealth, unit->defence, unit->damage));
	}

	if (unit->id != Unit_Empty) {
		//Vec2 pos = { transform->x, transform->y };
		// UnitDrawShield(pos, color);
	}

	float health = unit->health;

	SDL_Rect spriteDmg = spriteEmpty;

	if (health < 75) {
		spriteDmg = spriteDmg01;
	}

	if (health < 50) {
		spriteDmg = spriteDmg02;
	}

	if (health < 25) {
		spriteDmg = spriteDmg03;
	}

	if (health < 10) {
		spriteDmg = spriteDmg04;
	}

	DrawSprite(spriteDmg, coords.x, coords.y, transform->w, transform->h, 0, NULL);
}
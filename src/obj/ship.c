#include <string.h>
#include "ship.h"
#include "../engine/config.h"
#include "../engine/render.h"
#include "../ecs/entity.h"
#include "../ecs/ecs.h"
#include "../engine/sprite.h"
#include "../misc.h"
#include "../ui/hud.h"

Entity Ship_Create(int parent, int x, int y, int health, int defence, int damage) {
	ECS_Entity entity = ECS_Create();
	Component_Transform shipTransform = { .x = x, .y = y };
	Ship ship = { 0 };
	ship.maxHealth = health;
	ship.health = health;
	ship.defence = defence;
	ship.damage = damage;
	ship.parent = parent;
	ship.state = ShipState_Formation;
	ECS_SetComponent(entity, "Ship", &ship);
	ECS_SetComponent(entity, "Transform", &shipTransform);

	return entity;
}

void Ship_SelectArea(Ship* ships, int c, SDL_Rect area) {
	for (int i = 0; i < c; i++) {
		Component_Transform transform = Entity_GetComponentTransform(ships[i].entity);

		SDL_Rect rectShip = { transform.x, transform.y, 1, 1 };
		ships[i].selected = false;

		if (CheckBounds(area, rectShip)) {
			ships[i].selected = true;
		}
	}
}

void Ship_Formation(Ship* ships, int c, Vec2 point) {
	int row = 0;
	int column = 0;

	for (int i = 0; i < c; i++) {
		if (ships[i].entity == 0) {
			continue;
		}

		if (i % 10 == 0) {
			row++;
			column = 0;
		} else {
			column++;
		}

		Component_Transform transform = Entity_GetComponentTransform(ships[i].entity);
		Vec2 dest = { point.x + column * 32, point.y + row * 32 };
		SDL_Rect rect1 = { transform.x, transform.y, 1, 1 };
		SDL_Rect rect2 = { dest.x, dest.y, 1, 1 };

		if (!CheckBounds(rect1, rect2) && ships[i].state == ShipState_Formation) {
			Ship_MoveTo(ships[i], dest);
		}
	}
}

void Ship_MoveTo(Ship ship, Vec2 point) {
	Component_Transform transform = Entity_GetComponentTransform(ship.entity);

	transform.x = point.x;
	transform.y = point.y;

	/*
	transform.moveTo = point;

	Vec2 dir = { point.x - transform.x, point.y - transform.y };
	Vec2 vec = Vec2Normalize(dir);
	Vec2 v = { vec.x * 0.75, vec.y * 0.75 };
	transform.velocity = v;
	*/

	Entity_SetComponentTransform(ship.entity, transform);
}

Component_Transform Ship_ShortestDistance(Component_Transform transform) {
	int* distances = malloc(sizeof(int) * entityCount);
	memset(distances, -1, sizeof(int) * entityCount);

	int index = 0;
	Unit unit;
	Component_Transform transformUnit;
	for (int i = 0; i < entityCount; i++) {
		unit = entityComponents.units[i];
		transformUnit = entityComponents.transforms[i];

		if (unit.entity != 0 && unit.id != 0 && unit.owner == 0) {
			index = i;
			distances[i] = Distance(transformUnit.x, transformUnit.y, transform.x, transform.y);
		}
	}

	int min = distances[index];

	for (int i = 0; i < entityCount; i++) {
		if (distances[i] != -1 && distances[i] < min) {
			min = distances[i];
		}
		
		if (distances[i] == min) {
			index = i;
		}
	}

	free(distances);

	return entityComponents.transforms[index];
}

void ShipsDraw(Ship* ships, int c) {
	for (int i = 0; i < c; i++) {
		Component_Transform transform = Entity_GetComponentTransform(ships[i].entity);
		DrawSprite(spriteShip01, transform.x, transform.y, 16, 16, 0, NULL);
	}
}

void Ship_Update(Ship* ship, Component_Transform* transform) {
	if (ship->selected == true) {
		Ship_HandleAttack(*ship, *transform);
	} else {
		ship->attackPoint = Vec2_Zero;
	}
}

void Ship_Draw(Component_Transform transform, Ship ship) {
	Vec2 coords = { .x = transform.x, .y = transform.y };
	SDL_Rect rect1 = { coords.x * zoom + offset.x, coords.y * zoom + offset.y, 16 * zoom, 16 * zoom };
	SDL_Rect rect2 = { config.mouseX, config.mouseY, 1, 1 };

	if (CheckBounds(rect1, rect2)) {
		DrawHUDHealth(transform.x, transform.y, ship.maxHealth, ship.health);
		DrawHUDInfo(transform.x, transform.y, ship.parent, CalculateLevel(ship.maxHealth, ship.defence, ship.damage));
	}

	if (CheckBounds(rect1, rect2) && config.event.button.type == SDL_MOUSEBUTTONUP && config.event.button.button == SDL_BUTTON_LEFT) {
		if (ship.parent == UnitOwner_Player) {
			config.event.button.button = 0;
			ship.selected = !ship.selected;
			ECS_SetComponent(ship.entity, "Ship", &ship);
		}
	}

	if (ship.selected == true) {
		Color color = { 0, 100, 150, 255 };
		RenderCircle(transform.x * zoom + offset.x + 8, transform.y * zoom + offset.y + 8, 16, color);
	}

	DrawSprite(spriteShip01, transform.x, transform.y, 16, 16, 0, NULL);
}

void Ship_HandleAttack(Ship ship, Component_Transform transform) {
	if (ship.attackPoint.x != 0 && ship.attackPoint.y != 0) {
		if (ship.lastAttack + 1000 < SDL_GetTicks()) {
			Ship_Attack(&ship, &transform, ship.attackPoint);
			ship.lastAttack = SDL_GetTicks();
		}
	}

	Entity_SetComponentShip(ship.entity, ship);
}

void Ship_Attack(Ship* ship, Component_Transform* transform, Vec2 pos) {
	Entity entity = Entity_Create();

	Bullet bullet = { 0 };
	bullet.parent = ship->parent;
	bullet.createdAt = SDL_GetTicks();
	Component_Transform transformBullet = *transform;

	Vec2 dir = { pos.x - transform->x, pos.y - transform->y };
	Vec2 vec = Vec2Normalize(dir);
	Vec2 v = { vec.x * 1.75, vec.y * 1.75 };
	transformBullet.velocity = v;

	Entity_SetComponentBullet(entity, bullet);
	Entity_SetComponentTransform(entity, transformBullet);
}
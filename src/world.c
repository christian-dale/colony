#include <stdbool.h>
#include <SDL2/SDL.h>
#include "engine/config.h"
#include "options.h"
#include "ui/tutorial.h"
#include "misc.h"
#include "engine/render.h"
#include "ecs/ecs.h"
#include "engine/vector.h"
#include "engine/color.h"
#include "engine/sprite.h"
#include "ui/hud.h"
#include "ecs/entity.h"
#include "player.h"
#include "obj/enemy.h"
#include "obj/particle.h"
#include "obj/asteroid.h"
#include "obj/unit.h"
#include "obj/ship.h"

Particle* particles;
Asteroid* asteroids;
Unit* units;
Unit* worldUnits;
Ship* worldShips;
int unitsCount = 6;
int worldUnitsCount = 2;
int worldShipsCount = 0;
int players[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
int gridSize = 20;

void DrawGrid() {
	Color color = { 44, 44, 44, 255 };
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (int x = 0; x <= 64 * gridSize; x += 64) {
		SDL_RenderDrawLine(renderer, x * zoom + offset.x, 1 * zoom + offset.y, x * zoom + offset.x, (64 * gridSize) * zoom + offset.y);
	}

	for (int y = 0; y <= 64 * gridSize; y += 64) {
		SDL_RenderDrawLine(renderer, 1 * zoom + offset.x, y * zoom + offset.y, (64 * gridSize) * zoom + offset.x, y * zoom + offset.y);
	}
}

void World_AddShip(Ship ship) {
	worldShipsCount++;
	worldShips[worldShipsCount - 1] = ship;
}

void World_AddUnit(Unit unit) {

}

void World_Init() {
	particles = malloc(sizeof(Particle) * 32);
	asteroids = malloc(sizeof(Asteroid) * 32);
	units = malloc(sizeof(Unit) * 32);
	worldUnits = malloc(sizeof(Unit) * 20 * 20);
	worldShips = malloc(sizeof(Ship) * 1024);

	playerCurrency = 100000;
	energyStorage = 1000;

	Particle earth = {
		.id = 0, .name = "MOON", .sprite = spriteMoon01, .color = {0, 0, 255, 255},
		.mass = 1.989e30, .x = 0, .y = 0, .vx = 0, .vy = 0,
		.radius = 40, .resources = {.water = 100, .minerals = 100}
	};
	/*
	Particle moon = {
		.id = 1, .name = "MOON", .sprite = spriteMoon01, .color = {100, 100, 100, 255},
		.mass = 5.972e24, .x = AU, .y = 0, .vx = 0, .vy = 30290,
		.radius = 8, .resources = {.water = 100, .minerals = 100}
	};
	*/
	particles[0] = earth;

	Unit unitEmpty = {
		.id = 0, .name = "EMPTY TILE", .sprite = spriteEmpty,
		.toggle = false, .oxygen = 100, .food = 100, .water = 100,
		.maxHealth = 400, .health = 400, .defence = 100, .morale = 100, .population = 10
	};

	Unit station = {
		.id = 1, .name = "STATION", .sprite = spriteUnit01,
		.toggle = false, .cost = 1000, .oxygen = 100, .food = 100, .water = 100,
		.maxHealth = 400, .health = 400, .defence = 100, .morale = 100, .population = 10
	};

	Unit station2 = {
		.id = 2, .name = "STATION2", .sprite = spriteUnit02,
		.toggle = false, .cost = 1000, .oxygen = 10, .food = 100, .water = 100,
		.maxHealth = 400, .health = 400, .defence = 100, .morale = 100, .population = 10
	};

	Unit station3 = {
		.id = 3, .name = "STATION3", .sprite = spriteUnit03,
		.toggle = false, .cost = 1000, .oxygen = 100, .food = 100, .water = 100,
		.maxHealth = 400, .health = 400, .defence = 100, .morale = 100, .population = 10
	};

	Unit station4 = {
		.id = 4, .name = "GARDENS", .sprite = spriteUnit04,
		.toggle = false, .cost = 1000, .oxygen = 100, .food = 100, .water = 100,
		.maxHealth = 400, .health = 400, .defence = 100, .morale = 100, .population = 10
	};

	Unit station5 = {
		.id = 5, .name = "STATION5", .sprite = spriteUnit05,
		.toggle = false, .cost = 1000, .oxygen = 100, .food = 100, .water = 100,
		.maxHealth = 400, .health = 400, .defence = 100, .morale = 100, .population = 10
	};

	Unit station6 = {
		.id = 6, .name = "STATION6", .sprite = spriteUnit06,
		.toggle = false, .cost = 1000, .oxygen = 0, .food = 0, .water = 0,
		.maxHealth = 400, .health = 400, .defence = 0, .morale = 0, .population = 0, .energy = 100
	};

	ECS_Init();

	ECS_AddComponent("Transform", sizeof(Component_Transform));
	ECS_AddComponent("Unit", sizeof(Unit));
	ECS_AddComponent("UnitUI", sizeof(UnitUI));
	ECS_AddComponent("Ship", sizeof(Ship));
	ECS_AddComponent("Asteroid", sizeof(Asteroid));
	ECS_AddComponent("Bullet", sizeof(Bullet));

	// Place empty units on all tiles.
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			ECS_Entity entity = ECS_Create();
			Component_Transform cTransform = { .x = 0, .y = 0 };
			Unit cUnit = unitEmpty;
			cUnit.owner = 0;
			cTransform.x = j * 64;
			cTransform.y = i * 64;
			cTransform.w = 64;
			cTransform.h = 64;
			ECS_SetComponent(entity, "Transform", &cTransform);
			ECS_SetComponent(entity, "Unit", &cUnit);
		}
	}

	Unit unitsColony[6] = { station, station2, station3, station4, station5, station6 };

	for (int i = 0; i < 4; i++) {
		CreateColony(i, unitsColony, 1);
	}

	// Create UI specific units.

	UnitUI stationUI = { .id = 1, .name = "STATION", .sprite = spriteUnit01, .price = 8000 };
	UnitUI stationUI2 = { .id = 2, .name = "STATION 2", .sprite = spriteUnit02, .price = 8000 };
	UnitUI stationUI3 = { .id = 3, .name = "STATION 3", .sprite = spriteUnit03, .price = 8000 };
	UnitUI stationUI4 = { .id = 4, .name = "STATION 4", .sprite = spriteUnit04, .price = 8000 };
	UnitUI stationUI5 = { .id = 5, .name = "STATION 5", .sprite = spriteUnit05, .price = 8000 };
	UnitUI stationUI6 = { .id = 6, .name = "STATION 6", .sprite = spriteUnit06, .price = 8000 };

	ECS_SetComponent(ECS_Create(), "UnitUI", &stationUI);
	ECS_SetComponent(ECS_Create(), "UnitUI", &stationUI2);
	ECS_SetComponent(ECS_Create(), "UnitUI", &stationUI3);
	ECS_SetComponent(ECS_Create(), "UnitUI", &stationUI4);
	ECS_SetComponent(ECS_Create(), "UnitUI", &stationUI5);
	ECS_SetComponent(ECS_Create(), "UnitUI", &stationUI6);

	/*
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			Unit ship = { .id = 0, .name = "Ship", .sprite = spriteSatelitte01 .x = j * (AU * 0.1) + AU, .y = i * (AU * 0.1) };
			units[8 * i + j] = ship;
		}
	}*/

	for (int i = 0; i < 10; i++) {
		ECS_Entity entity = ECS_Create();
		Asteroid asteroid = { .id = i, .sprite = spriteAsteroid01, .x = -1000 + (rand() % 1000), .y = rand() % gridSize * 64 };
		ECS_SetComponent(entity, "Asteroid", &asteroid);
	}

	/*
	for (int i = 0; i < 64; i++) {
		Entity entity = Entity_Create();
		Ship ship = { 0 };
		Component_Transform transform = { .x = i * 16 + (rand() % 32), .y = i + (rand() % 32) };
		Entity_SetComponentShip(entity, ship);
		Entity_SetComponentTransform(entity, transform);
	}
	*/
}

void World_Update() {
	DrawGrid();
	int indexUI = 0;
	//Vec2 point = { 200, 200 };
	// Ship_Formation(entityComponents.ships, entityCount, point);

	ECS_Entities entities = ECS_QueryEntities(2, "Unit", "Transform");

	for (int i = 0; i < entities.count; i++) {
		Unit* unit = (Unit*) ECS_GetComponent(entities.entities[i], "Unit");
		Component_Transform* transform = (Component_Transform*) ECS_GetComponent(entities.entities[i], "Transform");
		UpdateUnit(unit, transform);
		DrawUnit(unit, transform);
	}

	entities = ECS_QueryEntities(2, "Ship", "Transform");

	for (int i = 0; i < entities.count; i++) {
		Ship* ship = (Ship*) ECS_GetComponent(entities.entities[i], "Ship");
		Component_Transform* transform = (Component_Transform*) ECS_GetComponent(entities.entities[i], "Transform");
		Ship_Update(ship, transform);
		Ship_Draw(*transform, *ship);
	}

	entities = ECS_QueryEntities(1, "Asteroid");

	for (int i = 0; i < entities.count; i++) {
		Asteroid* asteroid = (Asteroid*) ECS_GetComponent(entities.entities[i], "Asteroid");
		Asteroid_Update(asteroid);
		Asteroid_Draw(asteroid);
	}

	entities = ECS_QueryEntities(2, "Bullet", "Transform");

	for (int i = 0; i < entities.count; i++) {
		Bullet* bullet = (Bullet*) ECS_GetComponent(entities.entities[i], "Bullet");
		Component_Transform* transform = (Component_Transform*) ECS_GetComponent(entities.entities[i], "Transform");

		if (bullet->createdAt + 1000 * 30 < SDL_GetTicks()) {
			bullet->entity = 0;
			transform->entity = 0;
		}

		SDL_Rect rect1 = { transform->x, transform->y, 8, 8 };

		for (int i = 0; i < entityCount; i++) {
			if (entityComponents.units[i].entity != 0) {
				SDL_Rect rect2 = { entityComponents.transforms[i].x, entityComponents.transforms[i].y, 64, 64 };

				if (CheckBounds(rect1, rect2) && entityComponents.units[i].id != Unit_Empty) {
					entityComponents.units[i].health -= 10;
					bullet->entity = 0;
					transform->entity = 0;
				}
			}
		}

		Color color = { 100, 100, 100, 255 };
		RenderCircle(transform->x * zoom + offset.x, transform->y * zoom + offset.y, 1, color);
	}

	entities = ECS_QueryEntities(1, "Transform");

	for (int i = 0; i < entities.count; i++) {
		Component_Transform* transform = (Component_Transform*) ECS_GetComponent(entities.entities[i], "Transform");

		transform->x += transform->velocity.x * config.deltaTime;
		transform->y += transform->velocity.y * config.deltaTime;

		SDL_Rect rect1 = { transform->x, transform->y, transform->w, transform->h };
		SDL_Rect rect2 = { transform->moveTo.x - 4, transform->moveTo.y - 4, 8, 8 };

		if (CheckBounds(rect1, rect2) && transform->moveTo.x != 0 && transform->moveTo.y != 0) {
			transform->velocity.x = 0;
			transform->velocity.y = 0;
			transform->moveTo.x = 0;
			transform->moveTo.y = 0;
		}
	}

	entities = ECS_QueryEntities(1, "UnitUI");

	for (int i = 0; i < entities.count; i++) {
		UnitUI* unitUI = (UnitUI*) ECS_GetComponent(entities.entities[i], "UnitUI");
		DrawHUDUnit(*unitUI, indexUI++);
	}

	Tutorial_Update();
	//UpdateUnits(worldUnits, 20 * 20);
	//DrawUnits(worldUnits, 20 * 20);
	// Ship_Formation(entityComponents.ships, entityComponents.shipCount, point);
	// ShipsDraw(entityComponents.ships, entityComponents.shipCount);
	// DrawHUDUnits(entityComponents.unitsUI, entityCount);
	DrawHUDStats(playerCurrency, energyStorage);

	//DrawShips(units, 1);
	// DrawSprite(spriteMoon01, 200, 200, 64, 64);
	// DrawSprite(spriteSatelitte01, 100, 100, 32, 32);
	//DrawParticles(particles, 1);
}

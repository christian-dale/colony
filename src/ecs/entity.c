#include "entity.h"
#include "../misc.h"
#include <stdlib.h>
#include <string.h>

int ENTITY_MAX_SIZE = 10000;
Entity_Components entityComponents;
int entityCount = 1;

void Entity_Init() {
	entityComponents.transforms = calloc(sizeof(Component_Transform), ENTITY_MAX_SIZE);
	entityComponents.units = calloc(sizeof(Unit), ENTITY_MAX_SIZE);
	entityComponents.unitsUI = calloc(sizeof(UnitUI), ENTITY_MAX_SIZE);
	entityComponents.ships = calloc(sizeof(Ship), ENTITY_MAX_SIZE);
	entityComponents.asteroids = calloc(sizeof(Asteroid), ENTITY_MAX_SIZE);
	entityComponents.bullets = calloc(sizeof(Bullet), ENTITY_MAX_SIZE);
}

Entity Entity_Create() {
	return entityCount++;
}

Entity Entity_AtPos(int x, int y) {
	for (int i = 0; i < entityCount; i++) {
		if (entityComponents.transforms[i].x == x && entityComponents.transforms[i].y == y) {
			return entityComponents.transforms[i].entity;
		}
	}

	return 0;
}

void Entity_SetComponentTransform(Entity entity, Component_Transform transform) {
	transform.entity = entity;
	entityComponents.transforms[entity] = transform;
}

void Entity_SetComponentUnit(Entity entity, Unit unit) {
	unit.entity = entity;
	entityComponents.units[entity] = unit;
}

void Entity_SetComponentUnitUI(Entity entity, UnitUI unitUI) {
	unitUI.entity = entity;
	entityComponents.unitsUI[entity] = unitUI;
}

void Entity_SetComponentShip(Entity entity, Ship ship) {
	ship.entity = entity;
	entityComponents.ships[entity] = ship;
}

void Entity_SetComponentAsteroid(Entity entity, Asteroid asteroid) {
	asteroid.entity = entity;
	entityComponents.asteroids[entity] = asteroid;
}

void Entity_SetComponentBullet(Entity entity, Bullet bullet) {
	bullet.entity = entity;
	entityComponents.bullets[entity] = bullet;
}

Component_Transform Entity_GetComponentTransform(Entity entity) {
	for (int i = 0; i < entityCount; i++) {
		if (entityComponents.transforms[i].entity == entity) {
			return entityComponents.transforms[i];
		}
	}

	Component_Transform componentTransform = {0};
	return componentTransform;
}

Unit Entity_GetComponentUnit(Entity entity) {
	for (int i = 0; i < entityCount; i++) {
		if (entityComponents.units[i].entity == entity) {
			return entityComponents.units[i];
		}
	}

	Unit unit = {0};
	return unit;
}

UnitUI Entity_GetComponentUnitUI(Entity entity) {
	for (int i = 0; i < entityCount; i++) {
		if (entityComponents.unitsUI[i].entity == entity) {
			return entityComponents.unitsUI[i];
		}
	}

	UnitUI unitUI = {0};
	return unitUI;
}

Ship Entity_GetComponentShip(Entity entity) {
	for (int i = 0; i < entityCount; i++) {
		if (entityComponents.ships[i].entity == entity) {
			return entityComponents.ships[i];
		}
	}

	Ship ship = {0};
	return ship;
}

Asteroid Entity_GetComponentAsteroid(Entity entity) {
	for (int i = 0; i < entityCount; i++) {
		if (entityComponents.asteroids[i].entity == entity) {
			return entityComponents.asteroids[i];
		}
	}

	Asteroid asteroid = {0};
	return asteroid;
}

Bullet Entity_GetComponentBullet(Entity entity) {
	for (int i = 0; i < entityCount; i++) {
		if (entityComponents.bullets[i].entity == entity) {
			return entityComponents.bullets[i];
		}
	}

	Bullet bullet = {0};
	return bullet;
}
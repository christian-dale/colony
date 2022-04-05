#ifndef ENTITY_H_
#define ENTITY_H_

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../engine/vector.h"

enum EntityComponentTypes { ComponentType_Pos, ComponentType_Render };

typedef uint32_t Entity;

typedef struct UnitLab {
	int research;
} UnitLab;

typedef struct UnitGardens {
	int food;
} UnitGardens;

typedef struct UnitHangar {
	Entity* ships;
} UnitHangar;

typedef struct UnitArea {
	int people;
} UnitArea;

typedef union {
	UnitLab unitLab;
	UnitGardens unitGardens;
	UnitHangar unitHangar;
	UnitArea unitArea;
} Units;

typedef enum UnitOwnerTypes {
	UnitOwner_Player, UnitOwner_AI, UnitOwner_AI2, UnitOwner_AI3
} UnitOwnerTypes;

typedef struct Unit {
	Entity entity;
	int type;
	Units unit;
	int id;
	int owner;
	char name[64];
	SDL_Rect sprite;
	bool toggle;
	int cost;
	int upgrade;
	int oxygen;
	int food;
	int water;
	int defence;
	int maxHealth;
	int health;
	int damage;
	int morale;
	int population;
	int energy;
} Unit;

typedef struct UnitUI {
	Entity entity;
	int id;
	char name[64];
	SDL_Rect sprite;
	int price;
	int x;
	int y;
} UnitUI;

enum ShipState { ShipState_Formation, ShipState_MoveTo };

typedef struct Ship {
	Entity entity;
	int id;
	int parent;
	int state;
	int defence;
	int damage;
	int health;
	int maxHealth;
	Vec2 attackPoint;
	uint32_t lastAttack;
	bool selected;
} Ship;

typedef struct Asteroid {
	Entity entity;
	int id;
	SDL_Rect sprite;
	double x;
	double y;
} Asteroid;

typedef struct Bullet {
	Entity entity;
	int parent;
	uint32_t createdAt;
} Bullet;

typedef struct Component_Transform {
	Entity entity;
	double x;
	double y;
	int w;
	int h;
	Vec2 moveTo;
	Vec2 velocity;
} Component_Transform;

typedef struct Entity_Components {
	Component_Transform* transforms;
	Unit* units;
	UnitUI* unitsUI;
	Ship* ships;
	Asteroid* asteroids;
	Bullet* bullets;
	uint32_t transformCount;
	uint32_t unitCount;
	uint32_t unitUICount;
	uint32_t shipCount;
	uint32_t asteroidCount;
	uint32_t bulletCount;
} Entity_Components;

extern int ENTITY_MAX_SIZE;
extern int componentCount;
extern Entity_Components entityComponents;
extern int entityCount;

void Entity_Init();

Entity Entity_Create();

void Entity_AddComponent(char* name, int size);

Entity Entity_AtPos(int x, int y);

void Entity_SetComponent(Entity entity, char* name, void* component);

void Entity_SetComponentTransform(Entity entity, Component_Transform pos);

void Entity_SetComponentUnit(Entity entity, Unit unit);

void Entity_SetComponentUnitUI(Entity entity, UnitUI unitUI);

void Entity_SetComponentShip(Entity entity, Ship ship);

void Entity_SetComponentAsteroid(Entity entity, Asteroid asteroid);

void Entity_SetComponentBullet(Entity entity, Bullet bullet);

Component_Transform Entity_GetComponentTransform(Entity entity);

Unit Entity_GetComponentUnit(Entity entity);

UnitUI Entity_GetComponentUnitUI(Entity entity);

Ship Entity_GetComponentShip(Entity entity);

Asteroid Entity_GetComponentAsteroid(Entity entity);

Bullet Entity_GetComponentBullet(Entity entity);

#endif
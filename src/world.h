#ifndef WORLD_H_
#define WORLD_H_

#include "obj/particle.h"
#include "obj/asteroid.h"
#include "obj/unit.h"
#include "obj/ship.h"

extern Particle* particles;
extern Asteroid* asteroids;
extern Unit* units;
extern Unit* worldUnits;
extern Ship* worldShips;
extern int unitsCount;
extern int worldShipsCount;

void DrawGrid();

void World_AddShip(Ship ship);

void World_AddUnit(Unit unit);

void World_Init();

void World_Update();

#endif
#ifndef SHIP_H_
#define SHIP_H_

#include "../engine/vector.h"
#include "../ecs/ecs.h"
#include "../ecs/entity.h"

Entity Ship_Create(int parent, int x, int y, int health, int defence, int damage);

void Ship_SelectArea(Ship* ships, int c, SDL_Rect area);

void Ship_Formation(Ship* ships, int c, Vec2 point);

void Ship_MoveTo(Ship ship, Vec2 point);

Component_Transform Ship_ShortestDistance(Component_Transform transform);

void ShipsDraw(Ship* ships, int c);

void Ship_Update(Ship* ship, Component_Transform* transform);

void Ship_Draw(Component_Transform transform, Ship ship);

void Ship_HandleAttack(Ship ship, Component_Transform transform);

void Ship_Attack(Ship* ship, Component_Transform* transform, Vec2 pos);

#endif
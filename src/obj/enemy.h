#ifndef ENEMY_H_
#define ENEMY_H_

#include "../ecs/entity.h"
#include "../engine/vector.h"

enum EnemyType { Enemy_Default };

typedef struct Enemy {
	int id;
	int type;
	double x;
	double y;
} Enemy;

Enemy Enemy_Create(int type, Vec2 pos);

#endif
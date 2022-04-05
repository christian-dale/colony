#include <stdlib.h>

#include <SDL2/SDL.h>
#include "../ecs/entity.h"
#include "../obj/enemy.h"
#include "../engine/vector.h"

Enemy Enemy_Create(int type, Vec2 pos) {
	Enemy enemy = { .id = 0, .type = Enemy_Default, .x = pos.x, .y = pos.y };
	return enemy;
}
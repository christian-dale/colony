#include <SDL2/SDL.h>
#include "../engine/config.h"
#include "../engine/sprite.h"
#include "../ecs/entity.h"
#include "../ecs/ecs.h"
#include "../misc.h"
#include "../obj/unit.h"
#include "../obj/asteroid.h"

void Asteroid_Recycle(Asteroid* asteroid) {
	asteroid->x = -1000 + (rand() % 1000);
	asteroid->y = rand() % 64 * 20;
}

void Asteroid_Update(Asteroid* asteroid) {
	for (int i = 0; i < entityCount; i++) {
		Entity entity = entityComponents.units[i].entity;
		Unit unit = entityComponents.units[i];

		if (entity != 0 && unit.id != Unit_Empty) {
			Component_Transform transform = Entity_GetComponentTransform(entity);
			SDL_Rect rect = { transform.x, transform.y, transform.w, transform.h };
			SDL_Rect rect2 = { asteroid->x, asteroid->y, 16, 16 };

			if (CheckBounds(rect, rect2)) {
				Asteroid_Recycle(asteroid);
				unit.health -= 75;
				Entity_SetComponentUnit(entity, unit);
			}
		}
	}
}

void Asteroid_Draw(Asteroid* asteroid) {
	if (asteroid->x > 1000) {
		Asteroid_Recycle(asteroid);
	}

	asteroid->x = asteroid->x + 0.75 * config.deltaTime;
	DrawSprite(asteroid->sprite, asteroid->x, asteroid->y, 16, 16, asteroid->x * 0.1, NULL);
}
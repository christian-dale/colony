#include <stdlib.h>
#include <math.h>
#include "particle.h"
#include "../engine/render.h"
#include "../engine/vector.h"
#include "../engine/sprite.h"
#include "../misc.h"

Vec2 Particle_Attraction(Particle* self, Particle* other) {
	// Distance between the objects.
	long double distanceX = other->x - self->x;
	long double distanceY = other->y - self->y;
	long double distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

	// Newton's law of gravity.
	long double F = G * self->mass * other->mass / pow(distance, 2);

	// compute direction
	long double o = atan2(distanceY, distanceX); // Angle of the distance vector.

	// Direction vectors.
	Vec2 direction = { cos(o) * F, sin(o) * F };
	return direction;
}

void UpdateV(Particle* p, Vec2 total) {
	p->vx += total.x / p->mass * timestep;
	p->vy += total.y / p->mass * timestep;
	p->x += p->vx * timestep;
	p->y += p->vy * timestep;
}

void DrawParticleInfo(Particle particle, Vec2 coords) {
	Color color = { 0, 100, 100, 100 };
	Color color2 = { 0, 0, 255, 255 };

	DrawText(particle.name, coords.x, coords.y - 48);
	for (int i = 0; i < 8; i++) {
		RenderCircle(coords.x + 16 * i + offset.x, coords.y + offset.y - 32, 4, color);
		RenderCircle(coords.x + 16 * i + offset.x, coords.y + 16 + offset.y - 32, 4, color2);
	}
}

void DrawParticles(Particle* particles, int c) {
	for (int i = 0; i < c; i++) {
		Vec2 total = { 0, 0 };

		for (int j = 0; j < c; j++) {
			if (particles[j].id != particles[i].id) {
				Vec2 direction = Particle_Attraction(&particles[i], &particles[j]);
				total.x += direction.x;
				total.y += direction.y;
			}
		}

		UpdateV(&particles[i], total);

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		Vec2 coords = TranslateCoords(particles[i].x, particles[i].y);
		SDL_Rect rect1 = { coords.x + offset.x, coords.y + offset.y, 64, 64 };
		SDL_Rect rect2 = { mouseX, mouseY, 1, 1 };
		if (CheckBounds(rect1, rect2)) {
			DrawParticleInfo(particles[i], coords);
		}
		DrawSprite(particles[i].sprite, coords.x, coords.y, 64, 64, 0, NULL);
	}
}
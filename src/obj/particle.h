#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <SDL2/SDL.h>
#include "../engine/vector.h"
#include "../engine/color.h"

typedef struct Resource {
	int water;
	int minerals;
} Resource;

typedef struct Particle {
	int id;
	char name[128];
	SDL_Rect sprite;
	Color color;
	long double mass;
	double x;
	double y;
	long double vx;
	long double vy;
	int radius;
	Resource resources;
} Particle;

Vec2 Particle_Attraction(Particle* self, Particle* other);

void UpdateV(Particle* p, Vec2 total);

void DrawParticleInfo(Particle particle, Vec2 coords);

void DrawParticles(Particle* particles, int c);

#endif

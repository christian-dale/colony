#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "../ecs/entity.h"

void Asteroid_Recycle(Asteroid* asteroid);

void Asteroid_Update(Asteroid* asteroid);

void Asteroid_Draw(Asteroid* asteroid);

#endif
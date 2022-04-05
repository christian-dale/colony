#ifndef MISC_H_
#define MISC_H_

#include <stdbool.h>
#include "engine/vector.h"

extern long double G;
extern long double AU;
extern long double SCALE;
extern long double timestep;

#define COUNT(a) (sizeof(a) / sizeof(*a))

int CalculateLevel(int health, int defence, int damage);

double Distance(double x1, double y1, double x2, double y2);

Vec2 ConvertCoords(double x, double y);

Vec2 TranslateCoords(double x, double y);

int RoundGrid(int gridSize, int n);

bool CheckBoundsCircle(Vec2 pos1, int r1, Vec2 pos2, int r2);

bool CheckBounds(SDL_Rect rect1, SDL_Rect rect2);

#endif
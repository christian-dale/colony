#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct Vec2 {
	long double x;
	long double y;
} Vec2;

extern Vec2 Vec2_Zero;

Vec2 Vec2Normalize(Vec2 vec);

double Vec2Distance(Vec2 vec1, Vec2 vec2);

#endif
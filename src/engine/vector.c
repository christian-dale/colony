#include "vector.h"
#include "math.h"

Vec2 Vec2_Zero = { 0, 0 };

Vec2 Vec2Normalize(Vec2 vec) {
	double w = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	vec.x /= w;
	vec.y /= w;

	return vec;
}

double Vec2Distance(Vec2 vec1, Vec2 vec2) {
	return sqrt(pow((vec2.x - vec1.x), 2) + pow(vec2.y - vec1.y, 2));
}
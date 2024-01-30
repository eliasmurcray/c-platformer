#include <stdbool.h>
#include <math.h>
#include "Collision.h"

float lerpf(float v1, float v2, float f) {
	return (v2 - v1) * f + v1;
}

float constrainf(float v, float min, float max) {
	return v > max ? max : v < min ? min : v;
}

float distf(float x1, float y1, float x2, float y2) {
	const float dx = x2 - x1;
	const float dy = y2 - y1;
	return sqrtf(dx * dx + dy * dy);
}

bool side_side_collide(float v1, float v2, float len) {
	const float dp = v2 - v1;
	return dp > -len && dp < len;
}

bool square_triangle_collide(Square square, EquilateralTriangle triangle) {
	const float dy = (triangle.y - square.y - square.s) / 2.f;
	const float HSIZE = square.s / 2.f;
	return side_side_collide(square.x, triangle.x, square.s) && side_side_collide(square.y, triangle.y, square.s) && square.x + HSIZE >= triangle.x - dy && square.x - HSIZE <= triangle.x + dy;
}

bool square_circle_collide(Square square, Circle circle) {
	const float HSIZE = square.s  / 2.f;
	const float closest_x = constrainf(circle.x, square.x - HSIZE, square.x + HSIZE);
	const float closest_y = constrainf(circle.y, square.y - HSIZE, square.y + HSIZE);
	return distf(closest_x, closest_y, circle.x, circle.y) < HSIZE / 2.f;
}

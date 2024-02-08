#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>

typedef struct {
	float x;
	float y;
	float s;
} Square;

typedef struct {
	float x;
	float y;
	float w;
	float h;
} Rect;

typedef struct {
	float x;
	float y;
	float w;
	float h;
} EquilateralTriangle;

typedef struct {
	float x;
	float y;
	float r;
} Circle;

float lerpf(float v1, float v2, float f);

float constrainf(float value, float min, float max);

float distf(float x1, float y1, float x2, float y2);

bool side_side_collide(float v1, float v2, float len);

bool square_triangle_collide(Square square, EquilateralTriangle triangle);

bool square_circle_collide(Square square, Circle circle);

bool rect_rect_collide(Rect *r0, Rect *r1);

#endif

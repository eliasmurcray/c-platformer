#include "Camera.h"

void Camera_update(Camera *camera, float px, float py) {
	camera->x += (px - camera->x) * camera->speed;
	camera->y += (py - camera->y) * camera->speed;
}

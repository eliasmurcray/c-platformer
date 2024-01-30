#include "Camera.h"

void Camera_update(Camera *cam, float px, float py) {
	cam->x += (px - cam->x) * cam->speed;
	cam->y += (py - cam->y) * cam->speed;
}

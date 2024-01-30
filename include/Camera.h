#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
	float x;
	float y;
	float speed;
} Camera;

void Camera_update(Camera* camera, float px, float py);

#endif

#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include "vector3.h"
#include "matrix4x4.h"
#include "pgmath.h"



class Camera
{
	
public:
	int width;
	int height;
	float fov_y;
	Vector3 view_from;
	Vector3 view_at;
	Vector3 up;
	Matrix4x4 view;
	float near_plane_distance;
	float far_plane_distance;

	Camera();
	Camera(const int width, const int height, const float fov_y,
		const Vector3 view_from, const Vector3 view_at);

	int update();
};


#endif
#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include "vector3.h"
#include "matrix4x4.h"
#include "pgmath.h"



class Camera
{
	
public:
	int width_; // image width (px)
	int height_; // image height (px)
	float fov_y_; // vertical field of view (radians)
	Vector3 view_from_; // eye
	Vector3 view_at_; // what ya lookin at
	Vector3 up_; // up vector
	Matrix4x4 view_; // idk
	float near_plane_distance_;
	float far_plane_distance_;
	Matrix4x4 M_c_w_;

	Camera();
	Camera(const int width, const int height, const float fov_y,
		const Vector3 view_from, const Vector3 view_at);

	int buildViewMatrix();
	int buildProjectionMatrix();

	int update();
};


#endif
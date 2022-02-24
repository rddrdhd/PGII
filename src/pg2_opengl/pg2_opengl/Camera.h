#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include "vector3.h"
#include "matrix4x4.h"
#include "pgmath.h"



class Camera
{
private:
	int width_; // image width (px)
	int height_; // image height (px)
	float fov_y_; // vertical field of view (radians)
	float fov_x_; // horizontal field of view (radians)
	Vector3 view_from_; // eye
	Vector3 view_at_; // what ya lookin at
	Vector3 view_direction_;
	Vector3 up_; // up vector
	float near_plane_distance_;
	float far_plane_distance_;
	// MVP = Model View Projection (matrixes)
	Matrix4x4 view_matrix_; // MCW
	Matrix4x4 projection_matrix_; //
	
public:

	Camera();
	Camera(const int width, const int height, const float fov_y,
		const Vector3 view_from, const Vector3 view_at, const float far_plane, const float near_plane);

	int buildViewMatrix();
	int buildProjectionMatrix();

	void update(int width, int height);
};


#endif
#include "pch.h"
#include "Camera.h"
#include <iostream>

Camera::Camera() {
	Camera(640, 480, 0.785f, Vector3(1, 1, 1), Vector3(1, 1, 1), 1.0f, 99.0f);
};


Camera::Camera(const int width, const int height, const float fov_y, const Vector3 view_from, const Vector3 view_at, const float far_plane, const float near_plane) {
	this->width_ = width;
	this->height_ = height;

	float aspect = (float)this->width_ / (float)this->height_;
	this->fov_y_ = fov_y;
	this->fov_x_ = 2 * atan(aspect * tan(this->fov_y_ / 2.0f));

	this->view_from_ = view_from;
	this->view_at_ = view_at;

	this->near_plane_distance_ = near_plane;
	this->far_plane_distance_ = far_plane;
	this->buildViewMatrix();
	this->buildProjectionMatrix();
}
int Camera::buildViewMatrix()
{
	// vektory pro transformaci prostoru z kameroveho do svetoveho (pravotocivy!)
	Vector3 z_c = this->view_from_ - this->view_at_; // smer pohledu kamery na prostor
	Vector3 x_c = this->up_.CrossProduct(z_c); // kolmice mezi pohledem a svislou osou
	Vector3 y_c = z_c.CrossProduct(x_c); //

	// Matice pro prevod mezi soustavami musi byt z jednotkovych vektoru !
	z_c.Normalize();
	x_c.Normalize();
	y_c.Normalize();


	this->view_matrix_ = Matrix4x4(x_c, y_c, z_c, this->view_from_); // TODO tohle neni dobre
	//printf(this->view_matrix_.toString().c_str()); jaj
	return 0;
}
int Camera::buildProjectionMatrix()
{
	// návod? https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix
	float n = this->near_plane_distance_;
	Vector3 v = this->view_at_;



	return 0;
}
;
void Camera::update(int width, int height) {
	/*** Vytvorte metodu Update, ktera provede výpocet vsech potrebnych matic (V, P) na zaklade aktualnich parametru kamery.
	Jednotlive matice a jejich kombinace (MVP pro transformaci vertexu do Clip Space, MV pro transformaci vertexu do
	Eye space, MVn pro transformaci normal do Eye Space apod.) pak muzete podle potreby predavat (pres ukazatel
	na prvni prvek - metoda data) ve vykreslovaci smycce pomoci funkce SetMatrix4x4 (gutils.cpp) aktualnimu shaderu.
	Zaroven ve vykreslovaci smycce zajistete, aby se kamera vhodnym zpusobem pohybovala. ***/
	
	// chceme buildnout MVP matici
	// MVP = P*(V*M)
	this->width_ = width;
	this->height_ = height;

	float aspect = (float)this->width_ / (float)this->height_;
	this->fov_x_ = 2 * atan(aspect * tan(this->fov_y_ / 2.0f));
	
	this->buildViewMatrix();
	this->buildProjectionMatrix();
	
}

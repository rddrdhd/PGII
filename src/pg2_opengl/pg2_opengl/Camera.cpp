#include "pch.h"

#include "Camera.h"

Camera::Camera() {
	Camera(640, 480, 0.785f, Vector3(1, 1, 1), Vector3(1, 1, 1));
};

Camera::Camera(const int width, const int height, const float fov_y, const Vector3 view_from, const Vector3 view_at) {
	width_ = width;
	height_ = height;
	fov_y_ = fov_y;

	view_from_ = view_from;
	view_at_ = view_at;
}
int Camera::buildViewMatrix()
{
		// vektory pro transformaci prostoru z kameroveho do svetoveho (pravotocivy!)
	view_from_.Normalize();
	view_at_.Normalize();
	Vector3 z_c = view_from_ - view_at_; // smer pohledu kamery na prostor
	Vector3 x_c = up_.CrossProduct(z_c); // kolmice mezi pohledem a svislou osou
	Vector3 y_c = z_c.CrossProduct(x_c); //

	// Matice pro prevod mezi soustavami musi byt z jednotkovych vektoru !
	z_c.Normalize();
	x_c.Normalize();
	y_c.Normalize();

	view_matrix = Matrix4x4(x_c, y_c, z_c, view_from_); // TODO tohle neni dobre
	return 0;
}
int Camera::buildProjectionMatrix()
{
	float n = near_plane_distance_;

	return 0;
}
;
int Camera::update() {
	/*** Vytvorte metodu Update, ktera provede výpocet vsech potrebnych matic (V, P) na zaklade aktualnich parametru kamery.
	Jednotlive matice a jejich kombinace (MVP pro transformaci vertexu do Clip Space, MV pro transformaci vertexu do
	Eye space, MVn pro transformaci normal do Eye Space apod.) pak muzete podle potreby predavat (pres ukazatel
	na prvni prvek - metoda data) ve vykreslovaci smycce pomoci funkce SetMatrix4x4 (gutils.cpp) aktualnimu shaderu.
	Zaroven ve vykreslovaci smycce zajistete, aby se kamera vhodnym zpusobem pohybovala. ***/
	
	// chceme buildnout MVP matici
	// MVP = P*(V*M)
	return 1;
}

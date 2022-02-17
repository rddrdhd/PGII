#include "pch.h"

#include "Camera.h"

Camera::Camera() {
	Camera(640, 480, 0.785f, Vector3(1, 1, 1), Vector3(1, 1, 1));
};

Camera::Camera(const int width, const int height, const float fov_y, const Vector3 view_from, const Vector3 view_at) {
};
int Camera::update() {
	/*** Vytvorte metodu Update, ktera provede výpocet vsech potrebnych matic (V, P) na zaklade aktualnich parametru kamery.
	Jednotlive matice a jejich kombinace (MVP pro transformaci vertexu do Clip Space, MV pro transformaci vertexu do
	Eye space, MVn pro transformaci normal do Eye Space apod.) pak muzete podle potreby predavat (pres ukazatel
	na prvni prvek - metoda data) ve vykreslovaci smycce pomoci funkce SetMatrix4x4 (gutils.cpp) aktualnimu shaderu.
	Zaroven ve vykreslovaci smycce zajistete, aby se kamera vhodnym zpusobem pohybovala. ***/

	return 1;
}

#include "pch.h"
#include "Rasterizer.h"
#include "Camera.h"

Rasterizer::Rasterizer(int width, int height, float fovY, Vector3 viewFrom, Vector3 viewAt) {
	this->camera = Camera(width, height, fovY, viewFrom, viewAt, 1.0f, 99.0f);

	//this->light = std::make_shared<Directional>(Vector3{ -200, -300, 200 }, Vector3{ 0, 0, 0 }, deg2rad(45), 1024, 1024);
	//this->light = std::make_shared<Directional>(Vector3 {50, 0, 0}, Vector3 {0, 0, 0}, deg2rad(45), 1024, 1024);
}
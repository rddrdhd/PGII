#include "pch.h"
#include "Rasterizer.h"
#include "Camera.h"

Rasterizer::Rasterizer(int width, int height, float fovY, Vector3 viewFrom, Vector3 viewAt) {
	this->camera = Camera(width, height, fovY, viewFrom, viewAt, 1.0f, 99.0f);

	//this->light = std::make_shared<Directional>(Vector3{ -200, -300, 200 }, Vector3{ 0, 0, 0 }, deg2rad(45), 1024, 1024);
	//this->light = std::make_shared<Directional>(Vector3 {50, 0, 0}, Vector3 {0, 0, 0}, deg2rad(45), 1024, 1024);
}

/* OpenGL check state */
bool Rasterizer::check_gl(const GLenum error)
{
	if (error != GL_NO_ERROR)
	{
		//const GLubyte * error_str;
		//error_str = gluErrorString( error );
		//printf( "OpenGL error: %s\n", error_str );

		return false;
	}

	return true;
}
int Rasterizer::loadMash(const std::string& file_name) {
	return 0;
}
int Rasterizer::initBuffer() {
	return 0;
}
int Rasterizer::initShaders() {
	return 0;
}
int Rasterizer::mainLoop() {
	return 0;
}
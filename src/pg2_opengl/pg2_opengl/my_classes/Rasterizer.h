#pragma once
#ifndef RASTERIZE_H_
#define RASTERIZE_H_
#include "Camera.h"
#include "Vertex.h"
void glfw_callback_1(const int error, const char* description);
bool check_gl_1(const GLenum error = glGetError());
void GLAPIENTRY gl_callback_1(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param);
void framebuffer_resize_callback_1(GLFWwindow* window, int width, int height);

class Rasterizer
{
private:
	Camera camera;
	GLFWwindow* window;
	std::vector<Vertex> vertices;
	GLuint vao;
	GLuint vbo;

	//SceneGraph scene;
	//MaterialLibrary materials;

public:
	Rasterizer(int width, int height, float fovY, Vector3 viewFrom, Vector3 viewAt);

	//copypaste inint kontext
	int initOpenGL(int width, int height);
	// nahradit to trojuhelnikove pole 3 bodu za to, co nacteme loadMash.
	int loadMesh(const std::string& file_name); // load scene - nacist treba yaml se seznamem .obj souboru atd...
	int initBuffer(); // VBO atd
	int initShaders(); // nazvy files ve kterych mame shadery, ted mame dva. Podle tutorialus
	int mainLoop(); // z tutorialu
	std::vector<Vertex> getVertices(){ return this->vertices; };
	
};
#endif

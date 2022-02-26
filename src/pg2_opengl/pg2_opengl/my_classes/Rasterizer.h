#pragma once
#ifndef RASTERIZE_H_
#define RASTERIZE_H_
#include "pch.h"
#include "Camera.h"
class Rasterizer
{
private:
	Camera camera;
public:
	Rasterizer(int width, int height, float fovY, Vector3 viewFrom, Vector3 viewAt);

	//copypaste inint kontext
	int initOpenGL(int width, int height);
	// nahradit to trojuhelnikove pole 3 bodu za to, co nacteme loadMash.
	int loadMash(const std::string& file_name); // load scene - nacist treba yaml se seznamem .obj souboru atd...
	int initBuffer(); // VBO atd
	int initShaders(); // nazvy files ve kterych mame shadery, ted mame dva. Podle tutorialus
	int mainLoop(); // z tutorialu
	//SceneGraph scene;
	//MaterialLibrary materials;

	
};
#endif

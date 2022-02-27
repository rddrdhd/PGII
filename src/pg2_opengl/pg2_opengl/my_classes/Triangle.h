#pragma once
#include "./Vertex.h"
class Surface;
class Triangle
{
public:
	Triangle() {}
	Triangle(Vertex& v0,Vertex& v1,Vertex& v2, Surface* surface = NULL);

	Vertex vertex(const int i);
	void setVertex(const int i, Vertex& v) { this->vertices_[i] = v; };
private:
	Vertex vertices_[3];
};


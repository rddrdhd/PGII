#pragma once
#include "./Vertex.h"
class Surface;
class Triangle
{
public:
	Triangle() {}
	Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, Surface* surface = NULL);

	Vertex vertex(const int i);
private:
	Vertex vertices_[3];
};


#include "pch.h"
#include "Triangle.h"

Triangle::Triangle(Vertex& v0,Vertex& v1,Vertex& v2, Surface* surface)
{
	vertices_[0] = v0;
	vertices_[1] = v1;
	vertices_[2] = v2;
}

Vertex Triangle::vertex(const int i)
{
	return vertices_[i];
}
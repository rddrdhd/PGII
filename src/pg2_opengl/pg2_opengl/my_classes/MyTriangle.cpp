#include "pch.h"
#include "MyTriangle.h"

MyTriangle::MyTriangle(const MyVertex& v0, const MyVertex& v1, const MyVertex& v2, Surface* surface)
{
	vertices_[0] = v0;
	vertices_[1] = v1;
	vertices_[2] = v2;
}

MyVertex MyTriangle::vertex(const int i)
{
	return vertices_[i];
}



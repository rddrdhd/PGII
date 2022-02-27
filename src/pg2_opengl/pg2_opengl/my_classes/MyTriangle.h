#ifndef MYTRIANGLE_H_
#define MYTRIANGLE_H_

#include "MyVertex.h"

class MyTriangle
{
public:
	MyTriangle(){}
	MyTriangle(const MyVertex& v0, const MyVertex& v1, const MyVertex& v2, Surface* surface = NULL);

	MyVertex vertex(const int i);
private:
	MyVertex vertices_[3];
};

#endif
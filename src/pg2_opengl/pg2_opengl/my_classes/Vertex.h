#pragma once
#include "vector3.h"
struct Coord2f { float u, v; }; // texture coord structure
#define NO_TEXTURE_COORDS 1
struct Vertex {
public:
	Vector3 position; // pozice vertexu
	Vector3 normal; // normala vertexu
	Vector3 color; // RGBbarva vertexu <0,1>^3
	Coord2f texture_coords[NO_TEXTURE_COORDS]; // texturovaci souradnice
	Vector3 tangent; // prvni osa souradneho systemu tangnta-bitangenta-normala

	char pad_[8];  // doplni na 64 bitu, aby se tam vesel 32b ukazatel

	// vychozi konstruktor
	Vertex() { }

	// obecny konstruktor
	Vertex(const Vector3 position, const Vector3 normal, Vector3 color, Coord2f* texture_coords = NULL);

};


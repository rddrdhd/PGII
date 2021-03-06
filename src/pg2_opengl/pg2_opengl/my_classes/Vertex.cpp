#include "pch.h"
#include "Vertex.h"

Vertex::Vertex(const Vector3 position, const Vector3 normal, Vector3 color, Coord2f* texture_coords)
{
	this->position = position;
	this->normal = normal;
	this->color = color;

	if (texture_coords != NULL)
	{
		for (int i = 0; i < NO_TEXTURE_COORDS; ++i)
		{
			this->texture_coords[i] = texture_coords[i];
		}
	}
}
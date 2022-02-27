#include "pch.h"
#include "Surface.h"


Surface* BuildSurface(const std::string& name, std::vector<MyVertex>& face_vertices)
{
	const int no_vertices = static_cast<int>(face_vertices.size());

	assert((no_vertices > 0) && (no_vertices % 3 == 0));

	const int no_triangles = no_vertices / 3;

	Surface* surface = new Surface(name, no_triangles);

	// kopirovani dat
	for (int i = 0; i < no_triangles; ++i)
	{
		surface->get_triangles()[i] = MyTriangle(face_vertices[i * 3],
			face_vertices[i * 3 + 1], face_vertices[i * 3 + 2], surface);
	}

	return surface;
}

Surface::Surface()
{
	this->n_ = 0;
	this->triangles_ = NULL;
}

Surface::Surface(const std::string& name, const int n)
{
	assert(n > 0);

	this->name_ = name;

	this->n_ = n;
	this->triangles_ = new MyTriangle[n_];
}

MyTriangle& Surface::get_triangle(const int i)
{
	return this->triangles_[i];
}

MyTriangle* Surface::get_triangles()
{
	return this->triangles_;
}

std::string Surface::get_name()
{
	return this->name_;
}

int Surface::no_triangles()
{
	return this->n_;
}

int Surface::no_vertices()
{
	return 3 * this->n_;
}

void Surface::set_material(Material* material)
{
	this->material_ = material;
}

Material* Surface::get_material() const
{
	return this->material_;
}
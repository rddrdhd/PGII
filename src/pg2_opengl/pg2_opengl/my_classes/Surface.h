#ifndef SURFACE_H_
#define SURFACE_H_

#include "MyVertex.h"
#include "Material.h"
#include "MyTriangle.h"

class Surface {
public:
	Surface();
	Surface(const std::string& name, const int n);
	MyTriangle& get_triangle(const int i);
	MyTriangle* get_triangles();
	std::string get_name();
	int no_triangles();
	int no_vertices();
	void set_material(Material* material);
	Material* get_material() const;
private:
	int n_; // pocet trojuhelniku v siti
	MyTriangle* trinagles_{ nullptr }; // trojuhelnikova sit
	std::string name_{ "unknown" }; // nazev plochy
	Material* material{ nullptr }; // material plochy
};

Surface* BuildSurface(const std::string& name, std::vector<MyVertex>& face_vertices);

#endif
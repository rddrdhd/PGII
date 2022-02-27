#pragma once
#include "./Vertex.h"
#include "./Material.h"
#include "./Triangle.h"

class Surface {
public:
	Surface();
	Surface(const std::string& name, const int n);
	~Surface();
	Triangle& get_triangle(const int i);
	Triangle* get_triangles();
	std::string get_name();
	int no_triangles();
	int no_vertices();
	void set_material(Material* material);
	Material* get_material() const;
private:
	int n_; // pocet trojuhelniku v siti
	Triangle * triangles_; // trojuhelnikova sit
	std::string name_; // nazev plochy
	Material * material_; // material plochy
};
Surface* BuildSurface(const std::string& name, std::vector<Vertex>& face_vertices);

//Surface* BuildSurface(const std::string& name, std::vector<Vertex>& face_vertices);

#include "pch.h"
#include "Scene.h"

#include "objloader.h"
#include "matrix3x3.h"
#include "../glutils.h"
#include <random>

void Scene::loadMaterials() {
	for (auto material : materials_) {
		GLMaterial m;
		/*
		// DIFUSE
		auto tex_diffuse = material->texture(Material::kDiffuseMapSlot);
		if (tex_diffuse) {
			GLuint id = 0;
			CreateBindlessTexture(id, m.tex_diffuse_handle, tex_diffuse->width(), tex_diffuse->height(), tex_diffuse->data());
			m.albedo = Color3f({ 1, 1, 1 });
		}
		else {
			GLuint id = 0;
			GLubyte data[] = { 255, 255, 255, 255 }; // opaque white
			CreateBindlessTexture(id, m.tex_diffuse_handle, 1, 1, data);
			m.albedo = material->diffuse();
		}

		// ROUGHNESS, METALNESS
		auto tex_rma = material->texture(Material::kRoughnessMapSlot);
		if (tex_rma) {
			GLuint id = 0;
			CreateBindlessTexture(id, m.tex_rma_handle, tex_rma->width(), tex_rma->height(), tex_rma->data());
			m.rma = Color3f({ 1, 1, 1 });
		}
		else {
			GLuint id = 0;
			GLubyte data[] = { 255, 255, 255, 255 }; // opaque white
			CreateBindlessTexture(id, m.tex_rma_handle, 1, 1, data);
			m.rma = Color3f({ material->roughness_, material->metallicness, 1.0f });
		}

		// NORMAL MAP
		auto tex_norm = material->texture(Material::kNormalMapSlot);
		if (tex_norm) {
			GLuint id = 0;
			CreateBindlessTexture(id, m.tex_normal_handle, tex_norm->width(), tex_norm->height(), tex_norm->data());
			m.normal = Color3f({ 1, 1, 1 });
		}
		else {
			GLuint id = 0;
			GLubyte data[] = { 255, 255, 255, 255 }; // opaque white
			CreateBindlessTexture(id, m.tex_normal_handle, 1, 1, data);
			m.normal = Color3f({ 0, 0, 1 });
		}
		*/
		this->pointerIndexMap.emplace(material, this->materials.size());
		this->materials.push_back(m);
	}
}

void Scene::loadTextures() {
	for (auto surface : surfaces_) {
		auto it = this->pointerIndexMap.find(surface->get_material());
		if (it == this->pointerIndexMap.end()) {
			printf("material not found");
		}

		int mat_index = it->second;


		for (int i = 0, k = 0; i < surface->no_triangles(); i++) {
			Triangle& triangle = surface->get_triangle(i);

			auto dU1 = triangle.vertex(1).texture_coords->u - triangle.vertex(0).texture_coords->u;
			auto dV1 = triangle.vertex(1).texture_coords->v - triangle.vertex(0).texture_coords->v;

			auto dU2 = triangle.vertex(2).texture_coords->u - triangle.vertex(0).texture_coords->u;
			auto dV2 = triangle.vertex(2).texture_coords->v - triangle.vertex(0).texture_coords->v;

			auto e1 = triangle.vertex(1).position - triangle.vertex(0).position;
			auto e2 = triangle.vertex(2).position - triangle.vertex(0).position;

			auto t = (dV2 * e1 - dV1 * e2) / (dU1 * dV2 - dU2 * dV1);
			t.Normalize();

			for (int j = 0; j < 3; j++, k += 3) {
				const Vertex& vertex = triangle.vertex(j);

				verticies.push_back(MyVertex{
					// position
					vertex.position.x,
					vertex.position.y,
					vertex.position.z,
					// normal
					vertex.normal.x,
					vertex.normal.y,
					vertex.normal.z,
					// tangent
					t.x, //vertex.tangent.x,
					t.y, //vertex.tangent.y,
					t.z, //vertex.tangent.z,
					// texture coordinates
					vertex.texture_coords->u,
					vertex.texture_coords->v,
					// material index
					mat_index
					});
			}
		}
	}

	this->vertex_stride = sizeof(MyVertex);
}

Scene::Scene(std::string& file_name, std::string& background_file) {
	this->background = std::make_shared<Texture3f>(background_file);

	//const int no_surfaces = LoadOBJ(file_name.c_str(), this->surfaces_, this->materials_);

	this->loadMaterials();
	this->loadTextures();


}
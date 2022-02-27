#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Vector3.h"
#include "Texture.h"
#include "Structs.h"
#include <utility>

//maximalni pocet textur
#define NO_TEXTURES 6

//index lomu vzduchu za normalniho tlaku
#define IOR_AIR 1.000293f

//index lomu vody
#define IOR_WATER 1.33f

//index lomu skla
#define IOR_GLASS 1.5f

//typy shaderu
enum class Shader : char { NORMAL = 1, LAMBERT = 2, PHONG = 3, GLASS = 4, PBR = 5, MIRROR = 6, TS = 7, CT = 8 };

class Material
{
public:
	//inicializuje vychozi sedy material
	Material();
	// inicializuje material podle nastaveni
	// nazev, barva prostredi, barva rozptylu, barva odrazu, barva emise, lesklost, 
	// index lomu, shader, pole ukazatelu na textury, delka pole
	Material(std::string& name, const Color3f& ambient, const Color3f& diffuse,
		const Color3f& specular, const Color3f& emission, const float reflectivity,
		const float shininess, const float ior, const Shader shader,
		Texture3u** textures = NULL, const int no_textures = 0);

	~Material();

	void set_name(const char* name);

	std::string name() const;

	void set_texture(const int slot, Texture3u* texture);

	Texture3u* texture(const int slot) const;

	Shader shader() const;

	void set_shader(Shader shader);

	Color3f ambient(const Coord2f* tex_coord = nullptr) const;
	Color3f diffuse(const Coord2f* tex_coord = nullptr) const;
	Color3f specular(const Coord2f* tex_coord = nullptr) const;
	Color3f bump(const Coord2f* tex_coord = nullptr) const;
	float roughness(const Coord2f* tex_coord = nullptr) const;

	Color3f emission(const Coord2f* tex_coord = nullptr) const;

public:
	Color3f ambient_; // RGB barva prostredi <0,1>
	Color3f diffuse_; // RGB barva rozptylu <0,1>
	Color3f specular_; // RGB barva odrazu <0,1>

	Color3f emission_; // RGB barva emise <0,1>

	float shininess; // Koeficient lesklosti
	float roughness_; // Koeficient drsnosti
	float metallicness; // Koeficient kovovosti
	float reflectivity; // Koeficient odrazivosti
	float ior; // Index lomu

	static const char kDiffuseMapSlot; // Cislo slotu difuzni textury
	static const char kSpecularMapSlot;  // Cislo slotu spekularni textury
	static const char kNormalMapSlot; // Cislo slotu normalove textury
	static const char kOpacityMapSlot; // Cislo slotu transparentni textury
	static const char kRoughnessMapSlot; // Cislo slotu textury drsnosti
	static const char kMetallicnessMapSlot; // Cislo slotu textury kovovosti

	bool hasTexture(const char slot);

private:
	Texture3u* textures_[NO_TEXTURES]; // pole ukazatelu na textury
	/*
	slot 0 - diffuse map + alpha
	slot 1 - specular map + opaque alpha
	slot 2 - normal map
	slot 3 - transparency map
	*/

	std::string name_;

	Shader shader_{ Shader::NORMAL }; // typ shaderu
};

#endif
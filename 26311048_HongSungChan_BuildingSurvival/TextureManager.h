#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "glc2d.h"

struct Texture
{
	VEC2 m_scaling;
	int m_texture;
};

class TextureManager
{
private:
	std::vector<Texture> m_textures;
	std::unordered_map<std::string, int> m_textureSaveLocs;

public:
	TextureManager();

	int Init();

	int AddTexture(const std::string& key, const std::string& fileName, const VEC2& scaling = VEC2(1.0f, 1.0f));
	Texture GetTexture(const std::string& key) const;
};

extern TextureManager* GetTextureManager();
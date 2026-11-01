#include "TextureManager.h"

static TextureManager* g_textureManager;

TextureManager::TextureManager()
{
	g_textureManager = this;
}

int TextureManager::Init()
{
	//Player Animation
	 if (0 > AddTexture("Player_Idle", "Resource/Character/Player/Idle.png"))
		return -1;
	 if (0 > AddTexture("Player_Death", "Resource/Character/Player/Death.png"))
		 return -1;
	 if (0 > AddTexture("Player_Walk", "Resource/Character/Player/Walk.png"))
		 return -1;

	 if (0 > AddTexture("Zombie_Idle", "Resource/Character/Zombie/Idle.png"))
		 return -1;
	 if (0 > AddTexture("Zombie_Death", "Resource/Character/Zombie/Death.png"))
		 return -1;
	 if (0 > AddTexture("Zombie_Walk", "Resource/Character/Zombie/Walk.png"))
		 return -1;

	return 0;
}

int TextureManager::AddTexture(const std::string& key, const std::string& fileName, const VEC2& scaling)
{
	if (m_textureSaveLocs.find(key) != m_textureSaveLocs.end())
		return 0;

	int texture = g2_TextureLoad(fileName.c_str());
	if (0 > texture)
		return -1;

	m_textures.push_back(Texture{ scaling, texture });
	m_textureSaveLocs[key] = m_textures.size() - 1;

	return 0;
}

Texture TextureManager::GetTexture(const std::string& key) const
{
	auto index = m_textureSaveLocs.find(key);
	if (index == m_textureSaveLocs.end())
		return Texture{ VEC2(1.0f, 1.0f), -1 };

	return m_textures[index->second];
}

TextureManager* GetTextureManager()
{
	return g_textureManager;
}
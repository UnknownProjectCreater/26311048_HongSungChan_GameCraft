#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "glc2d.h"

class SoundManager
{
private:
	std::vector<int> m_sounds;
	std::unordered_map<std::string, int> m_soundSaveLocs;

public:
	SoundManager();

	int Init();

	int AddSound(const std::string& key, const std::string& fileName);
	int GetSound(const std::string& key) const;
};

extern SoundManager* GetSoundManager();
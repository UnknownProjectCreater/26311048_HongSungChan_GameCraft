#include "SoundManager.h"

static SoundManager* g_soundManager;

SoundManager::SoundManager()
{
	g_soundManager = this;
}

int SoundManager::Init()
{
	if (0 > AddSound("Bgm_Intro", "Resource/Audio/Music/Primordial-Soup-BASE.wav"))
		return -1;
	if (0 > AddSound("Bgm_Wave", "Resource/Audio/Music/Dark-Portents-MYSTERIOUS-TRAVELER.wav"))
		return -1;
	if (0 > AddSound("Bgm_Boss", "Resource/Audio/Music/Clement-Panchout-MW-FUP-Chaotic Boss.wav"))
		return -1;

	return 0;
}

int SoundManager::AddSound(const std::string& key, const std::string& fileName)
{
	if (m_soundSaveLocs.find(key) != m_soundSaveLocs.end())
		return 0;

	int sound = g2_SoundLoad(fileName.c_str());
	if (0 > sound)
		return -1;

	m_sounds.push_back(sound);
	m_soundSaveLocs[key] = m_sounds.size() - 1;

	return 0;
}

int SoundManager::GetSound(const std::string& key) const
{
	auto index = m_soundSaveLocs.find(key);
	if (index == m_soundSaveLocs.end())
		return -1;

	return m_sounds[index->second];
}

SoundManager* GetSoundManager()
{
	return g_soundManager;
}
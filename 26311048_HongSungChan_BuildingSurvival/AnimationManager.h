#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "glc2d.h"

struct AnimClip
{
	std::vector<RECT> m_frames;
	float m_frameTime = 0.1f;
	bool m_loop = true;
};

class Animator
{
private:
	std::unordered_map<std::string, std::shared_ptr<const AnimClip>> m_clips;
	const AnimClip* m_currentClip = nullptr;
	std::string m_currentKey;
	int m_frame = 0;
	float m_elapsed = 0.0f;
	bool m_finished = false;

public:
	int Add(const std::string& key, std::shared_ptr<const AnimClip> clip);
	int Play(const std::string& key);
	int Update(float deltaTime);
	const RECT& CurrentFrame() const;
	bool IsFinished() const;
};

class AnimationManager
{
private:
	std::unordered_map<std::string, std::shared_ptr<const AnimClip>> m_clips;

public:
	std::shared_ptr<const AnimClip> LoadClip(const std::string& key, int frameWidth, int frameHeight, int frameCount, float frameTime, bool loop, int row = 0);
	std::shared_ptr<const AnimClip> GetClip(const std::string& key) const;
};

extern AnimationManager* GetAnimationManager();
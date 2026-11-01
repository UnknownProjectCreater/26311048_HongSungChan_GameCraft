#include "AnimationManager.h"

static AnimationManager g_animationManager;

AnimationManager* GetAnimationManager()
{
	return &g_animationManager;
}

int Animator::Add(const std::string& key, std::shared_ptr<const AnimClip> clip)
{
	if (clip == nullptr || clip->m_frames.empty() || clip->m_frameTime <= 0.0f)
		return -1;

	m_clips[key] = clip;

	return 0;
}

int Animator::Play(const std::string& key)
{
	if (m_currentKey == key)
		return -1;

	auto clip = m_clips.find(key);
	m_currentClip = (clip != m_clips.end()) ? clip->second.get() : nullptr;
	m_currentKey = key;
	m_frame = 0;
	m_elapsed = 0.0f;
	m_finished = false;

	return 0;
}

int Animator::Update(float deltaTime)
{
	if (m_currentClip == nullptr || m_finished)
		return -1;

	m_elapsed += deltaTime;

	while (m_elapsed >= m_currentClip->m_frameTime)
	{
		m_elapsed -= m_currentClip->m_frameTime;

		if (m_frame + 1 < m_currentClip->m_frames.size())
		{
			m_frame++;
		}
		else if (m_currentClip->m_loop)
		{
			m_frame = 0;
		}
		else
		{
			m_finished = true;
			break;
		}
	}

	return 0;
}

const RECT& Animator::CurrentFrame() const
{
	static const RECT empty{};

	if (m_currentClip == nullptr)
		return empty;

	return m_currentClip->m_frames[m_frame];
}

bool Animator::IsFinished() const
{
	return m_currentClip == nullptr || m_finished;
}

std::shared_ptr<const AnimClip> AnimationManager::LoadClip(const std::string& key, int frameWidth, int frameHeight, int frameCount, float frameTime, bool loop, int row)
{
	auto loaded = m_clips.find(key);
	if (loaded != m_clips.end())
		return loaded->second;

	auto clip = std::make_shared<AnimClip>();
	clip->m_frameTime = frameTime;
	clip->m_loop = loop;

	for (int i = 0; i < frameCount; i++)
		clip->m_frames.push_back(RECT{ i * frameWidth, row * frameHeight, (i + 1) * frameWidth, (row + 1) * frameHeight });

	m_clips[key] = clip;

	return clip;
}

std::shared_ptr<const AnimClip> AnimationManager::GetClip(const std::string& key) const
{
	auto loaded = m_clips.find(key);
	if (loaded == m_clips.end())
		return nullptr;

	return loaded->second;
}
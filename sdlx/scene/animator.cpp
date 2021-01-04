#include "animator.h"

using namespace sdlgx::scene;

Animator::Animator()
{
}


Animator::~Animator()
{
}

void Animator::Set(int fps)
{
	m_timeBetweenFrames = 1.0f / (float)fps;
	m_timeSinceLastFrame = m_timeBetweenFrames;
}

bool Animator::Update(float elapsed)
{
	m_timeSinceLastFrame -= elapsed;
	if (m_timeSinceLastFrame <= 0) {
		m_timeSinceLastFrame = m_timeBetweenFrames;
		return true;
	}
	return false;
}

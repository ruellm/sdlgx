#pragma once
#include "sdlgx_common.h"
namespace sdlgx {
	namespace scene {
		class SDLGX_API Animator
		{
		public:
			Animator();
			~Animator();
			void Set(int fps);
			bool Update(float elapsed);
		private:
			float m_timeBetweenFrames;
			float m_timeSinceLastFrame;
		};
	}
}

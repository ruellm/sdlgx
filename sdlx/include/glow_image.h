#pragma once
#include "sdlgx_common.h"
#include "texture.h"
#include "object_base.h"

namespace sdlgx {
	namespace scene {

		class SDLGX_API GlowImage 
			: public sdlgx::core::ObjectBase
		{
		public:
			GlowImage();
			~GlowImage();

			void Load(int resid);
			void OnUpdate(float elapsed);
			void OnDraw(int x, int y);

			int GLOW_ALPHA_ACCEL;
		
		private:
			
			Texture _texture;
			float _speed;
			float _alpha;
			int _dir;			
		};
	}
}


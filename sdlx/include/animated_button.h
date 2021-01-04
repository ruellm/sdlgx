#pragma once

#include "sdlgx_common.h"
#include "uibase.h"
#include "sprite_sheet.h"

namespace sdlgx {
	namespace gui {

		class SDLGX_API AnimatedButton : public UIBase
		{
		public:
			AnimatedButton();
			~AnimatedButton();

			void Load(sdlgx::scene::SpriteSheet* idle, sdlgx::scene::SpriteSheet* hover);
			virtual void Select();
			virtual void UnSelect();
			virtual void OnUpdate(float elapsed);
			virtual void OnDraw();

		private:
			sdlgx::scene::SpriteSheet* _idle;
			sdlgx::scene::SpriteSheet* _hover;
			sdlgx::scene::SpriteSheet* _current;
		};
	}
}

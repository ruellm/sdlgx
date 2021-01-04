#pragma once
#include "button.h"

namespace sdlgx {
	namespace gui {
		class SDLGX_API TextButton : public sdlgx::gui::Button
		{
		public:
			TextButton();
			~TextButton();

			void Load(char* text, int size,
				int fontid,
				SDL_Color idle,
				SDL_Color hover,
				SDL_Color clicked);

		private:
			SDL_Color _idleColor;
			SDL_Color _hoverColor;
			SDL_Color _clickedColor;
		};
	}
}


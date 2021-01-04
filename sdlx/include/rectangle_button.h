#pragma once
#include "sdlgx_common.h"
#include "uibase.h"
#include "button.h"
#include "texture.h"

namespace sdlgx {
	namespace gui {
		
		class SDLGX_API RectangleButton : public Button {
		public:
			RectangleButton();
			~RectangleButton();

			void Set(int x, int y, int width, int height, bool fill = false);
			void SetFillColor(Uint8 r, Uint8 g, Uint8 b);
			void SetRectColor(Uint8 r, Uint8 g, Uint8 b);
			void SetHighlightColor(Uint8 r, Uint8 g, Uint8 b);
			void IsFill(bool fill);

		private:
			virtual void OnUpdate(float elapsed);
			virtual void OnDraw();
			virtual void OnMouseEnterMove(int x, int y);
			virtual void OnMouseLeave();

			SDL_Color _rect_color;
			SDL_Color _fill_color;
			SDL_Color _highlight_color;

			bool _with_fill;

		protected:
			virtual void DrawText() = 0;
			bool _selected;
		};
	}
}
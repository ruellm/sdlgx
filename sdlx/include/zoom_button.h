#pragma once
#include "sdlgx_common.h"
#include "uibase.h"
#include "texture.h"
#include "button.h"

namespace sdlgx {
	namespace gui {

		class SDLGX_API ZoomButton 
			: public Button
		{
		public:
			ZoomButton();
			~ZoomButton();

			void Load(short resid);
			void SetAcceleration(float value);
			void SetScaleUp(float value);
			float GetScaleUp();
			virtual void OnUpdate(float elapsed);
			virtual void OnDraw();
			virtual void OnMouseEnterMove(int x, int y);
			virtual void OnMouseLeave();
			virtual bool OnMouseUp(int x, int y);

			int GetNewX();
			int GetNewY();
			int GetState();

		private:
			sdlgx::scene::Texture* _icon;
			bool _selected;
			float _scaled_up;
			short _zooming_flag;
			short _state;
			float _alpha;
			float _size_accel;
			int _original_width;
			int _original_height;
			int _target_width;
			int _target_height;
			float _new_x;
			float _new_y;
		};
	}
}

#pragma once

#include "sdlgx_common.h"
#include "uibase.h"
#include "texture.h"
#include "resource.h"

namespace sdlgx {
	namespace gui {

		class IButtonEventHandler;

		class SDLGX_API Button 
			: public UIBase
		{
		public:
			Button();
			virtual ~Button();

			void Load(short idle, short highlight, 
				short clicked=RESOURCE_ID_NONE, short disable=RESOURCE_ID_NONE);
			
			void SetHoldThreshold(float value);
			void SetHandler(IButtonEventHandler* handler);
			virtual void OnMouseEnterMove(int x, int y);
			virtual void OnMouseLeave();
			virtual void SetEnable(bool value);
			virtual bool OnMouseDown(int x, int y);
			virtual bool OnMouseUp(int x, int y);
			virtual bool OnMouseUpOut(int x, int y);
			virtual void OnDraw();
			virtual void OnUpdate(float elapsed);

		protected:
			bool _select;
			bool _clicked;
			IButtonEventHandler* _handler;
			Uint32 _lastTime;
			float _holdThreshold;

			sdlgx::scene::Texture* _currentImg;
			sdlgx::scene::Texture* _highLightImg;
			sdlgx::scene::Texture* _idleImg;
			sdlgx::scene::Texture* _clickdImg;
			sdlgx::scene::Texture* _disableImg;
					
		};

		class IButtonEventHandler {
		public:
			virtual void OnButtonClick(Button* b) = 0;
			virtual void OnButtonHold(Button*b) {}
		};
	}
}


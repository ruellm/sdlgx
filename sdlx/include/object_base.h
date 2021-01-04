#pragma once

#include "sdlgx_common.h"

namespace sdlgx {
	namespace core {
		class SDLGX_API ObjectBase
		{
		public:
			ObjectBase();
			~ObjectBase();

			virtual void SetCoordinates(float x, float y);
			virtual void OnUpdate(float elapsed) {}
			virtual void OnDraw() {}
			virtual void SetVisible(bool value);

			float _x;
			float _y;
			bool _visible;
			int _width;
			int _height;
			int _id;

			int GetWidth();
			int GetHeight();

			int GetID() const;
			void SetID(int id);

		};

	}
}
//Ported from Nightmare Javascript Engine
//Author: Ruell Magpayo <ruellm@yahoo.com>
// Created Oct 01, 2012 ported Aug 8,2016
#pragma once
#include "sdlgx_common.h"
#include "animator.h"
#include "texture.h"

namespace sdlgx {
	namespace scene {

		//forward declaration
		class SDLGX_API SpriteSheet;

		class SDLGX_API ISpriteCallback {
		public:
			virtual void OnAnimationComplete(SpriteSheet* sprite) = 0;
		};

		class SDLGX_API SpriteSheet : public Texture
		{
		public:
			SpriteSheet();
			virtual ~SpriteSheet();

			void SetFPS(int fps);
			void SetLoop(bool flag);
			void Set(int frame_count, int fps, bool loop);			
			void SetCallbackHandler(ISpriteCallback* callback);
			virtual void SetAlpha(unsigned char alpha);

			int GetFrameWidth();

			virtual void Reset();
			virtual void OnUpdate(float elapsed);
			virtual void OnDraw(int x, int y);
			virtual void OnDrawFlip(int x, int y, SDL_RendererFlip flip);
			virtual void OnDraw();
			
		protected:
			// Total animation frames
			int _frameCount;

			// current frame
			int _currentFrame;

			// animation frame width
			int _frameWidth;

			// the loop flag, if this animation should loop
			bool _bLoop;
		
			//we use animator to interpolate animation frame
			Animator _animator;

			bool _called;

			ISpriteCallback* _handler;
		};
	}
}


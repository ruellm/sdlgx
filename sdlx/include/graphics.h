#pragma once
#include "sdlgx_common.h"

namespace sdlgx {
	namespace core {

		struct GraphicsSetup {
			int width;
			int height;
			int logical_width;
			int logical_height;
			bool full_screen;
			std::string window_title;
		};

		class SDLGX_API Graphics
		{
		public:
			Graphics();
			~Graphics();

			void Initialize(const struct GraphicsSetup& setup);
			void Cleanup();
			void Clear();
			void Present();
			SDL_Surface* GetWindowSurface();
			int GetWidth();
			int GetHeight();
			int GetLogicalWidth();
			int GetLogicalHeight();
			int LockMutex();
			void UnlockMutex();
			SDL_Renderer* GetRenderer();

			inline SDL_Window* GetWindow() {
				return m_window;
			}

			void SetResize(bool val) {
				_resize = val;
			}

			float GetScaleRatioW();
			float GetScaleRatioH();

		private:
			SDL_Window* m_window;
			SDL_Renderer* m_renderer;
			struct GraphicsSetup m_setup;
			static SDL_mutex* _mutex;

			void InitSDL(const struct GraphicsSetup& setup);
			void InitIMG();
			void InitTTF();

			// taken from http://www.gamedev.net/page/resources/_/technical/apis-and-tools/stretching-your-game-to-fit-the-screen-without-letterboxing-sdl2-r3547
			SDL_Rect _nativeSize;
			SDL_Rect _newWindowSize;
			float _scaleRatioW;
			float _scaleRatioH;
			SDL_Texture* _backBuffer;
			bool _resize;

			void Resize();
		};

	}
}


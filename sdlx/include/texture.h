#pragma once
#include "sdlgx_common.h"
#include "object_base.h"

namespace sdlgx {
	namespace scene {
		class SDLGX_API Texture : public sdlgx::core::ObjectBase
		{
		public:
			Texture();
			~Texture();

			void CreateFromScreen();
			void Create(int w=0, int h=0);
			bool LoadFromFile(const char* fname);
			bool LoadFromResource(short id);
			bool LoadFromSurface(SDL_Surface* surface);
			void SetAlpha(unsigned char alpha);
			void SetBlendMode(SDL_BlendMode blending);
			
			void Draw(int x, int y);
			void Draw();
			void Draw(const SDL_Rect& src, const SDL_Rect& dest);
			void Draw(SDL_Rect* src, SDL_Rect* dest);
			void DrawEx(SDL_Rect* src, SDL_Rect* dest, const double angle,
				const SDL_Point* center,const SDL_RendererFlip flip);

			void FillRect(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Rect* rect = NULL);
			void DrawRect(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Rect* rect = NULL);

			bool IsValid();
			void SetRenderTarget();
			void UnSetRenderTarget();
			SDL_Texture* GetTexturePtr();
			void Destroy();
			virtual void OnDraw();

		protected:
			//The actual hardware texture
			SDL_Texture* m_texture;
			SDL_Texture* old_target;
		};
	}
}


#pragma once
#include "sdlgx_common.h"
#include "texture.h"

namespace sdlgx {
	namespace scene {

		struct FontDefinitiion {
			char fname[50];
			int id;
			int max_size;
		};

		struct FontCache {
			int id;
			char* fname;
			TTF_Font** cache;
			int size;
		};

		SDLGX_API bool SDLGX_IsFontInitialized();
		SDLGX_API void SDLGX_InitFontDef(struct FontDefinitiion def[], int size);
		SDLGX_API void SDLGX_FontCleanUp();
		SDLGX_API void SDLGX_DrawText(int x, int y,
			const char* text, int fontid, int size, SDL_Color color);

		SDLGX_API void SDLGX_DrawTextCenter(int cx, int cy,
			const char* text, int fontid, int size, SDL_Color color);

		SDLGX_API Texture* SDLGX_GetTextCenter(int cx, int cy,
			const char* text, int fontid, int size, SDL_Color color);


		SDLGX_API Texture* SDLGX_GetText(const char* text, int fontid, int size, SDL_Color color);
	}
}

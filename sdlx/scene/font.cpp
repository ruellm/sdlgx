#include "font.h"
#include "texture.h"
#include "engine.h"

using namespace sdlgx::scene;
using namespace sdlgx::core;

struct FontCache* g_font_cache =  NULL;
int g_font_count = 0;

SDLGX_API 
bool sdlgx::scene::SDLGX_IsFontInitialized()
{
	return g_font_cache != NULL;
}

SDLGX_API 
void sdlgx::scene::SDLGX_InitFontDef(struct FontDefinitiion def[], int size)
{
	int g_font_count = size;
	g_font_cache = new (struct FontCache[size]);	

	for (int i = 0; i < size; i++) {
		struct FontCache* font = &g_font_cache[i];
		int size = strlen(def[i].fname) + 1;
		
		font->fname = new char[size];
		strcpy(font->fname, def[i].fname);
		font->id = def[i].id;

		size = sizeof(TTF_Font*) * def[i].max_size;
		font->cache = new TTF_Font*[size];
		memset(font->cache, 0, size);
		font->size = def[i].max_size;
	}
}

SDLGX_API 
void sdlgx::scene::SDLGX_FontCleanUp()
{
	for (int i = 0; i < g_font_count; i++) {
		struct FontCache* font = &g_font_cache[i];
		for (int f = 0; f < font->size; f++) {
			TTF_CloseFont(font->cache[f]);
		}

		SAFE_DELETE_ARRAY(font->cache);
		SAFE_DELETE_ARRAY(font->fname);
	}

	SAFE_DELETE_ARRAY(g_font_cache);
}

SDLGX_API 
void sdlgx::scene::SDLGX_DrawText(int x, int y,
	const char* text, int fontid, int size, SDL_Color color)
{
	
	Texture* texture = SDLGX_GetText(text, fontid, size, color);
	//Render the text
	texture->Draw(x, y);

	SAFE_DELETE(texture);
}

SDLGX_API 
void sdlgx::scene::SDLGX_DrawTextCenter(int cx, int cy,
	const char* text, int fontid, int size, SDL_Color color)
{
	Texture* t = SDLGX_GetText(text, fontid, size, color);
	int x = cx - (t->GetWidth() / 2);
	int y = cy - (t->GetHeight() / 2);
	t->Draw(x, y);
	SAFE_DELETE(t);
}

SDLGX_API
Texture*
sdlgx::scene::SDLGX_GetTextCenter(int cx, int cy,
	const char* text, int fontid, int size, SDL_Color color)
{
	Texture* t = SDLGX_GetText(text, fontid, size, color);
	int x = cx - (t->GetWidth() / 2);
	int y = cy - (t->GetHeight() / 2);
	t->SetCoordinates(x, y);

	return t;
}


SDLGX_API Texture* 
sdlgx::scene::SDLGX_GetText(const char* text, 
	int fontid, int size, SDL_Color color)
{

	struct FontCache* font = &g_font_cache[fontid];
	if (font->size < size) {
		font->cache = (TTF_Font**)realloc(font->cache, size);
		font->cache[size - 1] = NULL;
		font->size = size;
	}

	TTF_Font* f = font->cache[size - 1];
	if (f == NULL) {
		f = TTF_OpenFont(font->fname, size);
		if (f == NULL) {
			printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
			return 0;
		}

		font->cache[size - 1] = f;
	}

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(f, text, color);
	Texture* texture = new Texture();

	//create texture from TTF_Font surface
	texture->LoadFromSurface(textSurface);

	//Get rid of old surface
	SDL_FreeSurface(textSurface);

	return texture;
}
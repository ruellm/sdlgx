#include "texture.h"
#include "engine.h"
#include "resource.h"

using namespace sdlgx::scene;
using namespace sdlgx::core;
using namespace sdlgx::resource;


Texture::Texture() :
	m_texture(NULL), old_target(NULL)
{
}

Texture::~Texture()
{
	Destroy();
//	printf("\n TEXTURE DEALLOCATE %d", --g_texture_allocated);
}

bool Texture::LoadFromFile(const char* fname)
{
	SDL_Surface* loadedSurface = IMG_Load(fname);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", fname, 
			IMG_GetError());
		
		return false;
	}
	
	Destroy();

	LoadFromSurface(loadedSurface);
	
	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return m_texture != NULL;
}

void Texture::Destroy()
{
	// cleanup the old one
	try {
		if (m_texture) {
			SDL_DestroyTexture(m_texture);
			m_texture = NULL;
		}
	}
	catch (...) {
		printf("\n Texture::Destroy() SOmething wrong");
	}
}

bool Texture::LoadFromResource(short id)
{	
	SDL_Surface* surface = NULL;
	ImageResource* resource = ResourceManager::GetInstance()->GetResource(id);
	if (resource->defer) {
		surface = IMG_Load(resource->path);
	}
	else {
		surface = resource->img;
	}
	if (surface == NULL) return false;

	LoadFromSurface(surface);
	
	if (resource->defer) {
		SDL_FreeSurface(surface);
	}

	return true;
}

bool Texture::LoadFromSurface(SDL_Surface* surface)
{
	if (surface == NULL) return false;

	try {
		// cleanup the old one
		Destroy();

		// Create texture from surface pixels
		m_texture = SDL_CreateTextureFromSurface(CURRENT_RENDERER,
		
		surface);
		if (m_texture == NULL) {
			fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
		}

	}catch (...) {
		printf("\n SOmething's wrong %s", SDL_GetError());
	}

	_width = surface->w;
	_height = surface->h;

	return m_texture != NULL;
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(m_texture, blending);
}

void Texture::SetAlpha(unsigned char alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(m_texture, alpha);
}

void Texture::Draw()
{
	Draw(_x, _y);
}

void Texture::Draw(int x, int y)
{
	SDL_Rect dest = { x, y, _width, _height };
	SDL_RenderCopy(CURRENT_RENDERER, m_texture, NULL, &dest);
}

void Texture::Draw(const SDL_Rect& src, const SDL_Rect& dest)
{
	SDL_RenderCopy(CURRENT_RENDERER, m_texture, &src, &dest);
}

void Texture::Draw(SDL_Rect* src, SDL_Rect* dest)
{
	SDL_RenderCopy(CURRENT_RENDERER, m_texture, src, dest);
}

void Texture::DrawEx(SDL_Rect* src, SDL_Rect* dest, const double angle,
	const SDL_Point* center, const SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(CURRENT_RENDERER, m_texture, src, dest, angle, center, flip);
}

void Texture::OnDraw()
{
	Draw();
}

void  Texture::CreateFromScreen()
{
	SDL_Surface* window = CURRENT_GRAPHICS->GetWindowSurface();
	SDL_DestroyTexture(m_texture);

	m_texture = SDL_CreateTexture(CURRENT_RENDERER, window->format->format, 
		SDL_TEXTUREACCESS_TARGET, window->w, window->h);

	if (m_texture == NULL) {
		printf("CreateFromScreen: Unable to Create texture: %s \n", 
			SDL_GetError());
	}

	_width = window->w;
	_height = window->h;

}

void Texture::Create(int w, int h)
{
	SDL_Window* window = CURRENT_GRAPHICS->GetWindow();

	_width = LOGICAL_WIDTH;
	_height = LOGICAL_HEIGHT;

	if (w != 0 && h != 0) {
		_width = w;
		_height = h;
	}

	SDL_DestroyTexture(m_texture);
	m_texture = SDL_CreateTexture(CURRENT_RENDERER,
		SDL_GetWindowPixelFormat(window),
		SDL_TEXTUREACCESS_TARGET,
		_width,
		_height);

	if (m_texture == NULL) {
		printf("CreateFromScreen: Unable to Create texture: %s \n",
			SDL_GetError());
	}

}


SDL_Texture* Texture::GetTexturePtr()
{
	return m_texture;
}

bool Texture::IsValid()
{
	return m_texture != NULL;
}

void Texture::DrawRect(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Rect* rect)
{
	SetRenderTarget();
	SDL_RenderClear(CURRENT_RENDERER);
	SDL_SetRenderDrawColor(CURRENT_RENDERER, r, g, b, a);
	SDL_RenderDrawRect(CURRENT_RENDERER, rect);

	UnSetRenderTarget();
}

void Texture::FillRect(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Rect* rect)
{
	SetRenderTarget();
	SDL_RenderClear(CURRENT_RENDERER);
	SDL_SetRenderDrawColor(CURRENT_RENDERER, r, g, b, a);
	SDL_RenderFillRect(CURRENT_RENDERER, rect);

	UnSetRenderTarget();
}

void Texture::SetRenderTarget()
{
	old_target = SDL_GetRenderTarget(CURRENT_RENDERER);
	SDL_SetRenderTarget(CURRENT_RENDERER, m_texture);
	SDL_SetRenderDrawColor(CURRENT_RENDERER, 0, 0, 0, 0);
	SDL_RenderClear(CURRENT_RENDERER);
}

void Texture::UnSetRenderTarget()
{
	SDL_SetRenderTarget(CURRENT_RENDERER, old_target);
}

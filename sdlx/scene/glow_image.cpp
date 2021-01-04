#include "glow_image.h"

using namespace sdlgx::scene;

GlowImage::GlowImage() : _dir(0), 
_alpha(1.0f), _speed(0.0f),
GLOW_ALPHA_ACCEL(3)
{
}


GlowImage::~GlowImage()
{
}


void GlowImage::Load(int resid)
{
	if (_texture.LoadFromResource(resid))
	{
		_width = _texture.GetWidth();
		_height = _texture.GetHeight();
		_texture.SetBlendMode(SDL_BLENDMODE_BLEND);
	}

	_alpha = 0.0f;
	_dir = 0;
}

void GlowImage::OnUpdate(float elapsed)
{	
	if (_dir == 0) {
		_alpha += (GLOW_ALPHA_ACCEL * elapsed);
		if (_alpha >= 1.0f)
		{
			_alpha = 1.0f;
			_dir = 1;
		}
	}
	else if (_dir == 1) {
		_alpha -= (GLOW_ALPHA_ACCEL * elapsed);
	
		if (_alpha <= 0.5f) {
			_alpha = 0.5f;
			_dir = 0;
		}
	}
	
}

void GlowImage::OnDraw(int x, int y)
{	
	_texture.SetAlpha( (unsigned char)(_alpha * 255) );
	_texture.Draw(x, y);
}
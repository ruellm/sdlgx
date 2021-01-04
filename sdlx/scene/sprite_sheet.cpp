#include "sprite_sheet.h"
#include "engine.h"

using namespace sdlgx::scene;
using namespace sdlgx::core;

SpriteSheet::SpriteSheet() 
	: Texture()
{
	_frameCount = 1.0;
	_currentFrame = 0;
	_frameWidth = 0;
	_bLoop = true;
	_called = false;
	_handler = NULL;
}


SpriteSheet::~SpriteSheet()
{
	SDL_DestroyTexture(m_texture);
	m_texture = NULL;
}


void SpriteSheet::Set(int frame_count, int fps, bool loop)
{
	SetLoop(loop);
	SetFPS(fps);
	_frameCount = frame_count;

	_frameWidth = _width / frame_count;
}

void SpriteSheet::SetLoop(bool flag)
{
	_bLoop = flag;
}

void SpriteSheet::SetFPS(int fps)
{
	_animator.Set(fps);
}

void SpriteSheet::Reset()
{
	if (_currentFrame == _frameCount - 1) {
		_currentFrame = 0;
		_called = false;
	}
}

int SpriteSheet::GetFrameWidth()
{
	return _frameWidth;
}

void SpriteSheet::OnUpdate(float elapsed)
{
	if (_animator.Update(elapsed)) {
		++_currentFrame;
		if (_bLoop) {
			_currentFrame %= _frameCount;
		}
		else if (_currentFrame >= _frameCount) {
			_currentFrame = _frameCount - 1;
			if (_handler) {
				if (_bLoop == false && _called == false) {
					_called = true;
					_handler->OnAnimationComplete(this);
				}
			}
		}
	}
}

void SpriteSheet::OnDraw(int x, int y)
{
	int sourceX = _frameWidth * _currentFrame;

	SDL_Rect src = { sourceX, 0, _frameWidth,  _height };
	SDL_Rect dest = { x, y, _frameWidth,  _height };
	
	Draw(src, dest);
}

void SpriteSheet::OnDraw()
{
	OnDraw(_x, _y);
}

void SpriteSheet::OnDrawFlip(int x, int y, SDL_RendererFlip flip)
{
	int sourceX = _frameWidth * _currentFrame;

	SDL_Rect src = { sourceX, 0, _frameWidth,  _height };
	SDL_Rect dest = { x, y, _frameWidth,  _height };

	DrawEx(&src, &dest, 0.0, NULL, flip);
}

void SpriteSheet::SetCallbackHandler(ISpriteCallback* callback)
{
	_handler = callback;
}

void SpriteSheet::SetAlpha(unsigned char alpha)
{
	this->SetBlendMode(SDL_BLENDMODE_BLEND);
	Texture::SetAlpha(alpha);
}
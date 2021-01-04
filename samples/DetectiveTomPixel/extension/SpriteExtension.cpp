#include "SpriteExtension.h"

using namespace sdlgx::scene;

SpriteExtenshion::SpriteExtenshion() 
	: _current_idx(0)
{}

SpriteExtenshion::~SpriteExtenshion()
{
	for (int i = 0; i < _list.size();i++) {
		SpriteSheet* s = _list.at(i);
		SAFE_DELETE(s);
	}
}

void SpriteExtenshion::OnAnimationComplete(SpriteSheet* sprite)
{
	_current_idx++;
	if (_bLoop) {
		_current_idx %= _list.size();
		Reset();
	}
	else {
		if (_current_idx >= _list.size()) {
			_current_idx = _list.size() - 1;
		}
	}

}

void SpriteExtenshion::OnUpdate(float elapsed)
{
	_list.at(_current_idx)->OnUpdate(elapsed);
}

void SpriteExtenshion::OnDraw(int x, int y)
{
	_list.at(_current_idx)->OnDraw(x,y);
}

void SpriteExtenshion::OnDrawFlip(int x, int y, SDL_RendererFlip flip)
{
	_list.at(_current_idx)->OnDrawFlip(x, y, flip);
}

void SpriteExtenshion::AddSprite(SpriteSheet* s)
{
	s->SetCallbackHandler(this);
	_list.push_back(s);
}

void SpriteExtenshion::Reset()
{
	for (int i = 0; i < _list.size();i++) {
		_list.at(i)->Reset();
	}
	_current_idx = 0;
}

void SpriteExtenshion::SetAlpha(unsigned char alpha)
{
	_list.at(_current_idx)->SetAlpha(alpha);
}
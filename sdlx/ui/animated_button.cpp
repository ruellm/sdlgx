#include "animated_button.h"

using namespace sdlgx::gui;

AnimatedButton::AnimatedButton() :
	_idle (NULL), _hover(NULL), _current(NULL)
{
}


AnimatedButton::~AnimatedButton()
{
}

void AnimatedButton::Load(sdlgx::scene::SpriteSheet* idle,
	sdlgx::scene::SpriteSheet* hover) 
{
	_idle = idle;
	_hover = hover;

	_current = idle;
}

void AnimatedButton::Select()
{
	if (!IsEnable()) return;
	_current = _hover;
}

void AnimatedButton::UnSelect()
{
	if (!IsEnable()) return;
	_current = _idle;
}

void AnimatedButton::OnUpdate(float elapsed)
{
	if (_current == NULL) {
		if (_idle != NULL) {
			_current = _idle;
		}
		else {
			return;
		}
	}
	_current->OnUpdate(elapsed);
}

void AnimatedButton::OnDraw()
{
	if (_current == NULL) return;

	_current->OnDraw(_x, _y);
}
#include "button.h"

using namespace sdlgx::gui;
using namespace sdlgx::scene;

Button::Button() 
	: _currentImg(NULL), _highLightImg(NULL), 
	_idleImg(NULL), _clickdImg(NULL), _disableImg(NULL),
	_handler(NULL), _select(false), _clicked(false),
	_lastTime(0), _holdThreshold(0.5f)
{
	//...
}


Button::~Button()
{
	if (_idleImg != _clickdImg)
		SAFE_DELETE(_clickdImg);

	if (_disableImg != _idleImg)
		SAFE_DELETE(_disableImg);
	
	SAFE_DELETE(_highLightImg);
	SAFE_DELETE(_idleImg);
}

void Button::Load(short idle, short highlight, short clicked, short disable)
{
	_idleImg = new Texture();
	_idleImg->LoadFromResource(idle);
	_currentImg = _idleImg;

	_highLightImg = new Texture();
	_highLightImg->LoadFromResource(highlight);

	if (clicked != RESOURCE_ID_NONE)
	{
		_clickdImg = new Texture();
		_clickdImg->LoadFromResource(clicked);
	}
	else {
		_clickdImg = _idleImg;
	}

	if (disable != RESOURCE_ID_NONE)
	{
		_disableImg = new Texture();
		_disableImg->LoadFromResource(disable);
	}
	else {
		_disableImg = _idleImg;
	}

	_width = _idleImg->GetWidth();
	_height = _idleImg->GetHeight();
}

void Button::OnMouseEnterMove(int x, int y)
{
	if (!IsEnable()) return;
	if (_highLightImg) {
		_currentImg = _highLightImg;
	}

	_select = true;
}

void Button::OnMouseLeave()
{
	if (!IsEnable()) return;
	if (_idleImg) {
		_currentImg = _idleImg;
	}

	_select = false;
}

void Button::SetEnable(bool val)
{
	if (!val && _disableImg) {
		_currentImg = _disableImg;
	}
	else {
		_currentImg = _idleImg;
	}

	UIBase::SetEnable(val);
}

bool Button::OnMouseDown(int x, int y)
{
	if (!IsEnable()) return false;

	if (_clickdImg) {
		_currentImg = _clickdImg;
	}

	_clicked = true;
	
	return true;
}

bool Button::OnMouseUp(int x, int y)
{
	if (_clicked) {
		if (_handler) {
			_handler->OnButtonClick(this);
			_clicked = false;
		}
	}
	return true;
}

bool Button::OnMouseUpOut(int x, int y)
{
	_clicked = false;
	return true;
}

void Button::SetHandler(IButtonEventHandler* handler)
{
	_handler = handler;
}

void Button::OnDraw()
{
	if (_currentImg) {
		_currentImg->Draw(_x, _y);
	}
}

void Button::SetHoldThreshold(float value)
{
	_holdThreshold = value;
}

void Button::OnUpdate(float elapsed)
{
	if (_clicked) {
		Uint32 curentTime = SDL_GetTicks();
		float elapsed = (curentTime - _lastTime) / 1000.0f;

		if (elapsed >= _holdThreshold) {
			_lastTime = curentTime;
			if (_handler) {
				_handler->OnButtonHold(this);
			}
		}
	}
}
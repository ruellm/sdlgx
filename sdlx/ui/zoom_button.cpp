#include "zoom_button.h"

using namespace sdlgx::gui;
using namespace sdlgx::scene;

ZoomButton::ZoomButton()
{
	_selected = false;
	_scaled_up = 1.2f;

	_zooming_flag = -1; // 0: increase, 1: decrease,-1 normal
	_state = 0; //0: normal, 1: zoomed, 2: zooming

	_alpha = 0.5f;
	_icon = NULL;
}


ZoomButton::~ZoomButton()
{
	SAFE_DELETE(_icon);
}

void ZoomButton::SetAcceleration(float value)
{
	_size_accel = value;
}

void ZoomButton::SetScaleUp(float value)
{
	_scaled_up = value;
}

void ZoomButton::Load(short resid)
{
	_icon = new Texture();
	_icon->LoadFromResource(resid);

	_original_width = _icon->GetWidth();
	_original_height = _icon->GetHeight();

	_width = _original_width;
	_height = _original_height;

	_size_accel = 300;
}

void ZoomButton::OnUpdate(float elapsed) 
{
	int count = 0;

	//
	//NOTE: Zoom functionality must be placed in a common class or handler
	// SAME as the other animation
	//
	if (_zooming_flag == 0) {
		if (_width < _target_width) {
			_width += (_size_accel * elapsed);
		}
		else {
			_width = _target_width;
			count++;
		}

		if (_height < _target_height) {
			_height += (_size_accel * elapsed);
		}
		else {
			_height = _target_height;
			count++;
		}
	}
	else if (_zooming_flag == 1) {
		float thewidth = _width - (_size_accel * elapsed);
		float theheight = _height - (_size_accel * elapsed);
		if (thewidth >= _target_width) {
			_width = thewidth;
		}
		else {
			_width = _target_width;
			count++;
		}

		if (theheight > _target_height) {
			_height = theheight;
		}
		else {
			_height = _target_height;
			count++;
		}
	}

	if (count >= 2 && _zooming_flag != -1) {

		if (_state == 2 && _zooming_flag == 0)
			_state = 1; //zoomed
		else if (_state == 2 && _zooming_flag == 1) {
			_state = 0;
		}

		_zooming_flag = -1;
	}

	if (/*_zooming_flag != -1*/1) {
		// compute center
		float centerX = _x + (_original_width / 2);
		float centerY = _y + (_original_height / 2);

		_new_x = centerX - (_width / 2);
		_new_y = centerY - (_height / 2);
	}
	else {
		_new_x = _x;
		_new_y = _y;
	}

}

void ZoomButton::OnDraw()
{
	SDL_Rect src = {0, 0, _original_width, _original_height};
	SDL_Rect dest = {_new_x, _new_y, _width, _height};

	_icon->Draw(src, dest);
}

void ZoomButton::OnMouseEnterMove(int x, int y)
{
	if (_selected == true) return;
	_selected = true;

	if (_zooming_flag != 0 && _state == 0) {
		_zooming_flag = 0;

		_target_width = _original_width * _scaled_up;
		_target_height = _original_height * _scaled_up;

		_state = 2;
	}
}

void ZoomButton::OnMouseLeave()
{
	_selected = false;

	if (_zooming_flag != 1 && _state == 1) {
		_zooming_flag = 1;

		_target_width = _original_width;
		_target_height = _original_height;
		_state = 2;
	}
}

bool ZoomButton::OnMouseUp(int x, int y)
{
	if (_clicked) {
		if (_handler) {
			_handler->OnButtonClick(this);
			_clicked = false;
			_selected = false;
		}
	}
	return true;
}

int ZoomButton::GetNewX()
{
	return _new_x;
}

int ZoomButton::GetNewY()
{
	return _new_y;
}

int ZoomButton::GetState()
{
	return _state;
}

float ZoomButton::GetScaleUp()
{
	return _scaled_up;
}
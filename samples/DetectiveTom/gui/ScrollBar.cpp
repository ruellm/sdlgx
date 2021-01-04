#include "ScrollBar.h"



ScrollBar::ScrollBar() :
	_thumb_x(0),_thumb_y(0), _is_drag (false),
	_offset(0), _type(SCROLLBAR_VERTICAL),
	_button1(NULL), _button2(NULL), _gap(20),
	_step(5)
{
}


ScrollBar::~ScrollBar()
{
	SAFE_DELETE(_button1);
	SAFE_DELETE(_button2);
}

void ScrollBar::SetType(ScrollBarType type)
{
	_type = type;
}

void ScrollBar::SetGap(int gap)
{
	_gap;
}

void ScrollBar::SetStep(int step)
{
	_step = step;
}

void ScrollBar::SetBarImage(int resID)
{
	_bar.LoadFromResource(resID);
}

void ScrollBar::SetThumbImage(int resID)
{
	_thumb.LoadFromResource(resID);	
}

bool ScrollBar::OnMouseMove(int x, int y)
{
	if (_is_drag) {
		if (_type == SCROLLBAR_VERTICAL) {
			int diff = y - _old_y;
			_old_y = y;
			_offset += diff;
		}
		else {
			int diff = x - _old_x;
			_old_x = x;
			_offset += diff;
		}
		return true;
	}
	else {
		if (_button1 && _button2) {
			if (x >= _button1->_x && x <= _button1->_x + _button1->_width &&
				(y >= _button1->_y && y <= _button1->_y + _button1->_height)) {
				_button1->OnMouseEnterMove(x, y);
			}
			else {
				_button1->OnMouseLeave();
			}

			if (x >= _button2->_x && x <= _button2->_x + _button2->_width &&
				(y >= _button2->_y && y <= _button2->_y + _button2->_height)) {
				_button2->OnMouseEnterMove(x, y);
			}
			else {
				_button2->OnMouseLeave();
			}
		}
	}
	
	return false;
}

bool ScrollBar::OnMouseDown(int x, int y)
{
	//check if mouse down is in thumb
	if (x >= _thumb_x && x <= _thumb_x + _thumb.GetWidth() &&
		(y >= _thumb_y && y <= _thumb_y + _thumb.GetHeight())) {
		_is_drag = true;

		_old_y = y;
		_old_x = x;
	}
	else {
		if (_button1 && _button2) {
			if (x >= _button1->_x && x <= _button1->_x + _button1->_width &&
				(y >= _button1->_y && y <= _button1->_y + _button1->_height)) {
				return _button1->OnMouseDown(x, y);
			}
			else {
				_button1->OnMouseDownOut(x,y);
			}

			if (x >= _button2->_x && x <= _button2->_x + _button2->_width &&
				(y >= _button2->_y && y <= _button2->_y + _button2->_height)) {
				return _button2->OnMouseDown(x, y);
			}
			else {
				_button2->OnMouseDownOut(x,y);
			}
		}
	}
	
	return false;
}

bool ScrollBar::OnMouseUp(int x, int y)
{
	if (_is_drag) {
		_is_drag = false;
		_old_y = y;
		_old_x = x;
	}
	else {
		if (_button1 && _button2) {
			if (x >= _button1->_x && x <= _button1->_x + _button1->_width &&
				(y >= _button1->_y && y <= _button1->_y + _button1->_height)) {
				return _button1->OnMouseUp(x, y);
			}
			else {
				_button1->OnMouseUpOut(x, y);
			}

			if (x >= _button2->_x && x <= _button2->_x + _button2->_width &&
				(y >= _button2->_y && y <= _button2->_y + _button2->_height)) {
				return _button2->OnMouseUp(x, y);
			}
			else {
				_button2->OnMouseUpOut(x, y);
			}
		}
	}

	return false;
}

bool ScrollBar::OnMouseUpOut(int x, int y)
{
	_is_drag = false;
	_old_y = y;
	_old_x = x;
	return true;
}

void ScrollBar::OnUpdate(float elapsed)
{
	Refresh();
	if (_button1 && _button2)
	{
		_button1->OnUpdate(elapsed);
		_button2->OnUpdate(elapsed);
	}
}

void ScrollBar::Refresh()
{
	_barx = _x;
	_bary = _y;
	if (_type == SCROLLBAR_VERTICAL) {

		_width = _thumb.GetWidth();
		_height = _bar.GetHeight();

		int cx = _x + (_bar.GetWidth() / 2);
		_basey = _y;
		if (_button1 && _button2)
		{
			int b1x = cx - (_button1->GetWidth() / 2);
			int b1y = _y;
			_basey = b1y + _button1->GetHeight() + _gap;
			_button1->SetCoordinates(b1x, b1y);
			_bary = _button1->_y + _button1->GetHeight() + _gap;

			int b2x = b1x;
			int b2y = _y + _bar.GetHeight() + _button1->GetHeight() + _gap + _gap;
			_button2->SetCoordinates(b2x, b2y);

			if (_button1->GetWidth() > _width)
				_width = _button1->GetWidth();

			_height += _button1->GetHeight() + _gap;
			_height += _button2->GetHeight() + _gap;
		}

		_thumb_x = cx - (_thumb.GetWidth() / 2);
		_thumb_y = _basey + _offset;

		if (_thumb_y <= _basey) {
			_thumb_y = _basey;
			_offset = 0;
		}

		if (_thumb_y + _thumb.GetHeight() >= _basey + _bar.GetHeight()) {
			_thumb_y = (_basey + _bar.GetHeight()) - _thumb.GetHeight();
			_offset = _thumb_y - _basey;
		}

	}
	else {
		int cy = _y + (_bar.GetHeight() / 2);
		_basex = _x;

		_width = _bar.GetWidth();
		_height = _thumb.GetHeight();
		
		if (_bar.GetHeight() > _height)
			_height = _bar.GetHeight();

		if (_button1 && _button2)
		{
			int b1x = _x;
			int b1y = cy - (_button1->GetHeight() / 2);
			_basex = _x + _button1->GetWidth() + _gap;
			_button1->SetCoordinates(b1x, b1y);
			_barx = _button1->_x + _button1->GetWidth() + _gap;

			int b2x = _x + _button1->GetWidth() + _bar.GetWidth() + _gap + _gap;
			int b2y = b1y;
			_button2->SetCoordinates(b2x, b2y);

			_width += _button1->GetWidth() + _gap;
			_width += _button2->GetWidth() + _gap;
		}

		_thumb_y = cy - (_thumb.GetHeight() / 2);
		_thumb_x = _basex + _offset;

		if (_thumb_x <= _basex) {
			_thumb_x = _basex;
			_offset = 0;
		}

		if (_thumb_x + _thumb.GetWidth() >= _basex + _bar.GetWidth()) {
			_thumb_x = (_basex + _bar.GetWidth()) - _thumb.GetWidth();
			_offset = _thumb_x - _basex;
		}
	}

}

void ScrollBar::OnDraw()
{
	_bar.Draw(_barx, _bary);	
	_thumb.Draw( _thumb_x, _thumb_y);

	if (_button1) {
		_button1->OnDraw();
	}

	if (_button2) {
		_button2->OnDraw();
	}
}

void ScrollBar::SetButton1Param(int idle, int glow, float accel)
{
	_button1 = new GlowButton();
	_button1->Load(idle, idle);
	_button1->SetGlowImage(glow, accel);
	_button1->SetHandler(this);
	_button1->SetID(0);
}

void ScrollBar::SetButton2Param(int idle, int glow, float accel)
{
	_button2 = new GlowButton();
	_button2->Load(idle, idle);
	_button2->SetGlowImage(glow, accel);
	_button2->SetHandler(this);
	_button2->SetID(1);

}

void ScrollBar::OnButtonClick(sdlgx::gui::Button* b)
{
	switch (b->GetID())
	{
	case 0:
		_offset -= _step;
		break;
		
	case 1:
		_offset += _step;
		break;
	}
}

float ScrollBar::GetPercentage()
{
	int base = 0;
	int end = 0;
	int current = 0;

	if (_type == SCROLLBAR_VERTICAL) {
		base = _basey;
		end = _basey + _bar.GetHeight();
	}
	else {
		base = _basex;
		end = _basex + _bar.GetWidth();
	}

	return (float)_offset 
		/ ((float)(end-base));
}
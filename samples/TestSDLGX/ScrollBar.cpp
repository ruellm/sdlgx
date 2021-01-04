#include "ScrollBar.h"



ScrollBar::ScrollBar() :
	_thumb_y(0), _is_drag (false),
	_offset(0)
{
}


ScrollBar::~ScrollBar()
{
}

void ScrollBar::SetBarImage(int resID)
{
	_bar.LoadFromResource(resID);

	_height = _bar.GetHeight();
}

void ScrollBar::SetThumbImage(int resID)
{
	_thumb.LoadFromResource(resID);
	_width = _thumb.GetWidth();
}

bool ScrollBar::OnMouseMove(int x, int y)
{
	if (_is_drag) {
		int diff = y - _old_y;
		_old_y = y;
		_offset += diff;
		
		return true;
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
	}
	return false;
}

bool ScrollBar::OnMouseUp(int x, int y)
{
	_is_drag = false;
	_old_y = y;
	return false;
}

void ScrollBar::OnUpdate(float elapsed)
{
	int cx = _x + (_bar.GetWidth() / 2);
	_thumb_x = cx - (_thumb.GetWidth() / 2);
	_thumb_y = _y + _offset;

	if (_thumb_y <= _y) {
		_thumb_y = _y;
		_offset = 0;
	}
	
	if (_thumb_y + _thumb.GetHeight() >= _y + _bar.GetHeight()) {
		_thumb_y = (_y + _bar.GetHeight()) - _thumb.GetHeight();
		_offset = _thumb_y - _y;
	}
}

void ScrollBar::OnDraw()
{
	_bar.Draw(_x, _y);	
	_thumb.Draw( _thumb_x, _thumb_y);
}
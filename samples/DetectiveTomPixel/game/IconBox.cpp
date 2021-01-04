#include "IconBox.h"
#include "definitions.h"

IconBox::IconBox() :
	_state(ICONBOX_STATE_NONE),
	_zoom_flag(0), _handler(NULL)
{}

IconBox::~IconBox()
{}

void IconBox::Load(EvidenceType type)
{
	_texture.LoadFromResource(GetEvidenceResource(type));
	_zoom_flag = 0; // 0: increase, 1: decrease
	_type = type;
}

void IconBox::OnUpdate(float elapsed)
{
	if (_state == ICONBOX_STATE_ZOOMING) {
		OnUpdateZoom(elapsed);
	}
	else if (_state == ICONBOX_STATE_MOVING) {
		OnUpdateMoving(elapsed);
	}
}

void IconBox::OnDraw()
{
	SDL_Rect dest = { _x, _y, _width, _height };
	_texture.Draw(NULL,&dest);

}

void IconBox::ZoomIn(int cx, int cy)
{
	_state = ICONBOX_STATE_ZOOMING;
	_targetWidth = ICONBOX_WIDTH;
	_targetHeight = ICONBOX_HEIGHT;

	_width = ICONBOX_WIDTH * 0.10f;
	_height = ICONBOX_HEIGHT * 0.10f;

	_centerZoomX = cx;
	_centerZoomY = cy;

	_zoom_flag = 0;
}

void IconBox::MoveTo(int x, int y)
{
	_state = ICONBOX_STATE_MOVING;

	if (x - _x > 0) {
		_dirX = 0;
	}
	else {
		_dirX = 1;
	}

	if (y - _y > 0) {
		_dirY = 0;
	}
	else {
		_dirY = 1;
	}

	_targetX = x;
	_targetY = y;
}

void IconBox::OnUpdateMoving(float elapsed)
{
	int MOVE_ACCEL = 1200;
	int count = 0;

	if (_dirX == 0) {
		if (_x < _targetX) {
			_x += (MOVE_ACCEL * elapsed);
		}
		else {
			_x = _targetX;
			count++;
		}
	}
	else if (_dirX == 1) {
		if (_x > _targetX) {
			_x -= (MOVE_ACCEL * elapsed);
		}
		else {
			_x = _targetX;
			count++;
		}
	}

	if (_dirY == 0) {
		if (_y < _targetY) {
			_y += (MOVE_ACCEL * elapsed);
		}
		else {
			_y = _targetY;
			count++;
		}
	}
	else if (_dirY == 1) {
		if (_y > _targetY) {
			_y -= (MOVE_ACCEL * elapsed);
		}
		else {
			_y = _targetY;
			count++;
		}
	}

	if (count >= 2) {
		_state = ICONBOX_STATE_NONE;
		_handler->OnCustomEvent((void*)this, ICONBOX_EVT_MOVE_DONE);
	}
}

void IconBox::OnUpdateZoom(float elapsed)
{
	int SIZE_ACCEL = 1200;
	int count = 0;

	if (_zoom_flag == 0) {
		if (_width < _targetWidth) {
			_width += (SIZE_ACCEL * elapsed);
		}
		else {
			_width = _targetWidth;
			count++;
		}

		if (_height < _targetHeight) {
			_height += (SIZE_ACCEL * elapsed);
		}
		else {
			_height = _targetHeight;
			count++;
		}
	}
	else {
		int thewidth = _width - (SIZE_ACCEL * elapsed);
		int theheight = _height - (SIZE_ACCEL * elapsed);
		if (thewidth >= _targetWidth) {
			_width = thewidth;
		}
		else {
			_width = _targetWidth;
			count++;
		}

		if (theheight > _targetHeight) {
			_height = theheight;
		}
		else {
			_height = _targetHeight;
			count++;
		}
	}
	
	_x = _centerZoomX - (_width / 2);
	_y = _centerZoomY - (_height / 2);

	if (count >= 2) {
		_state = ICONBOX_STATE_NONE;
		_handler->OnCustomEvent((void*)this, ICONBOX_EVT_ZOOM_DONE);
	}
}

void IconBox::SetEventHandler(ICustomEvent* h)
{
	_handler = h;
}

EvidenceType IconBox::GetType()
{
	return _type;
}
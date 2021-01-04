#include "ComboBox.h"
#include "engine.h"

using namespace sdlgx::gui;
using namespace sdlgx::core;

ComboBox::ComboBox()
{
}


ComboBox::~ComboBox()
{
	for (int i=0; i < _items.size(); i++)
	{
		TextButton* item = _items.at(i);
		SAFE_DELETE(item);
	}
}

void ComboBox::Load(char options[][20], int count)
{
	///////////////////////////////////////
	int text_size = 10;		// CHANGE THIS
	///////////////////////////////////////
	SDL_Color idle = { 255,255,255 };
	SDL_Color hover = { 255,0,0 };

	_items.clear();
	
	for (int r = 0; r < count; r++) {
		TextButton* tb = new TextButton();
		
		//NOTE VALUES ARE HARDCODED, cannot be flexible
		//MODIFY THIS IN THE FUTURE
		tb->Load(options[r], 60, 0, idle, hover, idle);
		_items.push_back(tb);

		tb->SetID(1 + r);
		tb->SetHandler(this);
	}
}

void ComboBox::SetToggleButton(int residle, int clicked, int glow)
{
	_toggle.Load(residle, residle, clicked);
	_toggle.SetGlowImage(glow, 1);
	_toggle.SetID(0);
	_toggle.SetHandler(this);
}

void ComboBox::SetTextBoxImg(int resid)
{
	_textbox.LoadFromResource(resid);
}

bool ComboBox::OnMouseDown(int x, int y)
{
	int toggle_x = _x + _textbox.GetWidth();
	int toggle_y = _y;

	//check if mouse down in toggle button
	if (x >= toggle_x && x <= toggle_x + _toggle._width &&
		(y >= toggle_y && y <= toggle_y + _toggle._height)) {
		return _toggle.OnMouseDown(x, y);
	}

	//check items
	for (int i = 0; i < _items.size(); i++)
	{
		TextButton* obj = _items.at(i);
		if (x >= obj->_x && x <= obj->_x + obj->_width &&
			(y >= obj->_y && y <= obj->_y + obj->_height)) {
			return obj->OnMouseDown(x, y);
		}
	}

	if(_toggle.IsToggled()){
		if (y >= _y + _textbox.GetHeight() && y <= _height) {
			if (x >= _x + _textbox.GetWidth())
			{
				_toggle.SetToggled(false);
				return true;
			}
		}
	}

	return false;
}

bool ComboBox::OnMouseUp(int x, int y)
{
	//check items
	for (int i = 0; i < _items.size(); i++)
	{
		TextButton* obj = _items.at(i);
		if (x >= obj->_x && x <= obj->_x + obj->_width &&
			(y >= obj->_y && y <= obj->_y + obj->_height)) {
			return obj->OnMouseUp(x, y);
		}
	}
}


bool ComboBox::OnMouseDownOut(int x, int y)
{

	_toggle.SetToggled(false);
	return true;
}

bool ComboBox::OnMouseMove(int x, int y)
{
	int toggle_x = _x + _textbox.GetWidth();
	int toggle_y = _y;

	//check if mouse down in toggle button
	if (x >= toggle_x && x <= toggle_x + _toggle._width &&
		(y >= toggle_y && y <= toggle_y + _toggle._height)) {
		_toggle.OnMouseEnterMove(x,y);
		return true;
	}
	else {
		_toggle.OnMouseLeave();

		for (int i=0; i < _items.size(); i++)
		{
			TextButton* obj = _items.at(i);
			if (x >= obj->_x && x <= obj->_x + obj->_width &&
				(y >= obj->_y && y <= obj->_y + obj->_height)) {
				obj->OnMouseEnterMove(x, y);
			}
			else {
				obj->OnMouseLeave();
			}
		}
	}

	return false;
}

void ComboBox::OnButtonClick(sdlgx::gui::Button *b)
{
	printf("Button clicked %d", b->GetID());
	int id = b->GetID();
	if (id >= 1)
		_toggle.SetToggled(false);
}

void ComboBox::OnUpdate(float elasped)
{
	_width = _textbox.GetWidth() + _toggle._width;

	if(_items.size() > 0)
		_height = _textbox.GetHeight() + (((TextButton*)_items.at(0))->GetHeight()	*_items.size());
	else
		_height = _textbox.GetHeight();

	_toggle.OnUpdate(elasped);
}


void ComboBox::OnDraw()
{
	_textbox.Draw(_x, _y);

	_toggle._x = _x + _textbox.GetWidth();
	_toggle._y = _y;
	_toggle.OnDraw();

	if (_toggle.IsToggled()) {

		int h = ((TextButton*)_items.at(0))->GetHeight()	*_items.size();

		SDL_Rect rect = {_x, _y+ _textbox.GetHeight(), 
			_textbox.GetWidth(), h +10 };

		SDL_SetRenderDrawColor(CURRENT_RENDERER, 22, 84, 99, 0xFF);
		SDL_RenderFillRect(CURRENT_RENDERER, &rect);

		int y = _y + _textbox.GetHeight();
		for (int i = 0; i < _items.size(); i++)
		{
			TextButton* obj = _items.at(i);
			obj->_x = _x;
			obj->_y = y;
			obj->OnDraw();

			y += obj->_height;
		}
	}
}
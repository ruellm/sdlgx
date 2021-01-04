#include "rectangle_button.h"
#include "engine.h"

using namespace sdlgx::gui;
using namespace sdlgx::core;

RectangleButton::RectangleButton()
	: _with_fill(false), _selected(false)
{}

RectangleButton::~RectangleButton()
{
}

void RectangleButton::OnUpdate(float elapsed)
{}

void RectangleButton::OnDraw()
{
	SDL_Rect r;
	r.x = _x;
	r.y = _y;
	r.w = _width;
	r.h = _height;

	if (_with_fill) {
		SDL_SetRenderDrawColor(CURRENT_RENDERER, _fill_color.r, _fill_color.g, _fill_color.b, 255);
		SDL_RenderFillRect(CURRENT_RENDERER, &r);
	}

	if (_selected) {
		SDL_SetRenderDrawColor(CURRENT_RENDERER, _highlight_color.r, _highlight_color.g, _highlight_color.b, 255);
		SDL_RenderFillRect(CURRENT_RENDERER, &r);
	}

	SDL_SetRenderDrawColor(CURRENT_RENDERER, _rect_color.r, _fill_color.g, _fill_color.b, 255);
	SDL_RenderDrawRect(CURRENT_RENDERER, &r);

	DrawText();
}

void RectangleButton::OnMouseEnterMove(int x, int y)
{
	_selected = true;
}

void RectangleButton::OnMouseLeave()
{
	_selected = false;
}

void RectangleButton::Set(int x, int y, int width, int height, bool fill)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_with_fill = fill;
}

void RectangleButton::SetFillColor(Uint8 r, Uint8 g, Uint8 b)
{
	_rect_color.r = r;
	_rect_color.g = g;
	_rect_color.b = b;
	_with_fill = true;
}

void RectangleButton::SetRectColor(Uint8 r, Uint8 g, Uint8 b)
{
	_fill_color.r = r;
	_fill_color.g = g;
	_fill_color.b = b;
}

void RectangleButton::SetHighlightColor(Uint8 r, Uint8 g, Uint8 b)
{
	_highlight_color.r = r;
	_highlight_color.g = g;
	_highlight_color.b = b;
}
void RectangleButton::IsFill(bool fill)
{
	_with_fill = fill;
}
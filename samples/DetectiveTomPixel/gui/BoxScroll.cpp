#include "BoxScroll.h"
#include "definitions.h"
#include "font.h"

BoxScroll::BoxScroll() :
	_window(NULL)
{

}

BoxScroll::~BoxScroll()
{

}

void BoxScroll::OnDraw()
{
	_bg.OnDraw();

	SDL_Rect src = {0, _yoffset, _window->GetWidth(), _viewport_height };
	SDL_Rect dest = {_x + _window_X_offset, 
					 _y + _window_Y_offset, 
					 _window->GetWidth(),
					_viewport_height };
	
	_window->SetBlendMode(SDL_BLENDMODE_BLEND);
	_window->Draw(src, dest);

	_bar.OnDraw();
}

void BoxScroll::OnUpdate(float elapsed)
{
	_bar.OnUpdate(elapsed);
	_yoffset = _bar.GetPercentage() * _window->GetHeight();
}

void BoxScroll::SetBG(int resid)
{
	_bg.LoadFromResource(resid);
	_width = _bg.GetWidth();
	_height = _bg.GetHeight();
}

void BoxScroll::SetContent(sdlgx::scene::Texture* surface)
{
	_window = surface;
}

sdlgx::scene::Texture* BoxScroll::GetContent()
{
	return _window;
}


bool BoxScroll::OnMouseMove(int x, int y)
{
	return _bar.OnMouseMove(x, y);
}

bool BoxScroll::OnMouseDown(int x, int y)
{
	return _bar.OnMouseDown(x, y);
}

bool BoxScroll::OnMouseUp(int x, int y)
{
	return _bar.OnMouseUp(x, y);
}

bool BoxScroll::OnMouseUpOut(int x, int y)
{
	return _bar.OnMouseUpOut(x, y);
}

ScrollBar* BoxScroll::GetScrollBar()
{
	return &_bar;
}

/**/
/**/
/**/
CaseFileScrollBox::CaseFileScrollBox()
{

}

CaseFileScrollBox::~CaseFileScrollBox()
{

}

void CaseFileScrollBox::Init()
{
	SetBG(CASE_FILE_BOX_IMG);
	_bar.SetBarImage(CASE_FILE_SCROLLBAR_IMG);
	_bar.SetThumbImage(CASE_FILE_DRAG_IMG);
}

void CaseFileScrollBox::SetCoordinates(int x, int y)
{
	_x = x;
	_y = y;
	_bg.SetCoordinates(x, y);
	_bar.SetCoordinates(x + 364, y + 13);
	_window_X_offset = 5;
	_window_Y_offset = 5;
	_viewport_height = _bg.GetHeight();

}

sdlgx::scene::Texture* 
CaseFileScrollBox::BuildContent(
	char* title,
	char content[][50],
	int count)
{
	sdlgx::scene::Texture* texture = new sdlgx::scene::Texture();
	texture->Create(770-25, 500);

	texture->SetRenderTarget();
	
	sdlgx::scene::SDLGX_DrawText(10, 10,
		"Test", FONT_MANASPACE, 10, { 255,255,255 });

	sdlgx::scene::SDLGX_DrawText(10, 40,
		"The quick brown fox", FONT_MANASPACE, 10, { 255,255,255 });

	sdlgx::scene::SDLGX_DrawText(10, 90,
		"Are you crazy?", FONT_MANASPACE, 10, { 255,255,255 });
	
	texture->UnSetRenderTarget();
	return texture;
}

/**/
/**/
/**/
LogScrollBox::LogScrollBox() 
{

}

LogScrollBox::~LogScrollBox()
{
	SAFE_DELETE(_window);
}

void LogScrollBox::Init()
{
	SetBG(LOGS_WINDOW_IMG);
	_bar.SetBarImage(LOGS_SCROLL_LINE_IMG);
	_bar.SetThumbImage(LOGS_SCROLL_DRAG_IMG);
}

void LogScrollBox::Load()
{
	_window = new sdlgx::scene::Texture();
	_window->Create(1440 - 53, 1500);

	_window->SetRenderTarget();

	sdlgx::scene::SDLGX_DrawText(10, 10,
		"Test", FONT_MANASPACE, 50, { 255,255,255 });

	sdlgx::scene::SDLGX_DrawText(10, 70,
		"The quick brown fox", FONT_MANASPACE, 50, { 255,255,255 });

	sdlgx::scene::SDLGX_DrawText(10, 140,
		"Are you crazy?", FONT_MANASPACE, 50, { 255,255,255 });

	_window->UnSetRenderTarget();

}

void LogScrollBox::SetCoordinates(int x, int y)
{
	_x = x;
	_y = y;
	_bg.SetCoordinates(x, y);
	_bar.SetCoordinates(x + 1440, y + 55);
	_window_X_offset = 53;
	_window_Y_offset = 55;
	_viewport_height = _bg.GetHeight() - (55 + 55);
}

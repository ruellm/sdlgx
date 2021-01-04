#include "RectTextButton.h"
#include "font.h"

using namespace sdlgx::scene;

RectTextButton::RectTextButton() 
	: _idle(NULL), _hover(NULL)
{}

RectTextButton::~RectTextButton()
{
	SAFE_DELETE(_idle);
	SAFE_DELETE(_hover);
}

void RectTextButton::SetTextParam(const char* szText,
	int fontid, int size,
	SDL_Color idle, SDL_Color hover)
{
	_idle = SDLGX_GetText(szText, fontid, size, idle);
	_hover = SDLGX_GetText(szText, fontid, size, hover);
}

void RectTextButton::DrawText()
{
	int cx = _x + (_width / 2);
	int cy = _y + (_height / 2);

	sdlgx::scene::Texture* text = (_selected)?_hover:_idle;

	int x = cx - (text->GetWidth() / 2);
	int y = cy - (text->GetHeight() / 2);
	text->Draw(x, y);
}
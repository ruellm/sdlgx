#include "text_button.h"
#include "font.h"

using namespace sdlgx::gui;
using namespace sdlgx::scene;

TextButton::TextButton() : Button()
{

}


TextButton::~TextButton()
{
}


void TextButton::Load(char* text, int size, int fontid,
	SDL_Color idle,	SDL_Color hover,SDL_Color clicked)
{
	if (!SDLGX_IsFontInitialized()) return;

	_idleImg = SDLGX_GetText(text, fontid, size, idle);
	_highLightImg = SDLGX_GetText(text, fontid, size, hover);
	_clickdImg = SDLGX_GetText(text, fontid, size, clicked);

	_width = _idleImg->GetWidth();
	_height = _idleImg->GetHeight();

}
#include "GlowButton.h"
#include "font.h"

using namespace sdlgx::gui;
using namespace sdlgx::scene;

GlowButton::GlowButton() : Button()
{
}


GlowButton::~GlowButton()
{
}

void GlowButton::SetGlowImage(int resid, float accel)
{
	_glow.Load(resid);
	_glow.GLOW_ALPHA_ACCEL = accel;
}

void GlowButton::OnDraw()
{
	if (_select) {
		int centerX = _x + (_width / 2);
		int centerY = _y + (_height / 2);
		int x = centerX - (_glow._width / 2);
		int y = centerY - (_glow._height / 2);	
		_glow.OnDraw(x, y);
	}

	Button::OnDraw();
}

void GlowButton::OnUpdate(float elapsed)
{
	if (_select) {
		_glow.OnUpdate(elapsed);
	}

	Button::OnUpdate(elapsed);
}


/**/
/**/
GlowToggleButton::GlowToggleButton() : 
	GlowButton(), _toggled(false)
{

}

bool GlowToggleButton::OnMouseDown(int x, int y)
{
	SetToggled(!_toggled);
	return true;
}

void GlowToggleButton::OnDraw()
{
	if (_toggled) {
		_currentImg = _clickdImg;
	}
	GlowButton::OnDraw();
}

bool GlowToggleButton::IsToggled()
{
	return _toggled;
}

void GlowToggleButton::SetToggled(bool value)
{
	_toggled = value;
}

/**/
/**/
GlowButtonText::GlowButtonText() 
	: GlowButton(), _idle(NULL), _hover(NULL)
{
}

GlowButtonText::~GlowButtonText()
{
	SAFE_DELETE(_idle);
	SAFE_DELETE(_hover);
}

void GlowButtonText::SetTextParam(char* szText,
	int fontid, int size,
	SDL_Color idle, SDL_Color hover)
{
	_text = std::string(szText);
	_idle = SDLGX_GetText(szText, fontid, size, idle);
	_hover = SDLGX_GetText(szText, fontid, size, hover);
}

void GlowButtonText::OnDraw()
{
	GlowButton::OnDraw();
	Texture* texture = _idle;
	if (_select) {
		texture = _hover;
	}

	int x = (_x + (_width/2)) - (texture->GetWidth()/2);
	int y = (_y + (_height / 2)) - (texture->GetHeight() / 2);
	texture->Draw(x,y);
}

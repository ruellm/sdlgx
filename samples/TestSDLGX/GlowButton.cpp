#include "GlowButton.h"


using namespace sdlgx::gui;

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